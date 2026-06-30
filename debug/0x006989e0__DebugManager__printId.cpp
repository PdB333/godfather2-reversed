//FUNC_NAME: DebugManager::printId
void __fastcall DebugManager::printId(int thisPtr) {
    char buffer[260];
    // Compute an ID from object fields: offset +0x34 is an index, offset +0x4 is a base offset
    // Accesses an array element at (index * 0x504 + 0x40 + baseOffset)
    uint32_t id = *(uint32_t*)(*(int*)(thisPtr + 0x34) * 0x504 + 0x40 + *(int*)(thisPtr + 4));
    _sprintf(buffer, "%u", id);
    // Likely a debug output function
    FUN_004d3bc0(buffer);

    // SEH try block placeholder (local_114 and pcStack_10c are compiler-generated)
    // The actual work is the virtual call on a global singleton
    (**(code**)(*DAT_01129828 + 0x40))(); // Virtual function at vtable+0x40

    // Cleanup for SEH (always executed)
    if (local_114 != 0) {
        (*pcStack_10c)(local_114);
    }
}