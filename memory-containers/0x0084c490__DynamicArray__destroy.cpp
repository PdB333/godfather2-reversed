// FUNC_NAME: DynamicArray::destroy
// Function at 0x0084c490: Destructor/cleanup for a dynamic array.
// The container has a pointer to an array of 12-byte elements and a count.
// Iterates from end to start, calling destructor on each valid element (non-zero first field),
// then frees the array memory.

class DynamicArray {
public:
    int* data;    // Pointer to array of elements (each 12 bytes) // +0x00
    int count;    // Number of elements // +0x04
    // Total size: 0x08? Actually this struct size might be larger if it's a derived class,
    // but the function only accesses these two fields.
};

// Element in the array: first field (int) is a validity flag; 0 = empty
struct Element {
    int validFlag;  // +0x00
    int field_4;    // +0x04 (unknown)
    int field_8;    // +0x08 (unknown)
};

// External functions used
void __thiscall destroyElement(Element* elem);  // FUN_004daf90 - destruct single element
void __cdecl deallocateArray(void* ptr);        // FUN_009c8f10 - free array memory

void __thiscall DynamicArray::destroy() {
    int idx = this->count - 1;
    if (idx >= 0) {
        int offset = idx * sizeof(Element); // 0xC = 12 bytes
        do {
            Element* elem = reinterpret_cast<Element*>(reinterpret_cast<char*>(this->data) + offset);
            if (elem->validFlag != 0) {
                destroyElement(elem);
            }
            --idx;
            offset -= sizeof(Element);
        } while (idx >= 0);
    }
    if (this->data != nullptr) {
        deallocateArray(this->data);
    }
}