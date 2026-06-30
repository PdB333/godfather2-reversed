// FUNC_NAME: BankStream::loadBank

// Function address: 0x005a2870
// Role: Loads a bank stream (BNK) from a file into a shared buffer.
// Parameters:
//   outBuffer: output pointer to the loaded buffer (reference counted)
//   unkParam2: unused? (possibly flags or size)
//   unkParam3: unused?
//   filePath: the file path to load

#include <cstdint>

// Forward declarations of helper functions (from decompiled symbols)
extern void* operator new(uint32_t size, int zero);  // allocator
extern void operator delete(void* ptr);               // deallocator
extern void* malloc(uint32_t size);                   // low-level alloc
extern void free(void* ptr);                          // low-level dealloc

extern bool streamOpen(int handle, const char* path, bool flag1, bool flag2);
extern int streamRead(int handle, int offset, const char* buffer, int size, int unk);
extern bool streamIsValid(int handle);

extern void bufferInit();
extern bool bufferIsLoaded();

extern int** getObjectPool(void* poolManager);  // returns pointer to pointer container
extern void bufferReleaseRef(int** bufferPtr);
extern void bufferAttach(int** outBuffer, int* src);
extern void bufferClear();
extern void bufferReset();
extern void bufferAddRef(int* buffer);
extern void bufferProcessData(int handle);

extern int* getCriticalSection();  // returns mutex/CS object
extern void lockCriticalSection(int* cs);

extern int* bufferDuplicate(int* src);
extern void bufferSetupDirect(int handle);
extern void bufferFinalizeLoad(int** outBuf);
extern void bufferCleanupLoad();

// Global variables
extern int* g_someConfig;          // DAT_0119caec
extern void* g_freeFunc;           // DAT_0119caf4
extern void* g_freeFuncSize;       // DAT_0119caf8
extern void* g_allocFunc;          // DAT_0119caf0
extern void* g_poolManager;        // DAT_0119a9c8

void BankStream::loadBank(int*& outBuffer, uint32_t unkParam2, uint32_t unkParam3, const char* filePath)
{
    char* localBuffer = nullptr;
    int streamHandle;
    int bufferSize;
    char localStackData[16]; // small buffer for temporary string?
    char* tempStr = (char*)&localStackData; // originally local_14, can point to stack or heap

    // Step 1: Open the file stream and read size
    streamHandle = streamOpen(0, filePath, 1, 1);  // returns a handle
    bufferSize = streamRead(streamHandle, 0, filePath, 1, 1);

    // Step 2: Check if stream is valid and if we can proceed
    if (bufferSize == 0 || !streamIsValid(0))
    {
        // Clean up any allocated tempStr
        if (filePath != (const char*)0x14 && filePath != nullptr)
        {
            free((void*)filePath);
        }
        return;
    }

    // Step 3: Initialize buffer system
    bufferInit();

    // Step 4: Check if already loaded?
    bool alreadyLoaded = bufferIsLoaded();

    // Free the temporary string if it was allocated (not stack)
    if (tempStr != (char*)0x14 && tempStr != (char*)(&localStackData))
    {
        free(tempStr);
    }

    int* sourceBuffer = nullptr;
    int** bufferContainer = nullptr;

    // Step 5: If not already loaded, get a buffer from pool
    if (!alreadyLoaded)
    {
        bufferContainer = (int**)getObjectPool(g_poolManager);
        if (bufferContainer != &sourceBuffer) // &sourceBuffer is a dummy? maybe pointer comparison
        {
            sourceBuffer = *bufferContainer;
            if (sourceBuffer != nullptr)
            {
                sourceBuffer[0]++; // increment ref count
            }
        }

        // Release previous buffer if it existed
        if (outBuffer != nullptr)
        {
            outBuffer[0]--;
            if (outBuffer[0] == 0)
            {
                bufferReleaseRef(&outBuffer);
                // Note: original calls FUN_005a1b40 and then free with size 0x30
            }
        }

        if (sourceBuffer == nullptr)
        {
            // Directly attach the input buffer?
            bufferAttach(&outBuffer, outBuffer);  // seems odd, might be identity
            bufferClear();
            bufferReset();
            sourceBuffer = outBuffer; // local_2c
        }
        else
        {
            sourceBuffer[0]++; // increment ref count
            bufferAddRef(sourceBuffer);
        }
    }

    // Step 6: Lock critical section and set flags
    int* cs = getCriticalSection();
    lockCriticalSection(cs);
    cs[0x16] = 0; // some field
    cs[0] = (cs[0] & 0xFFFF8013) | 0x8013; // set flags

    // Step 7: Process the data with the handle
    bufferProcessData(streamHandle);

    // Step 8: Allocate and set up the final buffer based on outBuffer
    if (outBuffer == nullptr)
    {
        if (sourceBuffer != nullptr)
        {
            int* newBuf = (int*)operator new(0x10, 0); // size 16, zero init? (DAT_0119caf0)
            if (newBuf != nullptr)
            {
                sourceBuffer[0]++; // ref count
                newBuf = (int*)bufferDuplicate(sourceBuffer); // copy?
            }
            if (newBuf != nullptr)
            {
                newBuf[0]++; // ref count
            }
            outBuffer = newBuf;
        }
    }
    else
    {
        bufferSetupDirect(streamHandle);
        if (sourceBuffer != nullptr)
        {
            int* newBuf = (int*)operator new(0x10, 0);
            if (newBuf != nullptr)
            {
                sourceBuffer[0]++;
                newBuf = (int*)bufferDuplicate(sourceBuffer);
            }
            if (newBuf != nullptr)
            {
                newBuf[0]++;
            }
            outBuffer = newBuf;
        }
    }

    // Step 9: Finalize the load process
    bufferFinalizeLoad(&outBuffer);

    // Step 10: Release the temporary source buffer if used
    if (outBuffer != nullptr)
    {
        outBuffer[0]--;
        if (outBuffer[0] == 0)
        {
            bufferCleanupLoad();
        }
    }

    // Step 11: Decrement sourceBuffer ref count and possibly free
    sourceBuffer[0]--;
    if (sourceBuffer[0] == 0)
    {
        bufferReleaseRef(&sourceBuffer);
        free(sourceBuffer); // with size 0x30
    }

cleanup:
    // Step 12: Free original filePath if not null and not stack
    if (filePath != (const char*)0x14 && filePath != nullptr)
    {
        free((void*)filePath);
    }
    return;
}