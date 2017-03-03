#include <stdio.h>
#include <string.h>

#define MAX_CMD_LEN 1024

static void set_status(int * status, int value) {
  if(status != NULL) {
    (*status) = value;
  }
}

/**
 * Making calculations by calling external python command and reading it's output by pipe
 */
double calc(const char * str, int * status) {

  double result;
  FILE * p;
  char command[MAX_CMD_LEN + 1];

  snprintf(command, MAX_CMD_LEN, "python -c 'print(%s)' 2>/dev/null", str);
  
  p = popen(command, "r");

  if(p == NULL) {
    set_status(status, 1);
    return 0;
  }

  fscanf(p, "%lf", &result);
  
  set_status(status, pclose(p));

  return result;
}
