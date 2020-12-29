#include "dict.h"
#if __linux__
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#endif

#include <raylib.h>


static char ** dictionary_create_array(int count){
    char **tmp = NULL;
    int i;
    tmp = malloc(count * sizeof(char*));


    for(i = 0; i < count; i++){
        tmp[i] = malloc(255);
    }

    return tmp;
}

static dictionary *dictionary_init(){
        dictionary *dt = malloc(sizeof(dictionary));
        dt->count = 0;
        dt->words = NULL;

        return dt;
}


static int dictionary_count_lines(FILE *fp){
    if(!fp) return -1;
    char tmp;
    int lines = 0;
    while(fscanf(fp, "%c",&tmp) != -1){
        if(tmp == '\n') lines++;
    }

    return lines;
}

static char** dictionary_gen_word_list(FILE *fp, int count){
   char **list = NULL;
   int i;

   list = malloc(count * sizeof(char*));


   for(i = 0; i < count; i++){
       list[i] = malloc(255 * sizeof(char));
   }

   char buf[255 + 1] = {0};
   int line_count = 0;
   while(fgets(buf,255,fp)){
        char *line = &buf[0];

        //list[line_count] = line;
        memcpy(list[line_count], line, 255);

        line_count++;
   }

   return list;
}

dictionary *dictionary_start(const char *filename)
{
    dictionary *dt =  NULL;
    int total_lines = 0;
    FILE *fp = NULL;


    dt = dictionary_init();
    fp = fopen(filename, "rb+");

    if(!fp) goto failed_dict;

    total_lines = dictionary_count_lines(fp);
    fprintf(stdout, "%d lines loaded!\n\n", total_lines);
    rewind(fp);

    dt->words = malloc(sizeof (char*) * total_lines);




    dt->count = total_lines;
    dt->words = dictionary_gen_word_list(fp, total_lines);
    fclose(fp);

    //total_lines = dic
    return dt;

failed_dict:
    if(fp)fclose(fp);
    if(dt->words)free(dt->words);
    if(dt)free(dt);
    return NULL;

}

void dictionary_info(dictionary *d)
{
    int i;
    for(i = 0; i < d->count; i++){
        fprintf(stdout, "%s", d->words[i]);
    }
}

char **dictionary_array_random_words(dictionary *dt, int count)
{

    int i;
    char **list = dictionary_create_array(count);

    for(i = 0; i < count ; i++){
        int rnd = GetRandomValue(0, dt->count - 1);
        memcpy(list[i], dt->words[rnd], 255);
    }

    return list;
}
