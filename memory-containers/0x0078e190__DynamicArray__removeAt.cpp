// FUNC_NAME: DynamicArray::removeAt
void __thiscall DynamicArray::removeAt(uint index)
{
    // Check if index is within range and not the last element
    if (index < this->count - 1U)
    {
        // Shift elements left by one starting from index
        do
        {
            this->array[index] = this->array[index + 1];
            index = index + 1;
        } while (index < this->count - 1U);
    }
    // Decrement the count (shortens the array)
    this->count = this->count - 1;
    return;
}