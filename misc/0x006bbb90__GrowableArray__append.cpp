// FUNC_NAME: GrowableArray::append
// Address: 0x006bbb90
// Role: Appends a new 24-byte element to a growable array, returning pointer to it.
// Initializes element with debug magic: 0, 0, 0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911.

// struct GrowableArray {
//     void* buffer;   // +0x00 pointer to element array
//     int size;       // +0x04 number of elements
//     int capacity;   // +0x08 allocated capacity (in elements)
// };
// Each element is 0x18 bytes.

// __fastcall: this in ECX
void* __fastcall GrowableArray::append(GrowableArray* this)
{
    int newCapacity;

    if (this->size == this->capacity)
    {
        // Need to grow
        if (this->capacity == 0)
            newCapacity = 1;
        else
            newCapacity = this->capacity * 2;
        growableArray_resize(newCapacity); // external resize function (0x006bb3e0)
    }

    // Get pointer to new element (at buffer + size * 24)
    int* newElem = (int*)((char*)this->buffer + this->size * 0x18);
    if (newElem != nullptr)
    {
        // Initialize with debug magic values (first two ints zeroed)
        newElem[0] = 0;
        newElem[1] = 0;
        newElem[2] = 0xBADBADBA;
        newElem[3] = 0xBEEFBEEF;
        newElem[4] = 0xEAC15A55;
        newElem[5] = 0x91100911;
    }

    int oldSize = this->size;
    this->size = oldSize + 1;
    return (char*)this->buffer + oldSize * 0x18;
}