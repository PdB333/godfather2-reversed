// FUNC_NAME: SomeClass::processPendingOperations
void __fastcall SomeClass::processPendingOperations(void* this)
{
    // Check if bitmask at offset +0xD4->+0x10 has any of the flags 0x4480000 set
    // Assuming field_0xD4 points to a structure with flags at +0x10
    if ((*(uint32_t*)(*(uint32_t*)((uint32_t)this + 0xD4) + 0x10) & 0x4480000) == 0)
    {
        int32_t count = *(int32_t*)((uint32_t)this + 0xD8); // +0xD8: number of iterations
        for (int32_t i = 0; i < count; i++)
        {
            FUN_00577b30(*(uint32_t*)((uint32_t)this + 0xD4)); // process with main context
            FUN_00414aa0(); // presumably some system call (e.g., memory allocation?)
            FUN_00414aa0(); // second call
        }
    }
}