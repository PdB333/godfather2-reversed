// FUNC_NAME: OwnedList::DestroyAll
void __fastcall OwnedList::DestroyAll(uint* thisPtr)
{
    int* current = (int*)*thisPtr;          // +0x00: head of linked list
    while (current != nullptr)
    {
        int* next = (int*)current[7];      // +0x1C: next pointer (7*4)
        // Free sub-objects within node
        if (current[3] != 0)               // +0x0C: some pointer
        {
            FreeMemory((uint*)(current + 3)); // FUN_004daf90
        }
        if (*current != 0)                 // +0x00: first pointer
        {
            FreeMemory((uint*)current);    // FUN_004daf90
        }
        // Call virtual destructor/release on node (vtable offset +4)
        (*(void (__thiscall**)(int*, int))thisPtr[4])(current, 0);
        current = next;
    }
    // Clean up extra pointer if present
    if (thisPtr[3] != 0)                   // +0x0C: extra pointer
    {
        (*(void (__thiscall**)(uint, int))thisPtr[4])(thisPtr[3], 0);
    }
    // Call virtual destructor of container (vtable offset +0xC)
    (*(void (__thiscall**)())thisPtr[4])();
}
// FreeMemory is likely engine's deallocation (FUN_004daf90)