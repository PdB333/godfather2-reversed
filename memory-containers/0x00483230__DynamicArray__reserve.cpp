// FUNC_NAME: DynamicArray::reserve

void DynamicArray::reserve(uint newCapacity)
{
    // Structure fields: (this = ESI)
    // +0x00 void* data;       // pointer to array elements, each 16 bytes
    // +0x04 int count;        // number of elements
    // +0x08 int capacity;     // allocated capacity (number of elements that fit in buffer)

    if (this->capacity < newCapacity) {
        // Allocate new buffer: size = newCapacity * sizeof(Element) = newCapacity * 16
        void* newData = allocMem(newCapacity * 16);
        if (this->data != nullptr) {
            // Copy existing elements from old buffer to new buffer
            uint i = 0;
            if (this->count != 0) {
                int srcOffset = 0;
                for (;;) {
                    // Copy 16-byte element
                    if (newData != nullptr) {
                        ((undefined8*)newData)[srcOffset/8] = ((undefined8*)this->data)[srcOffset/8];
                        ((undefined8*)newData)[srcOffset/8 + 1] = ((undefined8*)this->data)[srcOffset/8 + 1];
                    }
                    i++;
                    if (i >= (uint)this->count)
                        break;
                    srcOffset += 16;
                }
            }
            // Free old buffer
            freeMem(this->data);
        }
        // Update fields
        this->data = newData;
        this->capacity = newCapacity;
    }
}