// FUNC_NAME: StringBuffer::appendRange
void __thiscall StringBuffer::appendRange(int* thisPtr, int* srcBegin, int* srcEnd)
{
    int lengthToAppend = *srcEnd - *srcBegin;
    FUN_0059c140(lengthToAppend >= 0); // assert non-negative length

    if (lengthToAppend > 0) {
        int newLength = *thisPtr + lengthToAppend;
        char* dest;

        if (newLength < thisPtr[1]) {
            // Capacity sufficient, use existing buffer
            dest = (char*)*thisPtr; // thisPtr[0] is current length, but we need the data pointer? Wait, careful.
            // Actually *thisPtr is the length, not the data pointer. The code uses *in_EAX which is the this pointer? Let's re-evaluate.
        }
        else {
            int oldDataPtr = *thisPtr; // This is actually the data pointer? No, *thisPtr is length. The decompiler uses in_EAX which is the this pointer. Let's re-read.
        }
    }
}