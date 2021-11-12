// synchdisk.cc
//	Routines to synchronously access the disk.  The physical disk
//	is an asynchronous device (disk requests return immediately, and
//	an interrupt happens later on).  This is a layer on top of
//	the disk providing a synchronous interface (requests wait until
//	the request completes).
//
//	Use a semaphore to synchronize the interrupt handlers with the
//	pending requests.  And, because the physical disk can only
//	handle one operation at a time, use a lock to enforce mutual
//	exclusion.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synchdisk.h"

//----------------------------------------------------------------------
// DiskRequestDone
// 	Disk interrupt handler.  Need this to be a C routine, because
//	C++ can't handle pointers to member functions.
//----------------------------------------------------------------------

static void
DiskRequestDone (void *arg)
{
    SynchDisk* disk = (SynchDisk *)arg;

    disk->RequestDone();
}

//----------------------------------------------------------------------
// SynchDisk::SynchDisk
// 	Initialize the synchronous interface to the physical disk, in turn
//	initializing the physical disk.
//
//	"name" -- UNIX file name to be used as storage for the disk data
//	   (usually, "DISK")
//----------------------------------------------------------------------

SynchDisk::SynchDisk(const char* name)
{
    semaphore = new Semaphore("synch disk", 0);
    lock = new Lock("synch disk lock");
    disk = new Disk(name, DiskRequestDone, this);
}

//----------------------------------------------------------------------
// SynchDisk::~SynchDisk
// 	De-allocate data structures needed for the synchronous disk
//	abstraction.
//----------------------------------------------------------------------

SynchDisk::~SynchDisk()
{
    delete disk;
    disk = NULL;
    delete lock;
    lock = NULL;
    delete semaphore;
    semaphore = NULL;
}

//----------------------------------------------------------------------
// SynchDisk::ReadSector
// 	Read the contents of a disk sector into a buffer.  Return only
//	after the data has been read.
//
//	"sectorNumber" -- the disk sector to read
//	"data" -- the buffer to hold the contents of the disk sector
//----------------------------------------------------------------------

void
SynchDisk::ReadSector(int sectorNumber, void* data)
{
    lock->Acquire();			// only one disk I/O at a time
    disk->ReadRequest(sectorNumber, data);
    semaphore->P();			// wait for interrupt
    lock->Release();
}

//----------------------------------------------------------------------
// SynchDisk::WriteSector
// 	Write the contents of a buffer into a disk sector.  Return only
//	after the data has been written.
//
//	"sectorNumber" -- the disk sector to be written
//	"data" -- the new contents of the disk sector
//----------------------------------------------------------------------

void
SynchDisk::WriteSector(int sectorNumber, const void* data)
{
    lock->Acquire();			// only one disk I/O at a time
    disk->WriteRequest(sectorNumber, data);
    semaphore->P();			// wait for interrupt
    lock->Release();
}

//----------------------------------------------------------------------
// SynchDisk::RequestDone
// 	Disk interrupt handler.  Wake up any thread waiting for the disk
//	request to finish.
//----------------------------------------------------------------------

void
SynchDisk::RequestDone()
{
    semaphore->V();
}


#ifdef CHANGED
//----------------------------------------------------------------------
//copyStringFromMachine
//
//----------------------------------------------------------------------
int
SynchDisk::copyStringFromMachine(int from, char *to, unsigned size){
  unsigned i = 0;
  int wait;
  while(i < size) && ReadMem(from[i],1,&wait)){
    to[i] = wait+'0';
    i++;
  }
  to[i] = '\0'
  return i;
  // On ne peut pas simplement passer un pointeur pointant à l'intérieur du tampon to dans ReadMem car on peut pas s'assurer de la présence d'un '\0' à la fin de la chaîne de caractères.
  // Il faudrait d'abord rentrer la chaîne de caractère dans un buffer qui possède une taille fixe, maximale et prédéfinie. De cette façon nous pouvons nous assurer que la chaîne de caractères que nous traitons ne peut pas avoir une taille trop grande.
  // Il faut un buffer qui possède une taille fixe car quand on déplace la chaîne de caractères on passe par la mémoire vive de l'ordinateur et celle-ci n'est pas infinie. Avoir une limite dure permet donc de ne pas dépasser la mémoire vive de l'ordinateur.

}
#endif
