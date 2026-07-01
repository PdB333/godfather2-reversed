// FUNC_NAME: ResizableArray::reserve
void __thiscall ResizableArray::reserve(ResizableArray *this, uint targetCapacity)
{
    undefined4 *newData;
    uint i;
    undefined4 *dest;

    // Field offsets:
    // +0x00: data pointer (int*)
    // +0x04: element count (size)
    // +0x08: allocated capacity (max elements)
    if (this->capacity < targetCapacity) {
        // Allocate new block: targetCapacity elements, each 4 bytes
        newData = (undefined4 *)FUN_009c8e80(targetCapacity * 4);
        if (this->data != 0) {
            i = 0;
            dest = newData;
            if (this->size != 0) {
                do {
                    if (newData != (undefined4 *)0x0) {
                        *dest = *(undefined4 *)(this->data + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < this->size);
            }
            FUN_009c8f10(this->data);
        }
        this->data = (int)newData;
        this->capacity = targetCapacity;
    }
    return;
}