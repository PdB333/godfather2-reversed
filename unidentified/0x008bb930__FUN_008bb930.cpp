// FUNC_NAME: SomeClass::deserializeFields
void __thiscall SomeClass::deserializeFields(void* stream) {
    char dataAvailable;
    int readInt;
    uint readType;

    // Initialize stream reading
    FUN_008bb320(stream);
    // Set a filter/mask for reading (likely a version or type mask)
    FUN_0043aff0(stream, 0x2ffc1ffd);

    dataAvailable = FUN_0043b120(); // Check if more data to read
    while (dataAvailable == 0) { // Continue until no data left (maybe inverted logic?)
        FUN_0043b210(); // Read a token? Possibly skip alignment or read next type indicator
        readType = FUN_0043ab70(); // Read field type ID
        switch (readType) {
        case 0:
            FUN_0043b210(); // Read something (maybe length)
            readInt = FUN_0043ab90(); // Read an integer (resource/asset ID or string ID)
            // Assign to field at +0x290 (likely a resource handle or string)
            FUN_00408980(this + 0x290, readInt);
            break;
        case 1:
            readInt = FUN_0043b210(); // Returns a pointer to a buffer? Actually returns an int
            // Copy a 32-bit value from the buffer at offset 8 into field at +0x298
            *(int*)(this + 0x298) = *(int*)(readInt + 8);
            break;
        case 2:
            FUN_0043b210(); // Read again
            readInt = FUN_0043ab90(); // Read integer
            // Assign to field at +0x29c
            FUN_00408980(this + 0x29c, readInt);
            break;
        case 3:
            readInt = FUN_0043b210(); // Read pointer/buffer
            // Copy value to field at +0x2a4
            *(int*)(this + 0x2a4) = *(int*)(readInt + 8);
            break;
        }
        FUN_0043b1a0(); // Advance or normalize stream position
        dataAvailable = FUN_0043b120(); // Check again for more data
    }
    return;
}