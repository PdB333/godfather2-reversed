// FUNC_NAME: EARSObject::EARSObject

void __fastcall EARSObject::constructor(EARSObject* this, int** vtableSlot1)
{
    int *nodePtr;
    int *listPtr;
    int* secondVtableSlot;

    // Set primary vtable pointer (likely at offset 0)
    *vtableSlot1 = &PTR_FUN_00e373b0;

    // Call base class constructors (three base classes)
    FUN_004ebba0(); // Base1 constructor
    FUN_004ebba0(); // Base2 constructor
    FUN_004ebba0(); // Base3 constructor

    // After last base constructor, EDX points to the secondary vtable slot
    secondVtableSlot = extraout_EDX;
    *secondVtableSlot = &PTR_FUN_00e37110;

    // Linked list insertion into global object list
    // DAT_01206880 + 0x14 holds pointer to list head structure
    nodePtr = (int*)secondVtableSlot[4]; // +0x10: pointer to next node? (maybe list prev)
    if (nodePtr != 0) {
        listPtr = (int*)(DAT_01206880 + 0x14);
        // Insert this object into the global list
        **(int***)listPtr = &PTR_LAB_01123be8; // Set prev pointer
        *listPtr = *listPtr + 4;               // Advance list pointer (to next slot)
        *(int*)*listPtr = (int)nodePtr;        // Link to old node
        *listPtr = *listPtr + 4;               // Advance again
        secondVtableSlot[4] = 0;               // Clear node pointers
        secondVtableSlot[5] = 0;
    }
}