// FUNC_NAME: DynamicArray::removeElement
void __thiscall DynamicArray::removeElement(int element)
{
    uint count = this->m_count; // +0x14
    uint index = 0;
    if (count != 0)
    {
        int* array = this->m_array; // +0x10
        while (*array != element)
        {
            index++;
            array++;
            if (count <= index)
            {
                // Element not found – call vtable callback (offset +0x28) with code 2
                (this->vtable[0x28 / 4])(2);
                return;
            }
        }
        if (index != 0xffffffff)
        {
            if (index != count - 1)
            {
                // Move last element into the removed slot
                this->m_array[index] = this->m_array[count - 1];
            }
            this->m_count = count - 1;
            if (this->m_count == 0)
            {
                this->m_count = 0;
                freeMemory(this->m_array); // FUN_009c8f10
                this->m_array = 0;
                this->m_capacity = 0; // +0x18
            }
        }
    }
    // Always call vtable callback at end
    (this->vtable[0x28 / 4])(2);
}