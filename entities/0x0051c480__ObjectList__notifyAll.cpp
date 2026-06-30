// FUNC_NAME: ObjectList::notifyAll
void ObjectList::notifyAll(int data)
{
    // m_count at +0x80 (short), number of items
    short count = *(short *)((char *)this + 0x80);
    if (0 < count)
    {
        // m_items at +0xf4, array of Item structures (20 bytes each)
        // First element at each offset is a pointer to an object
        int *itemPtr = (int *)((char *)this + 0xf4);
        for (int i = 0; i < count; i++)
        {
            int *objectPtr = itemPtr; // dereference to get object pointer
            if (*objectPtr != 0)
            {
                // Call virtual method at vtable+0x34 on the object
                void (*func)(int) = (void (*)(int))(*(int *)(*(int *)*objectPtr + 0x34));
                func(data);
            }
            itemPtr += 5; // advance by 20 bytes (5 ints)
        }
    }
}