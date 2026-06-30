// FUNC_NAME: GenericContainer::clearElements
// Address: 0x006bccd0
// Role: Releases all elements in an array of 8-byte structs, then frees the array itself.
// The container holds:
//   +0x00: pointer to array of Element (8 bytes each)
//   +0x04: count of elements
//   +0x08: unknown flag (cleared to 0)

struct Element {
    void* ptr;      // +0x00
    int field4;     // +0x04 (unused)
};

void __thiscall GenericContainer::clearElements(void)
{
    int count = this->count;                    // param_1[1]
    Element* elements = (Element*)this->basePtr; // *param_1

    // Iterate from end to start
    for (int i = count - 1; i >= 0; i--) {
        if (elements[i].ptr != 0) {
            // Call destructor/release on the element address
            FUN_004daf90(&elements[i]);
        }
    }

    // Reset count
    this->count = 0;

    // Free the array memory
    FUN_009c8f10(this->basePtr);

    // Clear pointers and flags
    this->basePtr = 0;
    this->unknown = 0;
}