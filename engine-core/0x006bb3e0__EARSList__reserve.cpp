// FUNC_NAME: EARSList::reserve
void __thiscall EARSList::reserve(int *thisPtr, uint newCapacity)
{
    // Fields:
    // thisPtr[0] = mBuffer (pointer to allocated memory block)
    // thisPtr[1] = mSize (number of elements currently stored)
    // thisPtr[2] = mCapacity (current maximum capacity)

    if ((uint)thisPtr[2] < newCapacity)
    {
        // Allocate new buffer: newCapacity * sizeof(Element) + 0x10 header for list head
        int *newBuffer = (int *)FUN_009c8e80(newCapacity * 0x18); // FUN_009c8e80 likely malloc

        if (thisPtr[0] != 0)
        {
            if (thisPtr[1] != 0)
            {
                // Point to first element in new buffer (skip 16-byte header)
                int *newElementIter = (int *)((int)newBuffer + 0x10);
                uint elementIndex = 0;
                do
                {
                    // Compute old element pointer
                    int *oldElement = (int *)((int)thisPtr[0] + elementIndex * 0x18);

                    // Relocate the element (intrusive linked list node)
                    int *newElem = newElementIter;
                    if (newElementIter != (int *)0x10) // always true, decompiler artifact
                    {
                        // Copy next pointer
                        int *next = (int *)*oldElement;
                        newElem[-4] = (int)next;    // +0x00: next

                        // Update previous pointer
                        newElem[-3] = 0;             // +0x04: prev, null if no next
                        if (next != 0)
                        {
                            newElem[-3] = next[1];   // next->prev = this new element
                            next[1] = (int)(newElem - 4);
                        }

                        // Copy data fields (offsets +0x08, +0x0C, +0x10, +0x14)
                        newElem[-2] = oldElement[2];
                        newElem[-1] = oldElement[3];
                        newElem[0] = oldElement[4];
                        newElem[1] = oldElement[5];
                    }

                    // Destroy old element (free node, remove from lists)
                    FUN_004daf90(oldElement); // likely destructor

                    elementIndex++;
                    newElementIter += 6; // advance 24 bytes = 6 ints
                } while (elementIndex < (uint)thisPtr[1]);
            }

            // Free old buffer
            FUN_009c8f10(thisPtr[0]); // likely free
        }

        // Update container fields
        thisPtr[0] = (int)newBuffer;
        thisPtr[2] = (int)newCapacity;
    }
    return;
}