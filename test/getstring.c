#include "syscall.h"

#define MAX_STRING_SIZE 256

/*
* Ce programme de test utilise la fonction GetString et PutString
*   Il peut être appelé avec 0, 1 ou 2 arguments.
*   Avec 0 arguments il attend de l'utilisateur qu'il écrive une chaîne de caractères dans la console et renverra "MAX_STRING_SIZE" caractères entourés de
*   chevrons.
*   Avec 1 argument (un fichier déjà existant dans code/userprog), il lira MAX_STRING_SIZE caractères du fichier et les reverra dans la console entourés de chevrons
*   Avec 2 arguments (deux fichiers déjà existant dans code/userprog), il lira MAX_STRING_SIZE caractères du premier fichier passé en paramètre
*   puis les écrira dans le deuxième fichier passé en paramètre entourés de chevrons
*   /!\ Attention /!\ En réalité dans on ne vera que MAX_STRING_SIZE - 1 caractères écrits car un caractère est utilisé pour écrire '\0' pour assurer la
*   sécurité du système.
*   L'utilisateur a le droit de modifier MAX_STRING_SIZE à sa guise (dans les limites du raisonnable).
*/
int main(){
  char buffer[MAX_STRING_SIZE];
  GetString(buffer, MAX_STRING_SIZE);
  PutString(buffer);
  return 0;
}
