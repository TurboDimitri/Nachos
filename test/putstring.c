#include "syscall.h"

#define MESSAGE "Je suis une string !\n"
#define MESSAGE2 "Moi aussi !\n"


/* Ce programme de test utilise la fonction PutString
*  Il doit être appelé avec 0 ou 2 arguments
*  Avec 0 argument cette fonction va écrire dans la console "MESSAGE" puis "MESSAGE2" avec chaque caractères entourés de chevrons.
*  Avec 2 arguments in.txt et out.txt le programme va écrire la même chose mais dans out.txt.
*  Le dernier message est un message vide pour s'assurer que le programme fonctionne avec une chaîne vide.
*  A vrai dire l'argument in.txt ne sert à rien mais si on essaye de lancer le programme avec seulement un argument out.txt alors il va
*  simplement écrire "MESSAGE" puis "MESSAGE2" avec chaque caractères entourés de chevrons dans la console.
*  L'utilisateur peut utiliser des messages de n'importe quelle taille.
*/
int main ()
{
	PutString(MESSAGE);
	PutString(MESSAGE2);
	//PutString('a');// <- On ne peut pas passer une seul caractère en paramètre à PutString. Bien qu'on puisse passer une chaîne de caractères de 1 caractère.
	// PutString("a"); <- Ceci fonctionne
	return 0;
}
