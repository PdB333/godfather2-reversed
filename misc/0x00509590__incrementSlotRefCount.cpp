// FUNC_NAME: incrementSlotRefCount
#include <intrin.h>

/**
 * Increments a reference count byte in a per-thread slot array.
 * 
 * @param slotIndex  Index of the slot (passed in EAX register).
 * @param subSlotPtr Pointer to a sub-index that selects a byte within the slot.
 * @return Pointer to the incremented byte.
 * 
 * The function accesses thread-local storage at FS:[0x2C] to get a TLS base,
 * then reads a pointer at offset +0x08 from that base to obtain the start of
 * an array of 0x50-byte blocks (slots). Each slot has a small reference-count
 * byte table starting at offset +0x55. The sub-index selects which byte to
 * increment. The function returns the address of that byte.
 * 
 * Calling convention: __fastcall? Actually first parameter (slotIndex) is in EAX,
 * second (subSlotPtr) on stack. This matches GCC regparm(1) or a custom convention.
 */
int* __fastcall incrementSlotRefCount(int slotIndex, int* subSlotPtr)
{
    // Get the pointer to the per-thread data from TLS (offset 0x2C)
    int* tlsBase = *(int**)__readfsdword(0x2C);

    // Dereference to get the table pointer (offset +8 from the TLS structure)
    int* tablePtr = *(int**)((char*)tlsBase + 8);

    // Calculate the base address of the requested slot (each slot is 0x50 bytes)
    char* slotBase = (char*)tablePtr + slotIndex * 0x50;

    // Get the sub-index from the provided pointer
    int subIndex = *subSlotPtr;

    // Point to the specific reference-count byte within the slot (+0x55)
    char* refCount = slotBase + 0x55 + subIndex;

    // Increment the reference count
    (*refCount)++;

    // Return the address of the incremented byte (callers may use this for later decrement)
    return (int*)refCount;
}