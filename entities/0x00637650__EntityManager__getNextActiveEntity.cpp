// FUNC_NAME: EntityManager::getNextActiveEntity

// Function at 0x00637650
// Iterates over two levels of entity storage, returning the next active entity.
// First level: linear array of 8-byte pairs (tag + value) stored at this+0xC, count at this+0x1C.
// Second level: bucket array of 0x14-byte entries (4 dwords: type, id, validFlag, data) at this+0x10,
//   indexed by bits defined by this+7 (count = 1 << (byte & 0x1f)).
// Output: an array of 4 dwords (type, id, data1, data2) written to the pointer passed in ESI.

int __thiscall EntityManager::getNextActiveEntity(int output[4])
{
    int currentIndex = FUN_00637590();                 // get current iterator position (likely stored inside object)
    currentIndex++;                                    // move to next slot

    // ---- First pass: linear array of 8-byte pairs ----
    int *linearArray = *(int **)(this + 0xC);          // each element: {tag, value}
    int linearCount = *(int *)(this + 0x1C);           // number of entries
    if (currentIndex < linearCount)
    {
        do
        {
            if (linearArray[currentIndex * 2] != 0)    // tag non-zero means valid
            {
                output[0] = 3;                         // type = 3 for linear entries
                output[1] = (int)(currentIndex + 1);   // id = 1-based index (cast as float in earlier code?)
                output[2] = linearArray[currentIndex * 2];     // first dword of pair (tag)
                output[3] = linearArray[currentIndex * 2 + 1]; // second dword of pair (value)
                return 1;                              // found
            }
            currentIndex++;
        } while (currentIndex < linearCount);
    }

    // ---- Second pass: bucket array indexed by bits ----
    int bucketIndex = currentIndex - linearCount;      // offset from linear array end
    int bucketCount = 1 << (*(unsigned char *)(this + 7) & 0x1F); // number of buckets (power of two)
    int *bucketArray = *(int **)(this + 0x10);         // each bucket: 0x14 bytes, 4 used dwords
    if (bucketIndex < bucketCount)
    {
        do
        {
            // Each bucket: [offset0]=type, [offset4]=id, [offset8]=validFlag, [offset0C]=data
            if (bucketArray[bucketIndex * 5 + 2] != 0) // check the valid flag (third dword)
            {
                output[0] = bucketArray[bucketIndex * 5];        // type
                output[1] = bucketArray[bucketIndex * 5 + 1];    // id
                output[2] = bucketArray[bucketIndex * 5 + 2];    // valid flag (also data?)
                output[3] = bucketArray[bucketIndex * 5 + 3];    // data
                return 1;
            }
            bucketIndex++;
        } while (bucketIndex < bucketCount);
    }

    return 0; // no more active entries
}