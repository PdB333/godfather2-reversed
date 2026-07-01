// FUNC_NAME: eastl::vector::insert

#include <cstring> // for memmove

// Forward declarations for EASTL allocation functions (from the game binary)
void* eastl_allocate(size_t size);
void eastl_deallocate(void* ptr);

struct Vector {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* capacity; // +0x08
};

void __thiscall Vector::insert(Vector* this, int* pos, int* value) {
    int* endPtr = this->end;
    
    // If there is room for one more element
    if (endPtr != this->capacity) {
        // If the value pointer is inside the vector and will be invalidated by the shift,
        // adjust it to point to the same logical element after the shift.
        if (pos <= value && value < endPtr) {
            value = value + 1;
        }
        
        // Copy the last element one slot to the right (to the current end position)
        if (endPtr != nullptr) {
            *endPtr = *(endPtr - 1);
        }
        
        // Shift elements from 'pos' to one before the end to the right by one slot.
        // The destination is endPtr - (number of bytes to shift), which equals pos + 4.
        size_t shiftSize = (size_t)((int)endPtr - 4 - (int)pos); // bytes from pos to (end-1)
        memmove((void*)((int)endPtr + ((int)(shiftSize / 4) * -4)), pos, shiftSize);
        
        // Insert the new value at the vacated position
        *pos = *value;
        
        // Update the end pointer
        this->end = endPtr + 1;
    } else {
        // Need to grow the vector
        int elemCount = (int)((int)endPtr - (int)this->begin) / 4; // number of elements
        int newElemCount = (elemCount == 0) ? 1 : (elemCount * 2);
        
        // Allocate new buffer (EASTL allocator, called with debug info)
        int* newBuffer = (int*)eastl_allocate(newElemCount * 4);
        
        // Copy elements before the insertion point
        size_t beforeBytes = (int)pos - (int)this->begin;
        memmove(newBuffer, this->begin, beforeBytes);
        
        // Place the new value at the insertion point
        int* insertPos = (int*)((int)newBuffer + beforeBytes);
        *insertPos = *value;
        
        // Copy elements after the insertion point
        size_t afterBytes = (int)this->end - (int)pos;
        memmove(insertPos + 1, pos, afterBytes);
        
        // Deallocate old buffer
        if (this->begin != nullptr) {
            eastl_deallocate(this->begin);
        }
        
        // Update vector metadata
        this->begin = newBuffer;
        this->end = (int*)((int)insertPos + afterBytes + 4);
        this->capacity = newBuffer + newElemCount;
    }
}