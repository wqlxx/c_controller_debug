#include <stdio.h>
#include "debug.c"

int main(int argc, char *argv[])
{	
	/*--------------------初始化---------------------*/
	char* log_dir = "./log";//the dir
	unsigned int  log_terminal = 1;//debug on terminal: yes or not

/* init the debug info */
	if( log_terminal )
	{
		debug_term_on();
	}
	else
	{
		debug_term_off();
	}
	if( log_dir == NULL ){
		debug_file_off();
	}else{
		debug_set_dir( log_dir );
		debug_file_on();
	}

	/*-------------------使用测试---------------------*/
  DBG("I printf on stdout and logfile...\n");
  return 0;
}
