
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"


int main(int argc, char **argv)
{
  IS is;
  int i; 
  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct("./.kilit");
  if (is == NULL) {
    perror("./.kilit");
    exit(1);
  }

  /* Read each line with get_line().  Print out each word. */

  while(get_line(is) >= 0) {
      char *ch;
      ch = strtok(is->text1, ":");
      while (ch != NULL) {
         printf("%s\n", ch);
         ch = strtok(NULL, ":");
      }
  }

  /* Free up the memory allocated with new_inputstruct, and
     close the open file.  This is not necessary in this program, 
     since we are exiting anyway, but I just want to show how you free it up. */

  jettison_inputstruct(is);
  return 0;
}