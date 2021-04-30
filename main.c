#include <stdlib.h>
#include <stdio.h>
#include "fields.h"
#include <string.h>
#include "jrb.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    IS is, is2;
    JRB b, node;
    is = new_inputstruct(".kilit");
    if (is == NULL)
    {
        perror(".kilit");
        exit(1);
    }

    if (argv[1] != NULL && !strcmp(argv[1], "-e"))
    {
        b = make_jrb();
        while (get_line(is) >= 0)
        {
            //jsondaki süslü parantezleri ayırma
            if (is->NF > 1)
            {
                char *token;
                char *token2;
                token = strtok(is->fields[0], ":");
                token2 = strtok(is->fields[1], ",");
                //json dan alınan stringlerin başındaki ve sonundaki tırnakları silme işlemi.
                token++;
                token2++;
                token2[strlen(token2) - 1] = 0;
                token[strlen(token) - 1] = 0;
                //Ağaca ekleme işlemi
                (void)jrb_insert_str(b, strdup(token), new_jval_s(strdup(token2)));
            }
        }
        //encripted islemi
        int fd, sz;
        is2 = new_inputstruct("istiklal_marsi");
        fd = open("encripted", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("encripted");
            exit(1);
        }
        while (get_line(is2) >= 0)
        {
            for (int i = 0; i < is2->NF; i++)
            {
                node = jrb_find_str(b, is2->fields[i]);
                if (node != NULL)
                {
                    sz = write(fd, node->val.s, strlen(node->val.s));
                    //bakalım
                    sz = write(fd, " ", strlen(" "));
                }
                else
                {
                    sz = write(fd, "******", strlen("******"));
                    sz = write(fd, " ", strlen(" "));
                }
            }
        }
        close(fd);
        jettison_inputstruct(is2);
    }
    else if (argv[1] != NULL && !strcmp(argv[1], "-d"))
    {
        b = make_jrb();
        while (get_line(is) >= 0)
        {
            if (is->NF > 1)
            {
                char *token;
                char *token2;
                token = strtok(is->fields[0], ":");
                token2 = strtok(is->fields[1], ",");
                token++;
                token2++;
                token2[strlen(token2) - 1] = 0;
                token[strlen(token) - 1] = 0;
                (void)jrb_insert_str(b, strdup(token2), new_jval_s(strdup(token)));
            }
        }
        //decripted islemi
        int fd, sz;
        is2 = new_inputstruct("encripted");
        fd = open("decripted", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("decripted");
            exit(1);
        }
        while (get_line(is2) >= 0)
        {
            for (int i = 0; i < is2->NF; i++)
            {
                node = jrb_find_str(b, is2->fields[i]);
                if (node != NULL)
                {
                    sz = write(fd, node->val.s, strlen(node->val.s));
                    sz = write(fd, " ", strlen(" "));
                }
                else
                {
                    sz = write(fd, "******", strlen("******"));
                    sz = write(fd, " ", strlen(" "));
                }
            }
        }
        close(fd);
        jettison_inputstruct(is2);
    }

    jettison_inputstruct(is);
    return 0;
}