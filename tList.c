
#include <stdio.h>
#include <string.h>
#include "List.h"

static int compString (void * s1, void * s2) {
  return strcmp((char*)s1, (char*)s2);
}

static void prString(void * s) {
  printf("%s",(char*)s);
}

static void prString2 (void * s) {
  printf("%s\n",(char*)s);
}

int startsWithM(void* s){
  return ((char*)s)[0] == 'm';
}

int main() {
  int i; status st;
  char * tab[] = {"belle marquise", "vos beaux yeux", "me font",
		  "mourir", "d'amour" };
  char* s;

  /* list creation */
  List* l = newList(compString,prString);
  if (!l) return 1;

  /* populating list */
  for (i=0; i < sizeof(tab)/sizeof(char*); i++)
    addList(l,tab[i]);

  /* display list - should be sorted */
  displayList(l);
  putchar('\n');

  /*  test contain predicate */
  if (isInList(l,"mourir"))
    puts("mourir is in list");
  else
    puts("mourir is not in list");
  if (isInList(l,"vivre"))
    puts("vivre is in list");
  else
    puts("vivre is not in list");

  /* access Nth element 3 = "me font" */
  st = nthInList(l, 3, &s);
  if (st) {fprintf(stderr,"%s\n", message(st)); return 1;}
  printf("me font? : %s\n",s);

  /* remove and add element */
  st = remFromListAt(l,4,&s);
  if (st) {fprintf(stderr,"%s\n", message(st)); return 2;}
  printf("mourir? : %s\n",s);
  st = addListAt(l,4,s);
  if (st) {fprintf(stderr,"%s\n", message(st)); return 3;}
  st = remFromList(l,s);
  if (st) {fprintf(stderr,"%s\n", message(st)); return 4;}
  st = addList(l,s);
  if (st) {fprintf(stderr,"%s\n", message(st)); return 5;}


  /* test length (beware: sizeof is long int!) */
  printf("length : %d (expected %ld)\n", lengthList(l),
	 sizeof(tab)/sizeof(char*));

  /* test forEach */
  puts("forEach:");
  forEach(l,prString2);

  /* final cleanup */
  delList(l);

  return 0;
}

