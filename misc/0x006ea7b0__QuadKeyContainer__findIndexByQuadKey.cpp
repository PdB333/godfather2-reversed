// FUNC_NAME: QuadKeyContainer::findIndexByQuadKey
uint __thiscall QuadKeyContainer::findIndexByQuadKey(const int* quadKey) const
{
    uint index = 0;

    // Check if there are any elements stored (count at +0x34)
    if (this->elementCount != 0) {
        // Pointer to array of element pointers (+0x30)
        int** currentPtr = this->elementArray;
        do {
            int* element = *currentPtr;

            // Compare four ints at offsets +0x50, +0x54, +0x58, +0x5C
            if (element[0x14] == quadKey[0] &&   // +0x50
                element[0x15] == quadKey[1] &&   // +0x54
                element[0x16] == quadKey[2] &&   // +0x58
                element[0x17] == quadKey[3]) {   // +0x5C
                // Found match, return index
                return index;
            }

            index++;
            currentPtr++;
        } while (index < this->elementCount);
    }

    // Not found
    return 0xFFFFFFFF;
}