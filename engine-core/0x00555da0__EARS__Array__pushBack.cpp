// FUNC_NAME: EARS::Array::pushBack
void __thiscall EARS::Array::pushBack(int *this, undefined4 *valuePtr)
{
    // Check if the current size equals capacity (masked to remove flag bits).
    // Capacity is stored in lower 30 bits; top bits may be flags.
    if (this[1] == (this[2] & 0x3fffffff)) {
        // Grow the array to accommodate more elements (4 bytes per element).
        FUN_00aa4190(this, 4);
    }
    // Write the value at the end of the array.
    // this[0] is a pointer to the data buffer, this[1] is the current size.
    *(undefined4 *)(this[0] + this[1] * 4) = *valuePtr;
    // Increase the size.
    this[1] = this[1] + 1;
}