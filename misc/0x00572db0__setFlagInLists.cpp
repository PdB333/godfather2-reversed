// FUNC_NAME: setFlagInLists
// Reconstructed from address 0x00572db0
// Searches two arrays of 0x20-byte elements for a matching ID and sets/clears bit 7 (0x80) in a ushort flag at offset +6.

struct ListElement {
    int id;         // +0x00
    /* +0x04 padding? */
    unsigned short flags; // +0x06
    /* rest of 0x20 bytes */
};

// pList points to a structure containing two dynamic arrays (via pointers) and their counts.
// Offset layout assumed:
// +0xa0: int* primaryArray (pointer to array of ListElement)
// +0xa4: int* secondaryArray (pointer to array of ListElement)
// +0xa8: short primaryCount
// +0xaa: short secondaryCount

void __fastcall setFlagInLists(int searchID, int pList, char bSet)
{
    short index;
    int* pArray;
    unsigned short* pFlags;

    // Search primary array
    if (*(short*)(pList + 0xa8) > 0) {
        pArray = *(int**)(pList + 0xa0);
        for (index = 0; index < *(short*)(pList + 0xa8); index++) {
            if (pArray[index] == searchID) {
                goto found;
            }
        }
    }

    // Search secondary array
    if (*(short*)(pList + 0xaa) > 0) {
        pArray = *(int**)(pList + 0xa4);
        for (index = 0; index < *(short*)(pList + 0xaa); index++) {
            if (pArray[index] == searchID) {
                goto found;
            }
        }
        // Not found in either array – return without action
        return;
    }

found:
    // pArray points to the correct array, index is the element index
    pFlags = (unsigned short*)((int)pArray + index * 0x20 + 6);
    if (bSet != 0) {
        *pFlags |= 0x80;   // Set bit 7
    } else {
        *pFlags &= 0xFF7F; // Clear bit 7
    }
}