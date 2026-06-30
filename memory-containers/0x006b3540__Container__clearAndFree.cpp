// FUNC_NAME: Container::clearAndFree
void __fastcall Container::clearAndFree()
{
    // Container struct (offset 0: array pointer, +4: count)
    // Array contains 8-byte elements, first 4 bytes are a pointer or identifier
    int index = this->count;
    while (--index >= 0)
    {
        // Check if element is valid (non-zero first field)
        if (*(int*)((char*)this->array + index * 8) != 0)
        {
            // Call destructor on the element
            DestroyElement((char*)this->array + index * 8);
        }
    }
    // Free the array buffer
    if (this->array != 0)
    {
        operatorDelete(this->array);
    }
}