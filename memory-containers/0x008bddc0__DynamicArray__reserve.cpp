// FUNC_NAME: DynamicArray::reserve
// Address: 0x008bddc0
// Role: Growable array capacity reservation (element size 8 bytes)
// Structure: DynamicArray { int* data; int size; int capacity; } at offsets 0, 4, 8

class DynamicArray {
    int* data;      // +0x00
    int size;       // +0x04
    int capacity;   // +0x08

public:
    // Ensures capacity >= neededCapacity, reallocating if necessary
    void __thiscall reserve(uint neededCapacity) {
        if ((uint)this->capacity < neededCapacity) {
            // Allocate new buffer (8 bytes per element)
            int* newData = (int*)memAlloc(neededCapacity * 8); // FUN_009c8e80

            if (this->data != nullptr) {
                // Copy existing elements (each 8 bytes)
                uint i = 0;
                int* dst = newData;
                if (this->size != 0) {
                    do {
                        if (newData != nullptr) {
                            int* src = this->data;
                            dst[0] = *(src + i * 2);       // copy first int of pair
                            dst[1] = *(src + i * 2 + 1);   // copy second int
                        }
                        i++;
                        dst += 2;
                    } while (i < (uint)this->size);
                }
                // Free old buffer
                memFree(this->data); // FUN_009c8f10
            }

            // Update pointers and capacity
            this->data = newData;
            this->capacity = neededCapacity;
        }
    }
};