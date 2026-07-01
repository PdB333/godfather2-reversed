// FUNC_NAME: TArray::deepCopy
int* TArray::deepCopy(TArray* other) {
    int newCapacity = other->capacity;     // +0x08
    this->capacity = newCapacity;          // +0x08
    this->size = other->size;              // +0x04

    if (newCapacity == 0) {
        this->data = nullptr;              // +0x00
        return this;
    }

    // Allocate memory for the new array (each element is 0x20 bytes)
    this->data = (Element*)allocateMemory(newCapacity << 5);  // FUN_009c8e80 (likely operator new)
    if (this->size != 0) {
        int offset = 0;
        for (uint i = 0; i < (uint)this->size; ++i) {
            Element* dest = (Element*)((int)this->data + offset);
            if (dest != nullptr) {
                // Copy element: set vtable and raw 0x20 bytes from source
                dest->vtable = &ELEMENT_VTABLE;  // PTR_LAB_00e35c24
                Element* src = (Element*)((int)other->data + offset);
                dest->field4 = src->field4;
                dest->field8 = src->field8;
                dest->fieldC = src->fieldC;
                dest->field10 = src->field10;
                dest->field14 = src->field14;
                dest->field18 = src->field18;
                dest->field1C = src->field1C;
            }
            offset += 0x20; // each element is 0x20 bytes
        }
    }
    return this;
}