#include "syscall.h"


/*
* Ce programme de test utilise la fonction GetChar et PutChar
*   Il peut être appelé avec 0, 1 ou 2 arguments.
*   Avec 0 arguments il attend de l'utilisateur qu'il écrive un char dans la console et lui renverra entouré de chevrons
*   Avec 1 argument (un fichier déjà existant dans code/userprog), il lira le premier caractère du fichier et le reverra dans la console entouré de chevrons
*   Avec 2 arguments (deux fichiers déjà existant dans code/userprog), il lira le premier caractère du premier fichier passé en paramètre
*   puis l'écrira dans le deuxième fichier passé en paramètre entouré de chevrons
*/
int main() {

    int test = GetChar();
    PutChar(test);

    return (int) GetChar();
}