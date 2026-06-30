// FUNC_NAME: processAllChildren
void processAllChildren(void* thisPtr, uint param_2)
{
    // param_1 (this) is a pointer to an object with two fields:
    // +0x34: pointer to a structure containing element count at offset +0xc (ushort)
    // +0x38: pointer to an array of pointers to child objects (index 0 unused)
    void** countInfo = *(void***)(thisPtr + 0x34);
    void** objects   = *(void***)(thisPtr + 0x38);

    if (countInfo != nullptr && objects != nullptr)
    {
        // The count is stored as ushort at offset +0xc from countInfo, plus 1 (index 0 is sentinel)
        ushort count = *(ushort*)(countInfo + 0xc) + 1;

        // Loop starts at 1 because index 0 is unused/sentinel
        for (uint i = 1; i < count; i++)
        {
            void* child = objects[i];
            if (child != nullptr)
            {
                // Call virtual function at vtable offset 0x14 (e.g., update/notify)
                void (**vtable)(void*, uint) = *(void (***)(void*, uint))child;
                vtable[5](child, param_2); // 0x14 / 4 = 5
            }
        }
    }
}