// FUN_004BB620: EARSArray::addRange(EARSArray const&)

void __thiscall EARSArray::addRange(EARSArray const* sourceArray)
{
    // Array element size is 0x10 (16 bytes)
    // Field offsets:
    // +0x1c: element buffer pointer
    // +0x20: current element count (size)
    // +0x24: capacity (maximum elements before reallocation)

    uint index = 0;
    int srcOffset = 0;

    if (sourceArray->size != 0) {
        do {
            int srcBase = sourceArray->buffer;            // base of source elements
            int currentCapacity = this->capacity;

            // Check if we need to grow the array
            if (this->size == currentCapacity) {
                if (currentCapacity == 0) {
                    currentCapacity = 1;
                } else {
                    currentCapacity *= 2;
                }
                // Reallocate the internal buffer (FUN_00407880)
                this->grow(currentCapacity);
            }

            int insertionIndex = this->size;
            this->size = insertionIndex + 1;

            // Destination address: buffer + (oldIndex * elementSize)
            int* destElement = (int*)(this->buffer + (insertionIndex * 16));
            if (destElement != nullptr) {
                // Copy element from source array to the new slot
                // Source: sourceArray->buffer + srcOffset
                // FUN_004d3b50 performs a copy (probably a placement copy or memcpy)
                FUN_004d3b50(srcBase + srcOffset);
            }

            index++;
            srcOffset += 16;
        } while (index < (uint)sourceArray->size);
    }
}