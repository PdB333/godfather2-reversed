// FUNC_NAME: ObjectList::findByID

// This function performs a linear search through an array of fixed-size elements (0x34 bytes each)
// to find an element whose ID field (at offset +0x8 within the element) matches the given key.
// Returns a pointer to the matching element, or nullptr if not found.

// Class structure:
// +0x00: vtable?
// +0x04: mArray (pointer to start of element array)
// +0x08: mCount (number of valid elements)

// Element structure (size 0x34 = 52 bytes):
// +0x00: ? (8 bytes of unknown)
// +0x08: id (int32 key)
// +0x0C ... remainder (44 bytes)

int* __thiscall ObjectList::findByID(int* thisPtr, int key)
{
    uint elementCount = thisPtr[2];      // +0x08: count of elements
    if (elementCount == 0) {
        return nullptr;
    }

    char* elementArray = (char*)thisPtr[1]; // +0x04: pointer to first element
    for (uint i = 0; i < elementCount; i++) {
        int* element = (int*)(elementArray + i * 0x34);
        if (element[2] == key) {           // +0x08: ID field within element
            return element;
        }
    }
    return nullptr;
}