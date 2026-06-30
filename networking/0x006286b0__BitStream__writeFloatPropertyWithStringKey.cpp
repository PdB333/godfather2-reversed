// FUNC_NAME: BitStream::writeFloatPropertyWithStringKey
void __thiscall BitStream::writeFloatPropertyWithStringKey(BitStream* this, int param_2) // param_2 is the float value (converted from int/float)
{
    // this is a bit stream with buffer and property list
    // offset +0x8: write pointer (current position in property list)
    // offset +0xC: read pointer (base of property list?)
    // offset +0x10: pointer to a structure with +0x20 and +0x24 (bit count and capacity)
    // in_EAX is an index passed in register (likely the index of a property to overwrite)
    // The function writes a key-value pair where key is a constant string (DAT_00e4156c) and value is param_2 as float.
    // It first tries to find if the key already exists in the property list; if so, overwrites it.
    // Otherwise appends a new entry.

    int index = in_EAX; // register variable, possibly passed from caller

    // Bounds check and update index based on current list size
    if ((index + 9999U) < 10000) { // likely a heuristic check for index validity
        index = index + 1 + ((*(int*)(this + 8) - *(int*)(this + 0xC)) >> 3);
    }

    // Check if there is space in the bit stream (not property list) to write a header
    if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
        FUN_00627360(); // likely an assert or stream overflow handler
    }

    // Write the key string (type 4 entry with string handle)
    undefined4* writePtr = *(undefined4**)(this + 8);
    *writePtr = 4; // type: string
    undefined4 stringHandle = FUN_00638920(this, &DAT_00e4156c, 1); // write string and get handle/offset
    writePtr[1] = stringHandle;
    *(int*)(this + 8) = *(int*)(this + 8) + 8; // advance write pointer

    FUN_00625e70(); // possibly compute checksum or update internal state

    int searchResult = FUN_00628380(this, 1); // search for existing property with same key? returns index or -1
    if (searchResult >= 0) {
        // Key found: overwrite the existing entry
        // Ensure space in bit stream for the value write
        if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
            FUN_00627360();
        }

        writePtr = *(undefined4**)(this + 8);
        *writePtr = 4;
        stringHandle = FUN_00638920(this, &DAT_00e4156c, 1);
        writePtr[1] = stringHandle;
        *(int*)(this + 8) = *(int*)(this + 8) + 8;

        // Write the float value (type 3 entry)
        writePtr = *(undefined4**)(this + 8);
        *writePtr = 3; // type: float
        writePtr[1] = (float)param_2; // convert to float
        *(int*)(this + 8) = *(int*)(this + 8) + 8;

        // Now find the location of the old entry to overwrite
        int oldEntryOffset = *(int*)(this + 8);
        int sourcePtr;
        if (index < 1) {
            sourcePtr = FUN_00625430(); // perhaps get base of property list?
        } else {
            sourcePtr = *(int*)(this + 0xC) + -8 + index * 8; // index into existing list
        }

        // Copy the new data into the old slot (overwrite the type and value)
        undefined4* dest = (undefined4*)FUN_00638020(this, *(undefined4*)(sourcePtr + 4)); // use appropriate function to get write destination
        *dest = *(undefined4*)(oldEntryOffset - 8);
        dest[1] = *(undefined4*)(oldEntryOffset - 4);
        *(int*)(this + 8) = *(int*)(this + 8) - 0x10; // rewind write pointer by 16 bytes (2 entries)
        return;
    }

    // Key not found: append new property
    FUN_00628430(); // likely prepare for append

    // Get the source data to copy from the key we just wrote? Actually it uses index to read from list
    undefined4* source;
    if (index < 1) {
        source = (undefined4*)FUN_00625430();
    } else {
        source = (undefined4*)(*(int*)(this + 0xC) + -8 + index * 8);
    }

    // Write the key again? Actually this seems to copy an existing entry into the current write position
    writePtr = *(undefined4**)(this + 8);
    *writePtr = *source;
    writePtr[1] = source[1];
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    // Write the float value
    writePtr = *(undefined4**)(this + 8);
    *writePtr = 3;
    writePtr[1] = (float)param_2;
    *(int*)(this + 8) = *(int*)(this + 8) + 8;

    int lastEntryOffset = *(int*)(this + 8);
    // Overwrite the initial key entry (the one written first) with the final combined key+value?
    undefined4* dest = (undefined4*)FUN_00638020(this, *(undefined4*)(lastEntryOffset - 0x14)); // offset to the first key entry
    *dest = *(undefined4*)(lastEntryOffset - 8);
    dest[1] = *(undefined4*)(lastEntryOffset - 4);
    *(int*)(this + 8) = *(int*)(this + 8) - 0x18; // rewind by 24 bytes (3 entries)
}
// Note: This reconstruction is approximate due to missing context and the use of in_EAX as a register variable.
// The constant DAT_00e4156c is likely a debug string or property key like "someEventType".
// The functions FUN_00627360, FUN_00625e70, FUN_00628380, FUN_00625430, FUN_00638020, FUN_00628430 are internal stream management functions.