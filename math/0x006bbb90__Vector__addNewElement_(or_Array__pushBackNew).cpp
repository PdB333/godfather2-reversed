// FUNC_NAME: Vector::addNewElement (or Array::pushBackNew)
// Address: 0x006bbb90
// This function implements a dynamic array (vector) with element size 0x18 (24 bytes).
// It adds a new element, growing the array if necessary, and returns a pointer to the new slot.
// The new element is initialized with debug sentinel values to detect uninitialized use.

#include <cstdint>

// The struct representing an element in the vector (size 24 bytes).
// In the real game, this is likely a class with a vtable or members.
struct Element {
    uint32_t field_0;      // +0x00
    uint32_t field_4;      // +0x04
    uint32_t field_8;      // +0x08
    uint32_t field_C;      // +0x0C
    uint32_t field_10;     // +0x10
    uint32_t field_14;     // +0x14
};

// The vector data structure.
// Fields are at offsets from the 'this' pointer.
struct Vector {
    Element* data;         // +0x00: pointer to allocated array
    int size;              // +0x04: number of elements currently stored
    int capacity;          // +0x08: total capacity (max elements before reallocation)
};

// __fastcall: ecx = this, no other parameters.
Element* __fastcall Vector::addNewElement(Vector* this) __attribute__((regparm(1)))
{
    if (this->size == this->capacity) {
        // Need to grow the array.
        int newCapacity;
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        // Reallocate the array to hold 'newCapacity' elements.
        // This function (FUN_006bb3e0) likely handles the actual memory allocation
        // and updates 'data' and 'capacity' accordingly.
        FUN_006bb3e0(newCapacity);  // reallocation function
    }

    // Get pointer to the next free slot.
    Element* newSlot = &this->data[this->size];

    if (newSlot != nullptr) {
        // Initialize the new element with debug sentinel values.
        // These magic numbers are typical of EA's debug builds to catch uninitialized data.
        newSlot->field_0 = 0;
        newSlot->field_4 = 0;
        newSlot->field_8 = 0xBADBADBA;
        newSlot->field_C = 0xBEEFBEEF;
        newSlot->field_10 = 0xEAC15A55;
        newSlot->field_14 = 0x91100911;
    }

    // Increment the size.
    this->size++;

    // Return the pointer to the newly added element.
    return newSlot;
}