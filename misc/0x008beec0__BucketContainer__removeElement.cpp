// FUNC_NAME: BucketContainer::removeElement
// Address: 0x008beec0
// Role: Removes an element value from the container's bucket array. Returns 1 if found and removed, else 0 (low byte of return).
// The container has a fixed number of buckets (count at +0x134). Each bucket is a struct with:
//   +0x00: int* pElements (pointer to dynamic array of ints)
//   +0x04: int elementCount
//   +0x08..+0x18: unused (5 ints, pad to 28 bytes per bucket)
// The bucket array starts at offset 0x10 of the block pointed by this+0x130.

uint __thiscall BucketContainer::removeElement(void* thisPtr, int elementToRemove)
{
    uint numBuckets = *(uint*)((int)thisPtr + 0x134);
    if (numBuckets == 0) {
        // Return low byte zero (failure)
        return 0;
    }

    // Pointer to the first bucket struct (after a 0x10-byte header)
    int* bucket = (int*)(*(int*)((int)thisPtr + 0x130) + 0x10);

    for (uint bucketIndex = 0; bucketIndex < numBuckets; bucketIndex++)
    {
        int elementCount = bucket[1]; // bucket->elementCount
        if (elementCount != 0)
        {
            int* pElements = (int*)bucket[0]; // bucket->pElements
            for (uint i = 0; i < (uint)elementCount; i++)
            {
                if (pElements[i] == elementToRemove)
                {
                    // Found; remove by shifting remaining elements left
                    if (i < (uint)elementCount - 1)
                    {
                        do {
                            pElements[i] = pElements[i + 1];
                            i++;
                        } while (i < (uint)elementCount - 1);
                    }
                    bucket[1] = elementCount - 1; // decrement count
                    return 1; // success
                }
            }
        }
        // Advance to next bucket (each bucket is 7 ints = 28 bytes)
        bucket += 7;
    }
    return 0; // element not found
}