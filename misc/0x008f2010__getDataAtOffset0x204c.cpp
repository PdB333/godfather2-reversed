// FUNC_NAME: getDataAtOffset0x204c
// Address: 0x008f2010
// Simple getter returning the 32-bit value at offset 0x204c from the this pointer.
// Likely a member of a large game object (e.g., Player, GodfatherGameManager).
// Field offset: +0x204c
uint32_t __fastcall getDataAtOffset0x204c(void* thisPtr) {
    return *(uint32_t*)((uint8_t*)thisPtr + 0x204c);
}