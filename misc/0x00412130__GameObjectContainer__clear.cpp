// FUNC_NAME: GameObjectContainer::clear
// Address: 0x00412130
extern void __cdecl FUN_009c8f10(void* ptr);
extern void __cdecl FUN_009c8eb0(void* ptr);

void __thiscall GameObjectContainer::clear()
{
    // this + 0x20C: pointer to array of entry pointers
    // this + 0x210: count of entries
    // this + 0x214: capacity (reset to 0 at end)
    int** entryArray = *(int***)(this + 0x20C);
    int count = *(int*)(this + 0x210);
    int** end = entryArray + count;

    for (int** current = entryArray; current != end; ++current)
    {
        int* entry = *current;
        if (entry != nullptr)
        {
            // entry[6] (offset 0x18): pointer to reference counted object
            int* refObj = (int*)entry[6];
            // refObj[0] : reference count
            (*refObj)--;

            if (*refObj == 0)
            {
                // Call virtual destructor via vtable at refObj[0x43] (offset 0x10C),
                // virtual function at vtable + 0x18 (index 6)
                (**(void (**)(int*))(*(int*)refObj[0x43] + 0x18))(refObj);
            }

            // entry[7] (offset 0x1C): another pointer to free
            if (entry[7] != 0)
            {
                FUN_009c8f10((void*)entry[7]);
            }

            // entry[0] : some object pointer, entry[3] : destruction callback
            if (*entry != 0)
            {
                void (*destroyCallback)(int) = (void (*)(int))entry[3];
                destroyCallback(*entry);
            }

            // Free the entry structure itself
            FUN_009c8eb0(entry);
        }
    }

    // Reset container state
    *(int*)(this + 0x210) = 0;  // count = 0
    FUN_009c8f10(*(void**)(this + 0x20C));  // free the array buffer
    *(int*)(this + 0x20C) = 0;   // pointer = null
    *(int*)(this + 0x214) = 0;   // capacity = 0
}