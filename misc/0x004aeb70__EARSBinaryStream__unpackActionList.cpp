// FUNC_NAME: EARSBinaryStream::unpackActionList
void __thiscall EARSBinaryStream::unpackActionList(int* pairArray)
{
    int key;
    int value;
    int allocateResult;
    int* stackPtr;
    int* newEntry;

    // Iterate over the array of (key, value) pairs; the array is terminated by a zero key
    key = *pairArray;
    while (key != 0) {
        // Call some global/static function (possibly initializing something)
        FUN_00625ca0();

        // Retrieve the second element of the current pair – the value/ID
        value = pairArray[1];

        // Check if there is enough data left in the internal buffer (this+0x10 points to a buffer descriptor)
        // The buffer descriptor has current read position at +0x20 and end position at +0x24
        if (*(unsigned int*)(*(int*)(this + 0x10) + 0x20) <= *(unsigned int*)(*(int*)(this + 0x10) + 0x24)) {
            // Perform a series of reads/writes to extract more data from the buffer
            int readValue = FUN_00627290();          // Probably reads an integer from the buffer
            FUN_00626f80();                         // Advances buffer read pointer
            FUN_00626fd0(0);                        // Writes zero somewhere (maybe to output)
            FUN_00626f80();                         // Advances buffer read pointer again
            FUN_00627010(readValue);                // Uses the read value
            FUN_006270e0();                         // Finalizes the read operation
        }

        // Allocate a new structure (8 bytes? memory manager)
        allocateResult = FUN_00638110(0);
        if (allocateResult != 0) {
            *(int*)(allocateResult + 0xc) = value;  // Store the value at offset 0xc
        }

        // Push an entry onto the internal stack (this+0x8 is a pointer to the stack top)
        stackPtr = *(int**)(this + 0x8);
        stackPtr[1] = allocateResult;               // Second element is the allocated block
        *stackPtr = 6;                              // First element is a type tag (6 = action command?)
        *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8; // Increase stack pointer by one entry (8 bytes)

        // Allocate a second structure and copy from two entries below the current stack top?
        int currentStack = *(int*)(this + 0x8);
        newEntry = (int*)FUN_00638020();            // Allocate another block
        if (newEntry != 0) {
            newEntry[0] = *(int*)(currentStack - 8);   // Copy from one entry below stack top
            newEntry[1] = *(int*)(currentStack - 4);   // Copy from the same entry's second word
        }
        *(int*)(this + 0x8) = *(int*)(this + 0x8) - 0x10; // Decrease stack pointer by two entries (16 bytes)

        // Move to the next pair in the input array
        pairArray += 2;
        key = *pairArray;
    }
    return;
}