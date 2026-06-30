// FUNC_NAME: CircularBuffer::push
void __thiscall CircularBuffer::push(int *this, undefined4 *valuePtr)
{
    int capacity = this[2] & 0x3fffffff; // +0x08: capacity (top bits used for flags)
    if (this[1] == capacity) {           // +0x04: writeIndex
        FUN_00aa4190(this, 4);           // grow buffer by one element (4 bytes)
    }
    *(undefined4 *)(this[0] + this[1] * 4) = *valuePtr; // +0x00: buffer pointer
    this[1] = this[1] + 1;
}