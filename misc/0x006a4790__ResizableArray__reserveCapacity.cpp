// FUNC_NAME: ResizableArray::reserveCapacity
void __thiscall ResizableArray::reserveCapacity(void* thisPtr, uint newCapacity)
{
    int* bufferPtr;
    int* newBuffer;
    int elementCount;
    int oldCapacity;
    int i;
    int srcOffset;
    int dstOffset;

    // this layout: +0x00: buffer, +0x04: elementCount, +0x08: capacity
    // element size = 0x30

    if (*(uint*)((int)thisPtr + 8) < newCapacity) {
        // allocate new buffer
        newBuffer = (int*)FUN_009c8e80(newCapacity * 0x30); // allocate(size * elementSize)
        dstOffset = 0;
        if (*(int*)thisPtr != 0) {
            elementCount = 0;
            srcOffset = 0;
            if (*(int*)((int)thisPtr + 4) != 0) {
                do {
                    bufferPtr = *(int**)thisPtr;
                    if (newBuffer != 0) {
                        // move/copy constructor for each existing element
                        FUN_006a46f0((int)bufferPtr + dstOffset);
                    }
                    elementCount++;
                    // set vtable pointer at offset 0x24 in each element
                    *(void***)((int)bufferPtr + dstOffset + 0x24) = &PTR_LAB_00e2f0c0;
                    dstOffset += 0x30;
                    srcOffset += 0x30;
                } while ((uint)elementCount < *(uint*)((int)thisPtr + 4));
            }
            FUN_009c8f10(*(int*)thisPtr); // free old buffer
        }
        *(int*)thisPtr = (int)newBuffer;
        *(uint*)((int)thisPtr + 8) = newCapacity;
    }
    return;
}