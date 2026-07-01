//FUNC_NAME: EARS::Array::removeAt
void __thiscall EARS::Array::removeAt(int *this, uint index)
{
    // this[0] = pointer to array of 8-byte elements
    // this[1] = count of elements
    uint count = this[1];
    if (index < count - 1) {
        // Shift elements left to fill the gap
        do {
            undefined4 *src = (undefined4 *)(this[0] + (index + 1) * 8);
            undefined4 *dst = (undefined4 *)(this[0] + index * 8);
            dst[0] = src[0];
            dst[1] = src[1];
            index++;
        } while (index < count - 1);
    }
    // Decrement count
    this[1] = count - 1;
}