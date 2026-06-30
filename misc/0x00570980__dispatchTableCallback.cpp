// FUNC_NAME: dispatchTableCallback
void __cdecl dispatchTableCallback(int index, void* param)
{
    // Global dispatch table base and count
    // DAT_01205570: base address of dispatch table (array of 12-byte entries)
    // DAT_01205574: number of entries in table
    extern int g_dispatchTableCount;  // DAT_01205574
    extern DispatchEntry* g_dispatchTable; // DAT_01205570

    // Check if index is valid: -1 is allowed (maybe sentinel), otherwise 0..count-1
    if ((index >= -1) && (index < g_dispatchTableCount))
    {
        // Each entry is 12 bytes; function pointer is at offset 4
        void (*handler)(void*) = *(void (**)(void*))((char*)g_dispatchTable + 4 + index * 12);
        if (handler != nullptr)
        {
            handler(param);
        }
    }
}