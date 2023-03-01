#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include "logger.h"

int _withLogs;

void init_logger(char* withLogs) {
	if(strcmp(withLogs, "log") == 0){
      _withLogs = 1;
   }
}

void logger(const char* tag, const char* message) {
	if (!_withLogs) return;

   FILE *fp;

   fp = fopen("log.txt", "a");
   time_t now;
	time(&now);
	fprintf(fp, "%s [%s]: %s\n", ctime(&now), tag, message);
   fclose(fp);
} 