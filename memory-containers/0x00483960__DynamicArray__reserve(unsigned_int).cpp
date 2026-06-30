// FUNC_NAME: DynamicArray::reserve(unsigned int)
void DynamicArray::reserve(uint newCapacity)
{
    int count;
    undefined8 *newBuffer;
    undefined8 *oldBuffer;
    int i;
    
    // Only resize if requested capacity is larger than current capacity
    if (newCapacity > this->capacity) {
        // Allocate new buffer: each element is 0x10 bytes
        newBuffer = (undefined8 *)operator new[](newCapacity << 4);
        
        // Copy existing elements if count > 0
        if (this->data != 0) {
            count = 0;
            if (this->size != 0) {
                i = 0;
                oldBuffer = newBuffer; // Used for writing back after loop? Actually the loop uses puVar3 = puVar2, and then increments puVar3. So it's writing to newBuffer.
                do {
                    // Copy one element (16 bytes) from old buffer
                    if (oldBuffer != 0) {
                        *oldBuffer = *(undefined8 *)(this->data + i);
                        oldBuffer[1] = *(undefined8 *)(this->data + i + 8);
                    }
                    count = count + 1;
                    i = i + 0x10;
                    oldBuffer = oldBuffer + 2; // Advance by 2 undefined8 (16 bytes)
                } while (count < this->size);
            }
            // Free old buffer
            operator delete[](this->data);
        }
        // Update pointer and capacity
        this->data = (SomeElementType *)newBuffer;
        this->capacity = newCapacity;
    }
    return;
}