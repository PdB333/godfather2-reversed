// FUNC_NAME: ObjectManager::ResolveHandle
// Function at 0x00485650: Resolves a handle to a pointer relative to a thread-local base.
// handle is passed in EAX, outOffset is the only explicit stack parameter.
// Returns a pointer derived from thread-local storage offset.

int* __fastcall ObjectManager::ResolveHandle(int handle, int* outOffset)
{
    // Global manager pointer (DAT_0120541c)
    extern ObjectManager* g_pObjectManager; // +0x17c holds sentinel pointer
    // Base address offset (DAT_01205410)
    extern int g_baseOffset;

    int* objectPtr;

    // If handle is not a special sentinel (>= -16 = 0xFFFFFFF0)
    if (handle < 0xFFFFFFF0)
    {
        objectPtr = GetObjectByHandle(g_pObjectManager, handle, 0);
    }
    else
    {
        // Special case: retrieve pointer from manager at offset 0x17C
        objectPtr = *(int**)((int*)g_pObjectManager + 0x5F); // 0x17C / 4 = 0x5F
    }

    if (objectPtr)
    {
        int offset = (int)objectPtr - g_baseOffset;
        *outOffset = offset;

        // Thread-local storage pointer from FS:0x2C
        int* tlsData = *(int**)__readfsdword(0x2C);
        // tlsData[2] is a base address at offset 8
        return (int*)(tlsData[2] + offset);
    }

    return nullptr;
}