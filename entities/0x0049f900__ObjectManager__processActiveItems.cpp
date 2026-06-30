// FUNC_NAME: ObjectManager::processActiveItems
// Address: 0x0049f900
// Role: Iterates over an internal array of object pointers and calls a handler on those with an active flag set (bit 0 at +0xB2).

void __thiscall ObjectManager::processActiveItems(int param1, int param2)
{
    // +0x8C: pointer to array of object pointers (int**)
    int** arrayBase = *reinterpret_cast<int***>(this + 0x8C);
    // +0x90: count of elements in the array
    int count = *reinterpret_cast<int*>(this + 0x90);
    if (count == 0) return;

    int** end = arrayBase + count;
    for (int** it = arrayBase; it != end; ++it)
    {
        void* object = *reinterpret_cast<void**>(it);
        // Check active flag at +0xB2 (bit 0)
        if ((*reinterpret_cast<unsigned char*>(object) + 0xB2) & 1) != 0)
        {
            // Call the handler with the same two parameters passed to this function
            invokeHandler(param1, param2);
        }
    }
}