// FUNC_NAME: enumerateCurrentProcessThreadIds

#include <windows.h>

// Global callback and data pointers (initialized elsewhere)
extern int DAT_01223130;
extern void* DAT_01223140; // pointer to enumeration function
extern void* DAT_01223144;
extern void* DAT_01223148;

void FUN_0064ad70(void); // initialization helper

uint enumerateCurrentProcessThreadIds(int* threadIdBuffer, uint maxThreadIds)
{
    uint count = 0;

    if (DAT_01223130 == 0)
    {
        FUN_0064ad70(); // initialize enumeration infrastructure
    }

    if (DAT_01223140 != NULL)
    {
        HANDLE hProcess = GetCurrentProcess();
        HANDLE hCurrentThread = GetCurrentThread();

        // Large structure used for enumeration state (size 0x2cc)
        uint8 enumState[0x2cc];
        memset(enumState, 0, sizeof(enumState));
        *(uint32_t*)enumState = 0x10001; // some flag

        // Output structure (size 0xa4) receives thread IDs
        uint8 outputStruct[0xa4];
        memset(outputStruct, 0, sizeof(outputStruct));

        // Pointer to a string at 0x64b0c4 (likely a module name like "KERNEL32.DLL")
        const char* moduleName = (const char*)0x64b0c4;
        *(uint32_t*)outputStruct = (uint32_t)moduleName; 
        *(uint32_t*)(outputStruct + 4) = 3; // count of pointers

        // Another pointer (to enumState) setup
        *(uint8**)(outputStruct + 0x10) = enumState; // offset 0x10
        *(uint32_t*)(outputStruct + 0x14) = 3;       // count

        // Possibly a pointer to outputStruct itself? (offset 0x90?)
        // ... (additional pointer setup omitted for clarity)

        int iteration = 0;
        while (count < maxThreadIds - 1)
        {
            // Callback function with command 0x14c (get next thread)
            int ret = ((int (__cdecl*)(int, HANDLE, HANDLE, void*, void*, int, void*, void*, int))
                        DAT_01223140)(0x14c, hProcess, hCurrentThread, 
                                     outputStruct, enumState, 0, 
                                     DAT_01223144, DAT_01223148, 0);

            if (ret == 0)
                break;

            // Check if pointer inside outputStruct is non-NULL (indicates valid data)
            if (*(uint8**)(outputStruct + 0x90) == NULL)
                break;

            if (iteration > 0)
            {
                // First dword of outputStruct contains thread ID
                threadIdBuffer[count] = *(uint32_t*)outputStruct;
                count++;
            }
            iteration++;
        }

        // Null-terminate the list
        threadIdBuffer[count] = 0;
    }

    return count;
}
```