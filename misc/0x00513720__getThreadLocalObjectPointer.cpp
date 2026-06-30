// FUNC_NAME: getThreadLocalObjectPointer
int __fastcall getThreadLocalObjectPointer(int* pOffset)
{
    int result = 0;
    if (*pOffset != 0) {
        // FS:[0x2C] is the TLS array pointer (Thread Local Storage slots)
        // Slot index 2 (offset 8) holds a pointer to a global per-thread structure.
        // Dereference that structure's first pointer (vtable? base?) then add the offset.
        int tlsArray = *(int*)(__readfsdword(0x2C));
        result = *(int*)(*(int*)(tlsArray + 8)) + *pOffset;
    }
    return result;
}