#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

		t_log* logger;
	t_config* config;

  //char log_user[100];
	/* ---------------- LOGGING ---------------- */
	
	//abir copilot desde las commmons
	logger = iniciar_logger();

	//log_info(logger, "Hola! Soy un log");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/*ingreso de parametros fuera de uso*/
	//printf("Ingrese texto a loggar!\n");
	//fgets(log_user, sizeof(log_user), stdin);
	//log_user[strcspn(log_user, "\n")] = 0; // Eliminar el salto de línea

	//log_info(logger,log_user);

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config

	//obtiene el valor de la "clave" de la configuracion
	valor = config_get_string_value(config, "CLAVE");
	////la loggea en un mensaje
	//log_info(logger, valor);

	//leemos "ip" y "puerto" de la configuracion
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);


	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger()
{
	t_log* nuevo_logger;
	
		//char file[20];
		//char process[20];
		//int print_console;
		//t_log_level level;

				//printf("Ingrese nombre archivo donde loggear\n");


				//printf("Ingrese nombre del proceso a loggear\n");

				//printf("desea imprimir por consola? (1/0)\n");
				//// Si elige 1, se imprime por consola, si elige 0 no

				//print_console = (bool) print_console;

				//printf("Ingrese el nivel de log 0 = Trace , 1 = Debug, 2 = Info, 3 = Warning , 4 = Error \n");

	nuevo_logger = log_create("tp0.log", "config test", false, LOG_LEVEL_INFO);
	if (nuevo_logger == NULL)
	{
		abort();
	}
	
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	//obtiene el directorio de trabajo actual
	char* path = getcwd(NULL, 0);
	//le agrega el nombre del archivo de configuracion
	string_append(&path, "/cliente.config");

	//pasa el nobre del archivo a la funcion de commons
	//config_create para crear el archivo de configuracion
	//config_create devuelve un puntero a la estructura t_config
	nuevo_config = config_create(path);

	if (nuevo_config == NULL)
	{
		abort();
	}
	
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	printf("Ingrese nombre del proceso a loggear\n");
	// La primera te la dejo de yapa
	//bucle levantado de la documentación de readline
	while (1)
	{
		leido = readline("> ");
		// Si no se ingresa nada, se sale del bucle
		if (leido == NULL || strlen(leido) == 0)
			break;

		// Loggeamos lo que leemos
		log_info(logger, leido);

		printf("loggeando: %s\n", leido);

		// Liberamos la memoria ocupada por la línea leída
		free(leido);
		
		printf("Ingrese nombre del proceso a loggear\n");
	}
	

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	//devuelve lo leido por consola a log_info
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	printf("Ingrese lineas para enviar al servidor\n");

	// Leemos y esta vez agregamos las lineas al paquete
	while (1)
	{
		leido= readline("> ");
		// Si no se ingresa nada, se sale del bucle
		if (leido == NULL || strlen(leido) == 0)
			break;
		//
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
	}

	enviar_paquete(paquete, conexion);
	

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
	  config_destroy(config);
	  close(conexion);
}
