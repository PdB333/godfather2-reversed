// FUNC_NAME: ResizeableArray::reserve
void __thiscall ResizeableArray::reserve(uint newCapacity) {
    // Structure layout:
    // +0x00: void* data;
    // +0x04: uint32 size;
    // +0x08: uint32 capacity;
    
    if (capacity < newCapacity) {
        undefined8* newData = (undefined8*)FUN_009c8e80(newCapacity << 4); // allocate newCapacity * 16 bytes
        
        if (data != 0) {
            uint oldSize = size;
            if (oldSize != 0) {
                int srcOffset = 0;
                undefined8* src = (undefined8*)data;
                undefined8* dst = newData;
                for (uint i = 0; i < oldSize; i++) {
                    // Copy 16-byte element (two 8-byte halves)
                    *dst = *(undefined8*)((char*)src + srcOffset);
                    dst[1] = *(undefined8*)((char*)src + srcOffset + 8);
                    srcOffset += 16;
                    dst += 2; // advance by 2 undefined8 (16 bytes)
                }
            }
            FUN_009c8f10(data); // free old block
        }
        
        data = newData;
        capacity = newCapacity;
    }
}