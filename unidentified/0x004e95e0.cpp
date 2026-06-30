// Function address: 0x004e95e0
// Role: Calls a function pointer stored in a global table at offset 0x28, with swapped parameters. Acts as a safe wrapper returning 0 if the pointer is null.
// Uses __fastcall: param_1 (ecx) and param_2 (edx) are swapped when calling the target function.

typedef int (__cdecl *TableFunc)(int paramA, int paramB); // Likely calling convention; adjust if known.

int __fastcall safeCallGlobalTableOffset28(int param_1, int param_2)
{
    // Global pointer to some structure (likely a function dispatch table)
    // DAT_012234c4 -> g_pSomeGlobalTable
    extern void* g_pSomeGlobalTable; // +0x28 contains function pointer

    if (g_pSomeGlobalTable != nullptr)
    {
        // Retrieve function pointer at offset 0x28
        TableFunc func = *(TableFunc*)((unsigned char*)g_pSomeGlobalTable + 0x28);
        if (func != nullptr)
        {
            // Call with swapped arguments: param_2 first, param_1 second
            return func(param_2, param_1);
        }
    }
    return 0;
}