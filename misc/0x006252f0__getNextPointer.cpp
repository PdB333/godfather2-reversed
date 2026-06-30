// FUNC_NAME: getNextPointer
// Function at 0x006252f0 - returns pointer at offset 0x4 (likely next node in a linked list)
void* __fastcall getNextPointer(void* thisPtr)
{
    return *(void**)((char*)thisPtr + 4);
}