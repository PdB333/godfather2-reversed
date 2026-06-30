// FUNC_NAME: EAString::reserve
//
// Reconstructs the function at 0x004d3fe0 which is a member function of a string-like class.
// The class layout: 
//   +0x00: char* data (pointer to character buffer)
//   +0x04: size_t length (number of characters without null terminator)
//   +0x08: size_t capacity (allocated buffer size, excluding null)
//   +0x0C: void (*deallocate)(void*) (deallocation function pointer, typically operator delete[])
//
// This function ensures the capacity is at least newCapacity.
// If current capacity < newCapacity, it allocates a new buffer of size newCapacity+1,
// copies existing data, null-terminates, deallocates the old buffer, and updates the object.

void __thiscall EAString::reserve(EAString* this, size_t newCapacity)
{
    char* newData;
    char* oldData;

    if (this->capacity < newCapacity)
    {
        if (this->data != nullptr)
        {
            // Allocate new buffer (size newCapacity+1 to include null terminator)
            newData = (char*)FUN_009c8e50(newCapacity + 1);  // likely operator new[] (size_t)
            // Copy existing data (length bytes)
            _memcpy(newData, this->data, this->length);
            // Null-terminate
            newData[this->length] = '\0';
            // Deallocate old buffer using stored function pointer
            if (this->data != nullptr)
            {
                this->deallocate(this->data);  // calls FUN_009c8eb0 (operator delete[])
            }
            // Update object
            this->data = newData;
            this->capacity = newCapacity;
            this->deallocate = (void (*)(void*))thunk_FUN_009c8eb0;  // set deallocator to operator delete[]
            return;
        }
        // If data is null, simply allocate a new empty buffer
        newData = (char*)FUN_009c8e50(newCapacity + 1);
        this->data = newData;
        newData[0] = '\0';
        this->deallocate = (void (*)(void*))thunk_FUN_009c8eb0;
        this->capacity = newCapacity;
    }
    // else: capacity already sufficient, nothing to do
}