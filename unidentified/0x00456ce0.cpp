// FUN_00456ce0: EARSObject::getSystemPointer
int __fastcall EARSObject::getSystemPointer(EARSObject* thisObj) {
    // Check if the system pointer at offset 0x28 is null; if so, initialize it via FUN_00ca3ee0 (likely a constructor)
    if (*(int*)((char*)thisObj + 0x28) == 0) {
        FUN_00ca3ee0(); // Creates or initializes the subsystem
    }
    return *(int*)((char*)thisObj + 0x28); // Return the pointer (possibly a handle or ID)
}