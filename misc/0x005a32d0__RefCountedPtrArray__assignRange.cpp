// FUNC_NAME: RefCountedPtrArray::assignRange
// Function at 0x005a32d0: Copies a range of reference-counted pointers from source to destination,
// handling reference count increments/decrements and self-assignment checks.
// Returns the end pointer of the destination range.
// Parameters:
//   sourceStart (in EAX) - start of source range
//   sourceEnd (param_1) - end of source range (exclusive)
//   destStart (param_2) - start of destination range
// Returns: pointer to one past the last copied element in destination

undefined4* RefCountedPtrArray::assignRange(undefined4* sourceStart, undefined4* sourceEnd, undefined4* destStart)
{
    undefined4* destCurrent = destStart;
    undefined4* srcCurrent = sourceStart;

    // Iterate over source range
    while (srcCurrent != sourceEnd)
    {
        // Move destination pointer forward for next iteration
        destStart = destCurrent + 1;

        // Self-assignment check: skip if source and destination point to same element
        if (srcCurrent != destCurrent)
        {
            // Decrement reference count of old pointer at destination
            int* oldPtr = (int*)*destCurrent;
            if (oldPtr != nullptr)
            {
                *oldPtr = *oldPtr - 1;
                if (*oldPtr == 0)
                {
                    // Release the object when ref count reaches zero
                    releaseRefCountedObject(*destCurrent); // FUN_005a3270
                }
            }

            // Assign new pointer from source and increment its reference count
            int* newPtr = (int*)*srcCurrent;
            *destCurrent = newPtr;
            if (newPtr != nullptr)
            {
                *newPtr = *newPtr + 1;
            }
        }

        // Advance source and destination iterators
        srcCurrent = srcCurrent + 1;
        destCurrent = destStart;
    }

    // Return the end of destination range (one past last copied)
    return destStart;
}