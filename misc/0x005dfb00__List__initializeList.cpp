// FUNC_NAME: List::initializeList
void __thiscall List::initializeList(void) 
// 'this' in ESI (unaff_ESI), arg in EAX (in_EAX) - nonstandard calling convention
{
    // in_EAX points to an object with a vtable (first dword is vtable pointer)
    int* vtable = *(int**)in_EAX;  // *in_EAX = vtable pointer
    int secondField = in_EAX[1];   // +0x04

    // Call virtual function at vtable+8 (third entry) – likely base class init
    (*(code**)(vtable[2]))(vtable);  // passes vtable pointer? Unusual; might be constructor override

    // If secondField is non-zero, copy something from it (FUN_004265d0)
    int copyResult;
    if (secondField == 0) {
        copyResult = 0;
    } else {
        copyResult = FUN_004265d0(secondField, vtable);  // possibly deep copy
    }

    // Link the source object (vtable?) into the list (FUN_005e0800)
    // unaff_ESI = this (list object)
    FUN_005e0800(this, vtable, copyResult);

    // Allocate a new list node (head/sentinel)
    int* newNode = (int*)FUN_005e10a0();  // returns a freshly allocated node
    // Store pointer to the new node at this+0x1c (likely a list head member)
    *(int*)(this + 0x1c) = (int)newNode;

    // Initialize the node as a circular doubly-linked list (self-loop)
    *(char*)((int)newNode + 0x15) = 1;          // +0x15: flag? mark as sentinel
    newNode[1] = (int)newNode;                   // +0x04: prev = self
    *newNode = (int)newNode;                     // +0x00: next = self
    newNode[2] = (int)newNode;                   // +0x08: some pointer? likely third pointer

    // Clear member at this+0x20 (optional count or cursor)
    *(int*)(this + 0x20) = 0;
    return;
}