// FUNC_NAME: DynamicArray::removeAt
void __thiscall DynamicArray::removeAt(unsigned int index)
{
    // this[0] = data pointer (int*)
    // this[1] = count (number of elements)
    int *data = (int *)this[0];
    int count = this[1];

    // Shift elements left only if index is not the last element
    if (index < (unsigned int)(count - 1))
    {
        do {
            data[index] = data[index + 1];
            ++index;
        } while (index < (unsigned int)(count - 1));
    }

    // Decrement the element count
    this[1] = count - 1;
}