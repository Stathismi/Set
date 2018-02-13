#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

void file_to_set(set *s, FILE *fp);
void print_results(set *sa, set *sb, set *sc);

int main(void)
{
   set *sa, *sb, *sc;
   FILE *fp1, *fp2;
   fp1=fopen("sense-and-sense.txt", "r");
   fp2=fopen("pride-andprej.txt", "r");
   if(fp1==NULL || fp2==NULL){
      ON_ERROR("Opening of a file Failed\n");
   }

   sa=set_init();
   sb=set_init();
   file_to_set(sa, fp1);
   file_to_set(sb, fp2);
   sc=set_intersection(sa, sb);
   print_results(sa, sb, sc);

   fclose(fp1);
   fclose(fp2);
   set_free(&sa);
   set_free(&sb);
   set_free(&sc);

   return 0;
}

void file_to_set(set *s, FILE *fp)
{
   arrtype tmp, tmp2;
   memset(&tmp2, ' ', sizeof(arrtype));

   while(fgets((char *)(&tmp.str), sizeof(arrtype), fp)!= NULL ){
      if(sscanf((char *)(&tmp.str), "%s", (char *)(&tmp2.str))==1){
         set_insert(s, tmp2);
         memset(&tmp2, ' ', sizeof(arrtype));
      }
   }
}

void print_results(set *sa, set *sb, set *sc)
{
   printf("There are %d unique words in sense-and-sense.txt\n",set_size(sa));
   printf("There are %d unique words in pride-and-prej.txt\n",set_size(sb));
   printf("There are %d common words\n",set_size(sc));

}
