// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity) {
    if (capacity < newCapacity) {
        int* newData = (int*)allocate(newCapacity * 4);
        if (data != 0) {
            uint i = 0;
            int* dst = newData;
            if (size != 0) {
                do {
                    if (dst != 0) {
                        *dst = data[i];
                    }
                    i++;
                    dst++;
                } while (i < size);
            }
            deallocate(data);
        }
        data = newData;
        capacity = newCapacity;
    }
}