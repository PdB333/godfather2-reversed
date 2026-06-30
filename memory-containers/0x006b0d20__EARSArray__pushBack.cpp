// FUNC_NAME: EARSArray::pushBack

// Function at 0x006b0d20
// Dynamic array (vector-like) push back operation
// Fields: data (offset +0x00), size (offset +0x04), capacity (offset +0x08)
void __thiscall EARSArray::pushBack(int* this, int* value)
{
    int size = this[1];
    int capacity = this[2];

    if (size == capacity)
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity = capacity * 2;
        }
        // Reallocate internal buffer to new capacity (modifies this[0] and this[2])
        FUN_006afb30(capacity);
    }

    int* dest = (int*)(this[0] + size * 4);
    this[1] = size + 1;
    if (dest != (int*)0x0)
    {
        *dest = *value;
    }
}