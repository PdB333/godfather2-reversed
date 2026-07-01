// FUNC_NAME: EARSVector::removeAt
// Removes an element at the given index from a dynamic array of 12-byte elements.
// Container layout: +0x00 = mData (pointer to array start), +0x04 = mSize (count of elements)
// Caller: 0x008c4df0

void __thiscall EARSVector::removeAt(uint index) {
    // Only shift elements if the removed element is not the last one
    if (index < mSize - 1) {
        int byteOffset = index * 12; // each element is 12 bytes

        do {
            // Calculate destination and source addresses
            undefined8* dest = (undefined8*)(mData + byteOffset);

            // Copy first 8 bytes from element at (index+1)
            *dest = *(undefined8*)(mData + 12 + byteOffset);

            // Copy next 4 bytes from the same source, offset 0x14 from *this
            *(undefined4*)(dest + 1) = *(undefined4*)((int)dest + 0x14);

            index++;
            byteOffset += 12;
        } while (index < mSize - 1);
    }

    // Decrease count after removal
    mSize--;
}