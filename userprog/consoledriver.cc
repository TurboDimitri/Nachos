#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore* readAvail;
static Semaphore* writeDone;
static void ReadAvailHandler (void*arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler (void*arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char*in, const char*out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}
ConsoleDriver::~ConsoleDriver()
{
    delete console;
    delete writeDone;
    delete readAvail;
}
void ConsoleDriver::PutChar(int ch){

    if (ch != '\n'){
        console->TX('<');
        writeDone->P();
    }
    console->TX(ch);
    writeDone->P();
    if (ch != '\n'){
        console->TX('>');
        writeDone->P();
    }
}
int ConsoleDriver::GetChar()
{
    readAvail->P();
    int ch = console->RX();
    return ch;
}
void ConsoleDriver::PutString(const char s[])
{
    int i = 0;
;
    while (s[i]!= '\0'){

        PutChar(s[i]);
        i++;
    }
}
void ConsoleDriver::GetString(char*s,int n)
{
   int i = 0;
   char tmp;
   while((i < n) && tmp != EOF && tmp != '\n'){

       tmp = GetChar();
       s[i] = tmp;

       i++;
   }
   s[i]='\0';

}

int ConsoleDriver::copyStringFromMachine(int from, char* to, unsigned size){
    unsigned i = 0;
    int tmp;

    while((i<size-1) && (machine ->ReadMem(from+i, 1, &tmp)) && ((char)tmp != '\0'))
{
      to[i] = (char) tmp;
      i++;
}

    to[i]='\0';

    return i+1;
}

void ConsoleDriver::copyStringToMachine(char* from, int to, unsigned size)
{
    unsigned i = 0;
    int tmp;
    while(i < size-1 && (machine->WriteMem(to+i, 1, (int ) from[i])) && (char) tmp != '\0'){
      tmp = (char ) to+i;
      i++;
    }
    machine->WriteMem(to+i,1, (int ) '\0');
}

int ConsoleDriver::length(int from){
    int i = 0;
    int tmp;
    while((machine ->ReadMem(from+i, 1, &tmp)) && ((char)tmp != '\0')) {
        i++;
    }
    return i;
}

    #endif // CHANGED
