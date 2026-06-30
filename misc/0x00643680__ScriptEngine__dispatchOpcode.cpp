// FUNC_NAME: ScriptEngine::dispatchOpcode
// Address: 0x00643680
// Processes an opcode with two arguments and writes the result (type + value) to a buffer pointed by EDI.
// The caller is responsible for setting EDI to a writable two-DWORD buffer.

void __fastcall ScriptEngine::dispatchOpcode(int thisObj, uint arg1, int opcode, uint arg2)
{
    uint temp;
    uint result;
    uint32_t* outputBuffer; // In asm, this is the EDI register (not a formal parameter)

    if (opcode > 4)
    {
        // Complex opcodes: 5..9 swap arguments; 10+ keep order
        if (opcode < 10)
        {
            temp = arg2;
            arg2 = arg1;
            arg1 = temp;
        }
        // Lookup function pointer from a table at base+opcode*4+0xC
        // (Ghidra placeholder: "function or expression too complex")
        uint fptr = *(uint*)((uint)"function or expression too complex" + opcode * 4 + 0xC);
        result = resolveComplexOp(fptr, arg1, arg2); // CALL FUN_006424f0
        outputBuffer[0] = 9;   // Result type 9
        outputBuffer[1] = result;
    }
    else
    {
        // Simple opcodes 0..4: pack arguments and call helper
        uint packed = ((arg1 << 9) | arg2) << 6 | (opcode + 0xC);
        // thisObj+0xC points to a context object; context+8 holds a parameter
        uint contextArg = *(uint*)(*(uint*)(thisObj + 0xC) + 8);
        result = resolveSimpleOp(packed, contextArg); // CALL FUN_006438e0
        outputBuffer[0] = 10;  // Result type 10
        outputBuffer[1] = result;
    }
}
```