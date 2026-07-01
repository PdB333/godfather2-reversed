//FUNC_NAME: getOwnerPointer
// Function at 0x0078e110: Simple getter returning a pointer stored at offset 0x1c (likely owner/parent pointer)
void* __fastcall getOwnerPointer(void* thisPtr) {
    return *(void**)((char*)thisPtr + 0x1c);
}