// FUNC_NAME: DebugConsole::printUInt
void __thiscall DebugConsole::printUInt(DebugConsole* this) {
    char buffer[260]; // For sprintf output
    uint value = *(uint*)( (*(int*)((uintptr_t)this + 0x34) * 0x504) + 0x40 + *(int*)((uintptr_t)this + 4) );
    _sprintf(buffer, "%u", value); // Format unsigned integer
    outputString(buffer); // Send string to output system (FUN_004d3bc0)

    // Virtual call to global debug console singleton (offset 0x40 in vtable)
    gDebugConsole->flushOutput(); // (*(code**)(*(uintptr_t*)DAT_01129828 + 0x40))()

    // The stack buffer and destructor call below likely represent a scope guard
    // that cleans up after flushOutput, but pcStack_10c is uninitialized.
    // Omitted due to missing constructor data.
}