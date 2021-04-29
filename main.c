#include <stdlib.h>
#include <stdio.h>
#include "fields.h"
#include <string.h>


int main(int argc, char *argv)
{
    IS is;
    is = new_inputstruct(".kilit");
    while (get_line(is) >= 0)
    {
      //jsondaki süslü parantezleri ayırma
        if (is->NF > 1)
        {
            char *token;
            char * token2;
            token = strtok(is->fields[0], ":");
            token2 = strtok(is->fields[1], ",");
            //json dan alınan stringlerin başındaki ve sonundaki tırnakları silme işlemi.
            token++;
            token2++;
            token2[strlen(token2) - 1] = 0;  
            token[strlen(token)-1] = 0;
            printf(" %s\n", token);

        }
    }
    jettison_inputstruct(is);
    return 0;
}