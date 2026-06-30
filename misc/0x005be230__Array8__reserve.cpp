// FUNC_NAME: Array8::reserve
void Array8::reserve(uint newCapacity)
{
    int iVar1;
    undefined4 *newBuffer;
    uint uVar3;
    undefined4 *oldBuffer;
    
    // this->capacity is at offset +8, this->size at +4, this->data at +0
    // If requested capacity is larger than current
    if ((uint)this->capacity < newCapacity) {
        // Allocate new buffer: each element is 8 bytes
        newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 8);
        if (this->data != 0) {
            uVar3 = 0;
            oldBuffer = newBuffer;
            if (this->size != 0) {
                // Copy existing elements (up to current size)
                do {
                    if (oldBuffer != (undefined4 *)0x0) {
                        iVar1 = this->data;
                        *oldBuffer = *(undefined4 *)(iVar1 + uVar3 * 8);
                        oldBuffer[1] = *(undefined4 *)(iVar1 + 4 + uVar3 * 8);
                    }
                    uVar3 = uVar3 + 1;
                    oldBuffer = oldBuffer + 2;
                } while (uVar3 < (uint)this->size);
            }
            // Free old buffer
            FUN_009c8f10(this->data);
        }
        // Update data pointer and capacity
        this->data = (int)newBuffer;
        this->capacity = newCapacity;
    }
    return;
}