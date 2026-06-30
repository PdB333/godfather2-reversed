// FUNC_NAME: ReleaseObject
// Function at 0x004df600: Releases an object by setting a destruction flag (0x200000 at +0xC), 
// calling a cleanup function (0x0051d6b0), and nulling an external pointer link at +0x08.
// The input parameter is a pointer to the object pointer; the function dereferences it,
// checks for null, sets the flag, calls a helper, and if a secondary pointer exists at +0x08
// (a pointer to an external reference back to this object), it sets that external reference to 0
// and then zeros the pointer at +0x08 itself.
// This is used by many entity destructors and cleanup routines.

void __fastcall ReleaseObject(int* pObjectPtrPtr)
{
    int* pObject;
    
    pObject = (int*)*pObjectPtrPtr;  // +0x00: pointer to object
    if (pObject != 0) {
        // Set destruction flag (bit 0x200000) at offset +0x0C
        *(unsigned int*)(pObject + 3) |= 0x200000;  // +0x0C: flags
        // Call cleanup helper (likely frees resources or notifies manager)
        FUN_0051d6b0();
        // If there is an external back-pointer at offset +0x08
        if (*(int**)(pObject + 2) != 0) {  // +0x08: pointer to external pointer
            // Null the external reference
            **(int**)(pObject + 2) = 0;
            // Remove own link to it
            *(int*)(pObject + 2) = 0;
        }
    }
}