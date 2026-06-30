// FUNC_NAME: SomeManager::processObjectRange
// Function address: 0x005a3830
// Role: Iterates over array of objects (size 0x20), processes each via two functions, and copies a field (offset 0x1c) to destination array.
// Parameters (unusual calling convention: start in EAX, end in ECX, dest in EDX)
// Returns new destination pointer (past last copied field).

typedef void (__cdecl *FreeFuncType)(void*);
extern FreeFuncType g_freeFunc; // Dereferenced from DAT_0119caf4

// Forward declarations of helper functions
void __cdecl processObject(void* obj);                // FUN_005a0a00
void __cdecl postProcess(void);                        // FUN_005a1060

void* __fastcall processObjectRange(void* pEnd, void* pDest, void* pStart)
{
    void* pCurrent = pStart;
    if (pCurrent == pEnd)
        return pDest;

    do
    {
        void* pNextDest = (char*)pDest + 0x20;
        
        // Process the current object
        processObject(pCurrent);
        postProcess();

        // Temporary stack buffer handling (possibly for scoped allocation)
        {
            char stackBuffer[16]; // local_10
            void* tmpPtr = nullptr; // local_14, originally stored as undefined1 *

            // Conditionally free temporary object if it was allocated elsewhere
            if (tmpPtr != (void*)stackBuffer && tmpPtr != nullptr)
                g_freeFunc(tmpPtr);
        }

        // Copy a field at offset 0x1c from source to destination
        *(int*)((char*)pDest + 0x1c) = *(int*)((char*)pCurrent + 0x1c);

        pDest = pNextDest;
        pCurrent = (char*)pCurrent + 0x20;
    } while (pCurrent != pEnd);

    return pDest;
}