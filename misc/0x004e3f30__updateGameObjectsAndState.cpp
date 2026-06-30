// FUNC_NAME: updateGameObjectsAndState

// Function at 0x004e3f30: Main per-frame update that iterates over game objects, copies some data structures, 
// checks conditions, and resets global state variables.
// TODO: Determine exact class context from caller at 0x004dfff0.

void updateGameObjectsAndState()
{
    int i;
    undefined4* srcData;
    undefined4* dstData;
    uint count;
    undefined4* copySrc;
    undefined4* copyDst;

    // 1. Call virtual update methods for each object in the global list
    // Iterates over numObjects (DAT_011946b4) and calls a virtual function at offset 0x1c
    i = 0;
    if (0 < DAT_011946b4) {
        do {
            // Each entry in objectList (DAT_011946b8) is a pointer to some object.
            // Virtual function is at vtable offset 0x1c (i.e., 7th entry in 4-byte vtable).
            (*(void (**)(void))(*(int*)objectList[i] + 0x1c))();
            i++;
        } while (i < DAT_011946b4);
    }

    // 2. Call some other function with two label addresses and apparently ESI context
    // FUN_00607d50 likely processes something related to these labels.
    FUN_00607d50(&LAB_004e3ba0, &LAB_004e3bc0, unaff_ESI);

    // 3. Copy and process a series of data blocks (likely network packets or input state)
    // DAT_012054d8 is the count of blocks to process.
    count = 0;
    if (DAT_012054d8 != 0) {
        srcData = &DAT_0119455c;  // Base of source data array
        do {
            // Extract various fields from the current block (size 0x2b * 4 = 172 bytes)
            // These are read from offsets relative to the start of the block.
            DAT_01218e42 = *(short*)((int)srcData - 2);     // 2 bytes at block_start - 2
            DAT_01218e44 = *srcData;                         // 4 bytes at block_start
            DAT_01218e40 = *(short*)(srcData - 1);          // 2 bytes at block_start - 4? (cast from int*)
            DAT_01218e48 = srcData[1];                       // 4 bytes at block_start+4

            // Copy 0x28 (40) ints (160 bytes) from srcData+2 to DAT_01218e50
            copySrc = srcData + 2;
            copyDst = &DAT_01218e50;
            for (i = 0x28; i != 0; i--) {
                *copyDst = *copySrc;
                copySrc++;
                copyDst++;
            }

            // Process the copied data
            FUN_004e23c0();

            count++;
            srcData += 0x2b;  // Advance to next block (0x2b * 4 = 172 bytes)
        } while (count < DAT_012054d8);
    }

    // 4. Scan another array for a specific pattern (likely a message or object type)
    count = 0;
    if (DAT_012224a8 != 0) {
        srcData = &DAT_0122232c;
        do {
            // Check if the two fields match expected labels
            if (((undefined1*)srcData[-1] == &LAB_00505b10) &&
                ((undefined*)*srcData == &DAT_00505b20)) {
                FUN_00609ca0();  // Found matching entry, perform action then stop
                break;
            }
            count++;
            srcData += 3;  // Each entry is 3 ints (12 bytes)
        } while (count < DAT_012224a8);
    }

    // 5. Modify a vtable pointer and call another function
    // Object at DAT_01206880 has a vtable pointer at offset 0x14.
    // Change it to point to PTR_LAB_01125084, then increment the pointer by 4.
    int* vtablePtr = (int*)(DAT_01206880 + 0x14);
    *(int**)vtablePtr = &PTR_LAB_01125084;
    *vtablePtr = *vtablePtr + 4;  // Adjust vtable entry index

    FUN_0052e510();

    // 6. Clear a set of global state variables (likely frame-specific counters/timers)
    DAT_01197d70 = 0;
    DAT_01197d74 = 0;
    DAT_01197d78 = 0;
    _DAT_01197d7c = 0;
    _DAT_01197d80 = DAT_00e2b118;   // Preset from other globals
    _DAT_01197d84 = DAT_00e2b1a4;
    _DAT_01197d88 = DAT_00e446c4;
    _DAT_01197d8c = DAT_00e2b1a4;
    DAT_01197d90 = 0;
}