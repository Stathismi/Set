#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define SETSIZE 1
#define ZEROSIZE 0

set* set_init(void)
{
   set *s;
   s=(set *)calloc(SETSIZE, sizeof(set));
   if(s==NULL){
      ON_ERROR("Creation of Set Failed\n");
   }
   s->ua=arr_init();
   s->sz=ZEROSIZE;
   return s;
}

set* set_copy(set* s)
{
   int i;
   set *sa=set_init();
   for(i=0; i<set_size(s); i++){
      set_insert(sa, arr_get(s->ua, i));
   }
   return sa;
}

set* set_fromarray(arrtype* a, int n)
{
   int i;
   set *sa=set_init();
   if(a==NULL){
      return sa;
   }
   for(i=0; i<n; i++) {
      set_insert(sa, a[i]);
   }
   return sa;
}

void set_insert(set* s, arrtype l)
{
   if(s!=NULL){
      if(!set_contains(s, l)){
         arr_set(s->ua, set_size(s), l);
         s->sz++;
      }
   }
}

int set_size(set* s)
{
   if(s==NULL){
      return 0;
   }
   return s->sz;
}

int set_contains(set* s, arrtype l)
{
   int i;
   arrtype unique_value;
   for(i=0; i<set_size(s); i++){
      unique_value=arr_get(s->ua, i);
      if(memcmp(&unique_value, &l, sizeof(arrtype))==0){
         return 1;
      }
   }
   return 0;
}

void set_remove(set* s, arrtype l)
{
   int i, k;
   arrtype unique_value;
   for(i=0; i<set_size(s); i++){
      unique_value=arr_get(s->ua, i);
      if(memcmp(&unique_value, &l, sizeof(arrtype))==0){
         for(k=i; k<(set_size(s)-1); k++){
            arr_set(s->ua, k, arr_get(s->ua, k+1));
         }
         s->sz--;
         return;
      }
   }
}

arrtype set_removeone(set* s)
{
   arrtype last_element = arr_get(s->ua, (set_size(s)-1));
   s->sz--;
   return last_element;
}

set* set_union(set* s1, set* s2)
{
   int i;
   set *sa=set_init();
   if(s1==NULL && s2==NULL){
      return sa;
   }
   if(s1==NULL){
      sa=set_copy(s2);
      return sa;
   }
   if(s2==NULL){
      sa=set_copy(s1);
      return sa;
   }
   sa=set_copy(s1);
   for(i=0; i<set_size(s2); i++) {
      set_insert(sa, arr_get(s2->ua, i));
   }
   return sa;
}

set* set_intersection(set* s1, set* s2)
{
   set *sa= set_init();
   int i;
   if(s1==NULL || s2==NULL){
      return sa;
   }
   for(i=0; i<set_size(s2); i++) {
      if(set_contains(s1, arr_get(s2->ua, i))){
         set_insert(sa, arr_get(s2->ua, i));
      }
   }
   return sa;
}

void set_free(set **s)
{
   if(s!=NULL){
      set* a = *s;
      arr_free(&a->ua);
      free(a);
      *s = NULL;
   }
}
