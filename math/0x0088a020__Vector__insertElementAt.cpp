// FUNC_NAME: Vector::insertElementAt
void __thiscall Vector::insertElementAt(void* thisPtr, void* insertPos, void* sourceElem)
{
    // Vector layout: [0] begin, [1] end, [2] capacity_end
    int* vec = (int*)thisPtr;
    char* begin = (char*)vec[0];
    char* end = (char*)vec[1];
    char* capacityEnd = (char*)vec[2];
    const int elemSize = 0x50; // 80 bytes per element

    if (end != capacityEnd) {
        // There is space for at least one more element
        // If the source element lies in the range [insertPos, end), adjust it forward by one element
        // because the later shift will overwrite it otherwise.
        if (insertPos <= sourceElem && sourceElem < end) {
            sourceElem = (char*)sourceElem + elemSize;
        }

        // Shift existing elements from end-1 down to insertPos to the right by one element
        // First, move the last element one slot forward (actually we work from the end backwards)
        char* src = end - elemSize;
        char* dst = end;
        // Copy one element from src to dst
        for (int i = 0; i < elemSize / 4; i++) {
            *(int*)dst = *(int*)src;
            src += 4;
            dst += 4;
        }

        // Now shift all elements between insertPos and the old end-1 to the right
        src = end - elemSize;
        dst = end;
        while (src != insertPos) {
            src -= elemSize;
            dst -= elemSize;
            char* tmpSrc = src;
            char* tmpDst = dst;
            for (int i = 0; i < elemSize / 4; i++) {
                *(int*)tmpDst = *(int*)tmpSrc;
                tmpSrc += 4;
                tmpDst += 4;
            }
        }

        // Copy the new element to insertPos
        src = (char*)sourceElem;
        dst = (char*)insertPos;
        for (int i = 0; i < elemSize / 4; i++) {
            *(int*)dst = *(int*)src;
            src += 4;
            dst += 4;
        }

        // Update end pointer (moved one element forward)
        vec[1] = (int)(end + elemSize);
        return;
    }

    // Reallocation needed
    int currentSize = (end - begin) / elemSize;
    int newSize;
    if (currentSize == 0) {
        newSize = 1;
    } else {
        newSize = currentSize * 2;
    }

    // Allocate new buffer (aligned)
    int allocSize = newSize * elemSize;
    char* newBuffer = (char*)allocate(allocSize, 0x10, 0, "EASTL", 0, 0, "eastl/allocator.h", 0xfd);

    // Copy elements before insertPos to new buffer
    copyMem(&insertPos, begin, insertPos, newBuffer, insertPos); // actually this is a placeholder for memmove
    // The decompiler shows two separate moves: first from begin to insertPos, then from insertPos to end, plus the new element.
    // We'll implement the standard approach:
    // 1. Copy [begin, insertPos) to newBuffer
    int prefixBytes = (char*)insertPos - begin;
    copyMem(newBuffer, begin, prefixBytes); // custom copy function
    // 2. Copy source element to newBuffer at position after prefix
    copyMem(newBuffer + prefixBytes, sourceElem, elemSize);
    // 3. Copy [insertPos, end) to newBuffer after the new element
    int suffixBytes = end - (char*)insertPos;
    copyMem(newBuffer + prefixBytes + elemSize, insertPos, suffixBytes);

    // Deallocate old buffer
    if (begin != 0) {
        deallocate(begin);
    }

    // Update vector pointers
    vec[0] = (int)newBuffer;
    vec[1] = (int)(newBuffer + prefixBytes + elemSize);
    vec[2] = (int)(newBuffer + allocSize);
}