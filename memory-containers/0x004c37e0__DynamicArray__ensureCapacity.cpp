// FUNC_NAME: DynamicArray::ensureCapacity

void DynamicArray::ensureCapacity(uint newCapacity) {
    if (capacity < newCapacity) {
        int* newData = (int*)alloc(newCapacity * sizeof(int));
        if (data != 0) {
            uint i = 0;
            int* dest = newData;
            if (size != 0) {
                do {
                    if (dest != 0) {
                        *dest = data[i];
                    }
                    ++i;
                    ++dest;
                } while (i < size);
            }
            free(data);
        }
        data = newData;
        capacity = newCapacity;
    }
}