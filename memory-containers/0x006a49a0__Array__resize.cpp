// FUNC_NAME: Array::resize
class Array {
public:
    void* data;  // +0x00: pointer to array of elements (each 0x30 bytes)
    int size;    // +0x04: number of elements currently stored
};

// External function that reallocates the internal buffer to at least newSize elements
void expandArrayStorage(int newSize);  // defined elsewhere (0x006a4790)

// Element vtable pointers (debug sentinels)
extern void* PTR_LAB_00d5d708;  // vtable for "constructed" element
extern void* PTR_LAB_00e2f0c0;  // vtable for "destructed" element

void __thiscall Array::resize(Array* this, int newSize) {
    int oldSize = this->size;

    if (oldSize < newSize) {
        // Need to expand the array
        expandArrayStorage(newSize);
        oldSize = this->size;  // re-read after potential reallocation

        if (oldSize < newSize) {
            // Initialize newly allocated elements
            int offset = oldSize * 0x30;  // element stride
            int count = newSize - oldSize;

            do {
                int* newElement = (int*)((char*)this->data + offset);

                if (newElement != nullptr) {
                    // Debug fill patterns for uninitialized memory
                    newElement[0] = 0xbadbadba;
                    newElement[1] = 0xbeefbeef;
                    newElement[2] = 0xeac15a55;
                    newElement[3] = 0x91100911;
                    newElement[9] = (int)&PTR_LAB_00d5d708;  // +0x24: vtable pointer
                }

                offset += 0x30;
                --count;
            } while (count != 0);

            this->size = newSize;
            return;
        }
    } else if (oldSize > newSize) {
        // Shrinking: destroy elements beyond newSize
        int lastIndex = oldSize - 1;
        int currentIndex = lastIndex;

        if (newSize <= lastIndex) {
            int offset = lastIndex * 0x30;
            int count = (lastIndex - newSize) + 1;

            do {
                // Set vtable to "dead" pointer for each element being removed
                *(void***)((char*)this->data + offset + 0x24) = &PTR_LAB_00e2f0c0;
                offset -= 0x30;
                --count;
            } while (count != 0);
        }
    }

    // If no change, or after shrinking, update size
    this->size = newSize;
    return;
}