// FUNC_NAME: getThreadLocalIndexedValue
int __fastcall getThreadLocalIndexedValue(void* thisPtr)
{
    // FS:[0x2C] typically points to a per-thread data structure (e.g., TEB or custom TLS table)
    // Dereference twice with offset +8 to get the base of a global object.
    // Then add 0x7c + index (from thisPtr+0x18) to read an int.
    int* pGlobalBase = *(int**)(*(int*)(__readfsdword(0x2C)) + 8);
    int index = *(int*)((char*)thisPtr + 0x18);  // offset 0x18 – likely an index into an array
    return *(int*)((char*)pGlobalBase + 0x7c + index * 4); // assuming 4-byte elements at base+0x7c
}