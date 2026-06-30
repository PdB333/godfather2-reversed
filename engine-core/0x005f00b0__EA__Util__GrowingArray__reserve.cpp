// FUNC_NAME: EA::Util::GrowingArray::reserve
void EA::Util::GrowingArray::reserve(uint newCapacity)
{
    // this is unaff_ESI
    // struct layout:
    // +0x00: data (int*)
    // +0x04: size (int)
    // +0x08: capacity (int)
    int* dataPtr = this->data;   // *unaff_ESI
    int currentSize = this->size; // unaff_ESI[1]
    int currentCapacity = this->capacity; // unaff_ESI[2]
    
    if ((uint)currentCapacity < newCapacity) {
        // reallocate to larger size
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // operator new[]
        if (dataPtr != 0) {
            uint copyIndex = 0;
            int* dest = newData;
            if (currentSize != 0) {
                do {
                    if (dest != (int*)0x0) {
                        *dest = dataPtr[copyIndex];
                    }
                    copyIndex++;
                    dest++;
                } while (copyIndex < (uint)currentSize);
            }
            FUN_009c8f10(dataPtr); // operator delete[]
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}