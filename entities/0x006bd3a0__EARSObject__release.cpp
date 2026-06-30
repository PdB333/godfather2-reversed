// FUNC_NAME: EARSObject::release
void EARSObject::release()
{
    // Decrement reference count; if it goes negative, destroy and unlink
    int refCountResult = RefCountDecrement(this); // FUN_006bcfa0
    if (refCountResult < 0)
    {
        // The embedded node at offset 0x48 is used for list management
        int* node = (this != nullptr) ? reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x48) : nullptr;
        int savedPrev = 0;
        if (node != nullptr)
        {
            // Save the previous pointer and then override it with the address of the stack variable
            // This is a temporary unlink from a local list head
            savedPrev = *(node + 1);               // node->prev at offset +4
            *(reinterpret_cast<int**>(node + 1)) = &node; // set node->prev to &node (head of temporary list)
        }
        // Finalize removal from the main list
        CompleteListUnlink(&node); // FUN_006bd130
        // Free the object if still valid after unlink
        if (node != nullptr)
        {
            FreeObjectMemory(&node); // FUN_004daf90
        }
    }
}