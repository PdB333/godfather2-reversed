// FUNC_NAME: ReadBuffer::readRange
// Address: 0x0058a290
// This function reads a range of 12-byte entries from a sequential buffer.
// It seeks to the given startIndex (must be >= currentIndex), then copies entries
// to the output array until the currentIndex reaches the total count (stored at +0x58).
// Offsets:
//   +0x50 : current data pointer (pointer to next entry to read)
//   +0x54 : current read index (number of entries read so far)
//   +0x58 : total number of entries in the buffer (end index)

void __thiscall ReadBuffer::readRange(int startIndex, unsigned int *output)
{
    int currentIndex = *(int *)(this + 0x54);      // +0x54
    int totalCount = *(int *)(this + 0x58);        // +0x58
    unsigned int *currentPtr = *(unsigned int **)(this + 0x50);  // +0x50

    // Seek forward to startIndex
    while (currentIndex < startIndex)
    {
        currentPtr += 3;        // skip 12 bytes (3 dwords) per entry
        currentIndex++;
        *(int *)(this + 0x50) = (int)currentPtr;   // update pointe
        *(int *)(this + 0x54) = currentIndex;      // update index
    }

    // Copy entries from current to totalCount
    while (currentIndex < totalCount)
    {
        // Read three dwords from current entry
        unsigned int a = currentPtr[0];
        unsigned int b = currentPtr[1];
        unsigned int c = currentPtr[2];

        // Store to output
        output[0] = a;
        output[1] = b;
        output[2] = c;

        // Advance
        currentPtr += 3;
        currentIndex++;
        *(int *)(this + 0x50) = (int)currentPtr;
        *(int *)(this + 0x54) = currentIndex;
        output += 3;
    }
}