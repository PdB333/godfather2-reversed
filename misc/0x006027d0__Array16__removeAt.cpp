// FUNC_NAME: Array16::removeAt
void __fastcall Array16::removeAt(int *this, uint index)
{
    // this[0] = pointer to array of 16-byte elements
    // this[1] = number of elements (count)
    uint count = this[1];
    if (index < count - 1) {
        // Shift elements left by one (16 bytes each)
        int offset = index << 4; // index * 16
        do {
            // Copy element at index+1 to index
            undefined8 *src = (undefined8 *)(this[0] + offset + 0x10);
            undefined8 *dst = (undefined8 *)(this[0] + offset);
            *dst = *src;
            dst[1] = src[1];
            index++;
            offset += 0x10;
        } while (index < count - 1);
    }
    // Decrement count
    this[1] = count - 1;
}