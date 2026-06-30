// FUNC_NAME: DynamicArray::reserve

void __thiscall DynamicArray::reserve(DynamicArray* this, unsigned int newCapacity)
{
    int* oldPointer;
    unsigned int oldSize;
    int* newPointer;
    unsigned int i;

    if (this->capacity < newCapacity)
    {
        // Allocate new memory block
        newPointer = (int*)allocateMemory(newCapacity * 4);
        if (this->pointer != 0)
        {
            // Copy existing elements
            oldSize = this->size;
            i = 0;
            while (i < oldSize)
            {
                if (newPointer != 0)
                {
                    newPointer[i] = this->pointer[i];
                }
                i++;
            }
            // Free old memory
            freeMemory(this->pointer);
        }
        // Update pointer and capacity
        this->pointer = newPointer;
        this->capacity = newCapacity;
    }
}