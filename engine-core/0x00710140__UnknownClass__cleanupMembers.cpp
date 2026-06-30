// FUNC_NAME: UnknownClass::cleanupMembers
void __thiscall cleanupMembers(int thisPtr) {
    // Release sub-object at offset 0xb0 if allocated
    if (*(void**)(thisPtr + 0xb0) != nullptr) {
        // FUN_004daf90 likely deallocates or releases the resource
        FUN_004daf90(thisPtr + 0xb0);
    }
    // Release sub-object at offset 0x9c via stored destructor function pointer
    if (*(void**)(thisPtr + 0x9c) != nullptr) {
        // The function pointer at offset 0xa8 is a custom deleter or virtual destructor
        (*(void(__thiscall**)(void*))(thisPtr + 0xa8))(*(void**)(thisPtr + 0x9c));
    }
}