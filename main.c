#include <stdlib.h>
#include <stdio.h>
#include "fields.h"
#include <string.h>
#include "jrb.h"
#include <fcntl.h>
#include <unistd.h>
void encripted_decripted(char *tur, char *giris_metin, char *cikis_metin)
{
    //Tanımlamalar
    JRB b, node;
    int fd, sz;
    IS is, is2;
    is = new_inputstruct(".kilit");
    b = make_jrb();
    if (is == NULL)
    {
        perror(".kilit");
        exit(1);
    }
    while (get_line(is) >= 0)
    {
        if (is->NF > 1)// Json formatındaki dosyanın süslü parantezlerden ayırma
        {
            //Kilit dosyasındaki key value ayrışımı
            char *token;
            char *token2;
            token = strtok(is->fields[0], ":");
            token2 = strtok(is->fields[1], ",");
            token++;
            token2++;
            token2[strlen(token2) - 1] = 0;
            token[strlen(token) - 1] = 0;
            //JRB ekleme islemi
            if (tur != NULL && !strcmp(tur, "-e"))
            {
                (void)jrb_insert_str(b, strdup(token), new_jval_s(strdup(token2)));
            }
            else if (tur != NULL && !strcmp(tur, "-d"))
            {
                (void)jrb_insert_str(b, strdup(token2), new_jval_s(strdup(token)));
            }
        }
    }
    is2 = new_inputstruct(giris_metin);
    // Şifrelenecek ya da çözümlenecek metni yazdırdığımız dosyanın açılması
    fd = open(cikis_metin, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror(cikis_metin);
        exit(1);
    }

    while (get_line(is2) >= 0)
    {
        for (int i = 0; i < is2->NF; i++)
        {
            //Okuduğumuz dosyadaki değerinin agaçta olup olmadığının kontrolü
            node = jrb_find_str(b, is2->fields[i]);
            //varsa
            if (node != NULL)
            {
                //çıkış metnine yazdırma
                sz = write(fd, node->val.s, strlen(node->val.s));
                sz = write(fd, " ", strlen(" "));
            }
            //yoksa
            else
            {
                sz = write(fd, is2->fields[i], strlen(is2->fields[i]));
                sz = write(fd, " ", strlen(" "));
            }
        }
    }
    close(fd);
    jettison_inputstruct(is2);
    jettison_inputstruct(is);
}
int main(int argc, char *argv[])
{
    encripted_decripted(argv[1],argv[2],argv[3]);
    return 0;
}