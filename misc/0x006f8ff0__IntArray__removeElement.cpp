// FUNC_NAME: IntArray::removeElement
void __thiscall IntArray::removeElement(int* this, uint index)
{
    // this[0] = pointer to data array (int*)
    // this[1] = count (number of elements)
    int* data = (int*)this[0];
    int count = this[1];

    if (index < count - 1)
    {
        // Shift elements left from index+1 to end-1
        do
        {
            data[index] = data[index + 1];
            index++;
        } while (index < count - 1);
    }

    // Decrement the count
    this[1] = count - 1;
}