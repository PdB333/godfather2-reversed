// FUNC_NAME: Vector::growCapacity
void Vector::growCapacity(int *thisPtr, uint newCapacity) {
    int *oldData;
    int *newData;
    int *elemSrc;
    int *elemDst;
    uint index;
    
    oldData = thisPtr;
    if ((uint)thisPtr[2] < newCapacity) { // +0x08: current capacity
        newData = (int *)FUN_009c8e80(newCapacity * 0x14); // allocate 20-byte elements
        index = 0;
        if (*thisPtr != 0) { // +0x00: data pointer exists
            if (thisPtr[1] != 0) { // +0x04: element count
                do {
                    elemSrc = (int *)(*oldData + index); // source element
                    elemDst = newData + index / 4; // destination element (index is byte offset)
                    // Actually index is initialized 0 and incremented by 0x14 each iteration,
                    // so it's byte offset. elemDst should be newData + (index/4) but they use newData + (count*5) via puVar6+5.
                    // Let's correct:
                    // elemDst = newData + (index/4)? No, they set puVar6 = puVar3 and then puVar6 += 5 each iteration.
                    // Better to write as pointer arithmetic.
                    if (elemDst != 0) {
                        *elemDst = *elemSrc;          // copy first 4 bytes
                        elemDst[1] = elemSrc[1];      // copy next 4 bytes
                        FUN_006099f0(elemSrc + 2);    // deep copy element at offset +8 (possibly string/resource)
                    }
                    if (elemSrc[2] != 0) {            // if internal pointer at +8 is non-null
                        FUN_009c8f10(elemSrc[2]);     // free/destruct it
                    }
                    index++; // iteration count, not byte offset, actually it's a counter iVar4 increased by 0x14
                    // Actually they used param_1 as counter (set to 0 initially) and incremented as (int*) 
                    // I'll rename to elementIndex
                    // Then they increase puVar6 (destination) by 5 words (20 bytes)
                } while (elementIndex < (uint)thisPtr[1]); // loop until all elements copied
            }
            FUN_009c8f10(*thisPtr); // free old data block
        }
        *thisPtr = (int)newData;      // +0x00: set new data pointer
        thisPtr[2] = newCapacity;     // +0x08: update capacity
    }
}