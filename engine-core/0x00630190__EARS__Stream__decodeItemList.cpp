// FUNC_NAME: EARS::Stream::decodeItemList
// Function at 0x00630190: Decodes a list of items from a binary stream using a custom allocator.
// This is part of the EARS engine's serialization system, likely for reading packed data.
// The stream structure (this) has:
//   +0x08: writePtr (current output position)
//   +0x0C: readPtr  (current input position, points to a tag/count structure)

int __thiscall decodeItemList(void* this)
{
    int* readPtr = *(int**)((int)this + 0xC);
    int* writePtr = *(int**)((int)this + 0x8);

    // Validate the input stream: must have a tag of 5 at the current read position
    if ((writePtr <= readPtr) || (readPtr == nullptr) || (*readPtr != 5))
    {
        assertOrError(PTR_s_table_00e2a8b0); // likely an assertion failure
    }

    int itemCount = getItemCount(1); // get the number of items to process
    int* nextRead = (int*)(*(int*)((int)this + 0xC) + 8); // advance read pointer past tag

    // Check if there is more data to read; if not, use itemCount as a float for later
    float startIndex;
    if ((nextRead < *(int**)((int)this + 0x8)) && (nextRead != nullptr) && (*nextRead > 0))
    {
        resetSomething(); // possibly reset internal state
        startIndex = 0.0f;
    }
    else
    {
        startIndex = (float)itemCount;
    }

    if (itemCount > 0)
    {
        seekTo(itemCount - 1); // seek to the last item index

        // Allocate and write the first item (8 bytes) from the allocator
        int* allocBlock = (int*)allocateMemory();
        int* outputPtr = *(int**)((int)this + 0x8);
        *outputPtr = allocBlock[0];
        outputPtr[1] = allocBlock[1];
        *(int*)((int)this + 0x8) += 8; // advance write pointer

        int currentIndex = (int)startIndex;
        while (currentIndex < itemCount)
        {
            // Allocate a new block for the next item
            allocBlock = (int*)allocateMemory();
            outputPtr = *(int**)((int)this + 0x8);
            *outputPtr = allocBlock[0];
            outputPtr[1] = allocBlock[1];
            *(int*)((int)this + 0x8) += 8;

            int savedWritePos = *(int*)((int)this + 0x8);
            int inputValue = *(int*)(*(int*)((int)this + 0xC) + 4); // read a value from input stream

            // Read an additional value from the input stream (possibly a float or int)
            int* tempBlock = (int*)allocateMemory();
            if (tempBlock == &DAT_00e2a93c) // sentinel check for special allocator behavior
            {
                float floatVal = (float)currentIndex;
                int type = 3;
                tempBlock = (int*)readValue(this, inputValue, &type); // read a value from the stream
            }

            // Overwrite the previously written item with the new data (swap/reorder)
            *tempBlock = *(int*)(savedWritePos - 8);
            tempBlock[1] = *(int*)(savedWritePos - 4);
            *(int*)((int)this + 0x8) -= 8; // move write pointer back

            currentIndex++;
        }

        // Write a null terminator (8 bytes of zero)
        **(int**)((int)this + 0x8) = 0;
        *(int*)((int)this + 0x8) += 8;

        // Final read and write to complete the list
        int finalInputValue = *(int*)(*(int*)((int)this + 0xC) + 4);
        int finalWritePos = *(int*)((int)this + 0x8);
        int* finalBlock = (int*)allocateMemory();
        if (finalBlock == &DAT_00e2a93c)
        {
            float floatVal = (float)itemCount;
            int type = 3;
            finalBlock = (int*)readValue(this, finalInputValue, &type);
        }
        *finalBlock = *(int*)(finalWritePos - 8);
        finalBlock[1] = *(int*)(finalWritePos - 4);
        *(int*)((int)this + 0x8) -= 8;

        return 1;
    }
    return 0;
}