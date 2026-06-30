// FUNC_NAME: ScriptContext::invokeFunction

// Reconstructed C++ for function at 0x004f2b80
// Purpose: Reads 6 DWORD arguments from an internal buffer (offset +0x18) and calls a function pointer with those arguments.
// The buffer pointer is advanced past the read data with alignment to DWORD boundaries.

class ScriptContext {
public:
    // Buffer pointer at offset +0x18 (points to packed argument data)
    unsigned char* m_pArgs;  // +0x18

    // Invokes a function with arguments unpacked from the internal buffer.
    // param_1: this (ScriptContext*)
    // param_2: function pointer to call (void (*)(...))
    void invokeFunction(void (*func)(int, int, int, int, int, int)) {
        // Read the first argument directly from the current buffer position
        int arg1 = *(int*)m_pArgs;

        // Advance the buffer pointer past the first argument, aligning to next DWORD boundary
        unsigned char* alignedPtr = (unsigned char*)((int)(m_pArgs) + 7) & 0xFFFFFFFC;
        m_pArgs = alignedPtr;

        // Read the remaining 5 arguments from the aligned position
        int arg2 = *(int*)alignedPtr;
        int arg3 = *(int*)(alignedPtr + 4);
        // Read 8-byte value (two DWORDs) for arg4 and arg5
        long long arg4_5 = *(long long*)(alignedPtr + 8);
        int arg4 = (int)(arg4_5 & 0xFFFFFFFF);
        int arg5 = (int)(arg4_5 >> 32);
        int arg6 = *(int*)(alignedPtr + 16);

        // Call the provided function with the unpacked arguments
        func(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};