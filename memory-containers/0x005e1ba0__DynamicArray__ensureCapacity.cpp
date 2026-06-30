// FUNC_NAME: DynamicArray::ensureCapacity
void __thiscall DynamicArray::ensureCapacity(uint minCapacity) {
    // Structure offsets: +0x0 buffer (int*), +0x4 size (uint), +0x8 capacity (uint)
    if (this->capacity < minCapacity) {
        int* newBuffer = (int*)allocMemory(minCapacity * sizeof(int)); // FUN_009c8e80
        if (this->buffer != nullptr) {
            uint i = 0;
            int* dst = newBuffer;
            if (this->size != 0) {
                do {
                    if (newBuffer != nullptr) {
                        *dst = this->buffer[i];
                    }
                    i++;
                    dst++;
                } while (i < this->size);
            }
            freeMemory(this->buffer); // FUN_009c8f10
        }
        this->buffer = newBuffer;
        this->capacity = minCapacity;
    }
}