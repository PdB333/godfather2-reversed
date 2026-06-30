// FUNC_NAME: ScriptVM::pushThreeArgs
void __fastcall ScriptVM::pushThreeArgs(uint param_2, uint param_3, uint param_4) {
    // Global script state (offset 0x14 = stack pointer)
    char* state = (char*)gScriptState; // DAT_01206880

    // Get current stack top pointer from state+0x14
    uint** stackTopPtr = (uint**)(state + 0x20); // 0x14? wait offset 0x14
    // Actually offset 0x14 is a pointer to pointer? Let's recalc:
    // iVar1 = DAT_01206880; offset 0x14 points to a pointer that we treat as stack top.
    uint** pStackTop = (uint**)(state + 0x14);
    uint* stackTop = *pStackTop;

    // First operation: set the value at stackTop to a static function table pointer
    *stackTop = &PTR_LAB_01126b18; // function pointer table

    // Advance stack top by 4 bytes (one element)
    stackTop = (uint*)((char*)stackTop + 4);

    // Align to 4-byte boundary (round up)
    stackTop = (uint*)(((uint)stackTop + 3) & ~3);

    // Store param_2 at aligned address
    *stackTop = param_2;
    stackTop = (uint*)((char*)stackTop + 4);

    // Align again
    stackTop = (uint*)(((uint)stackTop + 3) & ~3);

    // Store param_3
    *stackTop = param_3;
    stackTop = (uint*)((char*)stackTop + 4);

    // Align again
    stackTop = (uint*)(((uint)stackTop + 3) & ~3);

    // Store param_4
    *stackTop = param_4;
    stackTop = (uint*)((char*)stackTop + 4);

    // Update the stack top pointer in state
    *pStackTop = stackTop;
}