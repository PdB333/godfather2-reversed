// FUNC_NAME: Vec3Array::pushBack
void __thiscall Vec3Array::pushBack(int *this, float x, float y, float z)
{
    int *bufferPtr;
    int count;
    int capacity;
    undefined4 *newBlock;

    bufferPtr = this + 1; // +0x04: pointer to count field
    if (this[1] <= this[4]) { // count <= maxCapacity? Initial allocation needed
        initBegin();          // 0x005c0b40
        initMiddle();         // 0x005c3960
        initEnd();            // 0x005c28c0
        newBlock = (undefined4 *)allocBlock(); // 0x005c2960
        *newBlock = (int)someFunction;         // 0x005bf600 – likely vtable or function pointer
        newBlock[1] = (void*)this;             // set back-pointer
        *(byte*)(newBlock + 2) = 1;            // set active flag at offset +8
    }
    count = *bufferPtr;
    int nextIndex = count + 1;
    if (this[2] < nextIndex) { // capacity < needed size
        int newBuffer = reallocBuffer(*this, nextIndex, 0xC, bufferPtr, this + 2); // 0x005c27a0
        *this = newBuffer;
    }
    undefined4 *dest = (undefined4 *)(*this + count * 0xC); // offset to element slot
    *bufferPtr = nextIndex;
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return;
}