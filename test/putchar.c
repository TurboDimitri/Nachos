#include "syscall.h"


/* Ce programme de test utilise la fonction PutChar
*  Il doit être appelé avec 0 ou 2 arguments.
*  Avec 0 argument cette fonction va écrire dans la console "abcd" avec chaque caractères entourés de chevrons.
*  Avec 2 arguments in.txt et out.txt le programme va écrire la même chose mais dans out.txt.
*  A vrai dire l'argument in.txt ne sert à rien mais si on essaye de lancer le programme avec seulement un argument out.txt alors il va
*  simplement écrire "abcd" avec chaque caractères entourés de chervons dans la console.
*/
void print(char c, int n){
  int i;
#if 1
  for (i = 0; i < n; i++) {
    PutChar(c + i);
  }
  // PutChar("test"); <- Quand on essaye d'utiliser PutChar avec une chaîne de caractères en paramètres le programme écrit juste "<>" dans la console.
#endif
}

int
main()
{
  print('a',4);
  return 8;
}

