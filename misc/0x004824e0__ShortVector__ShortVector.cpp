// FUNC_NAME: ShortVector::ShortVector
// Reconstructed constructor for a dynamic array of shorts (int16). 
// Allocates an initial capacity, sets vtable pointer, and stores global singleton.
// Fields:
// +0x00: vtable pointer
// +0x04: data (pointer to array of shorts)
// +0x08: size (number of elements)
// +0x0C: capacity (allocated elements)
// +0x10: reserved? (unused, set to 0)
// +0x14: reserved?
// +0x18: reserved?
// +0x1C: reserved?
// +0x20: reserved?
// +0x24: reserved?
ShortVector * __fastcall ShortVector::ShortVector(ShortVector *this)
{
    // Store global singleton pointer (unique this for the singleton instance)
    g_pShortVectorSingleton = this;

    // Set vtable pointer
    this->vtable = &kShortVectorVtable;

    // Initialize fields to zero
    this->data = 0;       // +0x04
    this->size = 0;       // +0x08
    this->capacity = 0;   // +0x0C
    this->field_0x10 = 0; // +0x10
    this->field_0x14 = 0; // +0x14
    this->field_0x18 = 0; // +0x18
    this->field_0x1c = 0; // +0x1C
    this->field_0x20 = 0; // +0x20
    this->field_0x24 = 0; // +0x24

    // If size equals capacity, we need to grow (though size==0, capacity==0, so this will trigger)
    if (this->size == this->capacity)
    {
        int newCapacity;
        if (this->capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = this->capacity * 2;
        }
        ShortVector_realloc(newCapacity); // Reallocate with new capacity (this is likely a static/global helper that modifies this's data/capacity)
    }

    // Append a new short element at the end and set it to 0
    short *elementPtr = (short *)(this->data + this->size);
    this->size++;
    if (elementPtr != 0)
    {
        *elementPtr = 0;
    }

    return this;
}