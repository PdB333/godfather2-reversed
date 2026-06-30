// FUNC_NAME: EARSRefArray::RemoveRange
void __thiscall EARSRefArray::RemoveRange(int *thisPtr, int beginIndex, int endIndex)
{
    int *srcElem, *dstElem;
    int newSize, numToMove, lastIdx, numToDestroy, destroyOffset;

    // If the range is empty, do nothing
    if (endIndex - beginIndex == 0) {
        return;
    }

    // Calculate new size after removal
    newSize = thisPtr[1] - (endIndex - beginIndex); // thisPtr[1] is count
    dstElem = (int *)(thisPtr[0] + beginIndex * 12); // thisPtr[0] is array data pointer
    srcElem = (int *)(thisPtr[0] + endIndex * 12);

    // If there are elements after the erased range, shift them left
    if (beginIndex < newSize) {
        numToMove = newSize - beginIndex; // number of elements to move
        do {
            if (dstElem != srcElem) {
                // The element's first int is a pointer to a reference‑counted object
                int refPtr = *srcElem;
                if (*dstElem != refPtr) {
                    if (*dstElem != 0) {
                        // Release the existing reference
                        EARSRefArray::ReleaseReference(dstElem);
                    }
                    // Assign new pointer and update the linked list (external ref‑counting)
                    *dstElem = refPtr;
                    if (refPtr != 0) {
                        dstElem[1] = *(int *)(refPtr + 4); // next pointer
                        *(int **)(refPtr + 4) = dstElem;   // update previous node's next
                    }
                }
            }
            // Copy the remaining two ints (2nd and 3rd?? Actually offset 8)
            int tmp = *(srcElem + 2); // third int (12‑byte element: int[3])
            dstElem[2] = tmp;

            srcElem += 3; // advance 12 bytes
            dstElem += 3;
            numToMove--;
        } while (numToMove != 0);
    }

    // Destroy the now‑unused elements at the tail of the array
    lastIdx = thisPtr[1] - 1; // original last index
    if (newSize <= lastIdx) {
        destroyOffset = lastIdx * 12;
        numToDestroy = (lastIdx - newSize) + 1; // number of elements to destroy
        do {
            if (*(int *)(thisPtr[0] + destroyOffset) != 0) {
                EARSRefArray::ReleaseReference((int *)(thisPtr[0] + destroyOffset));
            }
            destroyOffset -= 12;
            numToDestroy--;
        } while (numToDestroy != 0);
    }

    // Update the array size
    thisPtr[1] = newSize;

    return;
}