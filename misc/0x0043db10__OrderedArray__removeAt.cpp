// FUNC_NAME: OrderedArray::removeAt

class OrderedArray {
    int* data;      // +0x00: pointer to element array
    int size;       // +0x04: current number of elements
    // each element is 0x1C bytes (7 ints)
    // method: void removeAt(uint index)
};

void OrderedArray::removeAt(uint index) {
    if (index < size - 1) {
        int byteOffset = index * 0x1C; // offset in bytes
        int* currentElement = (int*)( (char*)data + byteOffset );
        do {
            // shift next element into current position
            currentElement[0] = currentElement[7];   // copy int0
            currentElement[1] = currentElement[8];   // copy int1
            currentElement[2] = currentElement[9];   // copy int2
            currentElement[3] = currentElement[10];  // copy int3
            currentElement[4] = currentElement[11];  // copy int4
            currentElement[5] = currentElement[12];  // copy int5
            currentElement[6] = currentElement[13];  // copy int6
            index++;
            byteOffset += 0x1C;
            currentElement = (int*)( (char*)data + byteOffset );
        } while (index < size - 1);
    }
    size--;
}