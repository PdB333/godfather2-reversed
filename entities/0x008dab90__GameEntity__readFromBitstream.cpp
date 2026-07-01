// FUNC_NAME: GameEntity::readFromBitstream
// Function at 0x008dab90: Deserialization method for game entity from a bitstream.
// Reads fields and calls virtual methods based on flags.

void __thiscall GameEntity::readFromBitstream(int *thisPtr, void *stream)
{
    // Initialize bitstream reading
    initBitstream(stream);
    // Read magic/class ID
    readMagic(stream, 0x1ea6b19a);

    // Loop while there is more data in the stream (hasMoreData returns 0 when not done yet)
    while (hasMoreData(stream) == 0)
    {
        // Read section type from stream
        int sectionType = readSectionType(stream);
        switch (sectionType)
        {
        case 0: // int field at this+0x1BC (offset 0x6f in int units)
        {
            int *data = readDataPointer(stream);
            thisPtr[0x6f] = data[2]; // data[2] corresponds to *(int*)(data + 8)
            break;
        }
        case 1: // int field at this+0x1C0 (offset 0x70)
        {
            int *data = readDataPointer(stream);
            thisPtr[0x70] = data[2];
            break;
        }
        case 2: // int field at this+0x1C4 (offset 0x71)
        {
            int *data = readDataPointer(stream);
            thisPtr[0x71] = data[2];
            break;
        }
        case 3: // int field at this+0x1C8 (offset 0x72)
        {
            int *data = readDataPointer(stream);
            thisPtr[0x72] = data[2];
            break;
        }
        case 4: // 4-int vector field at this+0x1CC (offset 0x73)
        {
            readDataPointer(stream); // advance
            int *vec = readVector4(stream);
            thisPtr[0x73] = vec[0];
            thisPtr[0x74] = vec[1];
            thisPtr[0x75] = vec[2];
            thisPtr[0x76] = vec[3];
            break;
        }
        case 5: // 4-int vector field at this+0x1E0 (offset 0x78)
        {
            readDataPointer(stream);
            int *vec = readVector4(stream);
            thisPtr[0x78] = vec[0];
            thisPtr[0x79] = vec[1];
            thisPtr[0x7a] = vec[2];
            thisPtr[0x7b] = vec[3];
            break;
        }
        case 6: // 4-int vector field at this+0x1F4 (offset 0x7d)
        {
            readDataPointer(stream);
            int *vec = readVector4(stream);
            thisPtr[0x7d] = vec[0];
            thisPtr[0x7e] = vec[1];
            thisPtr[0x7f] = vec[2];
            thisPtr[0x80] = vec[3];
            break;
        }
        case 7: // string field at this+0x194 (offset 0x65)
        {
            readDataPointer(stream);
            char *str = readString(stream);
            setString(thisPtr + 0x65, str); // FUN_004089b0
            break;
        }
        case 8: // string field at this+0x19C (offset 0x67)
        {
            readDataPointer(stream);
            char *str = readString(stream);
            setString(thisPtr + 0x67, str);
            break;
        }
        case 9: // string field at this+0x1A4 (offset 0x69)
        {
            readDataPointer(stream);
            char *str = readString(stream);
            setString2(thisPtr + 0x69, str); // FUN_00408240
            break;
        }
        case 10: // Virtual function call based on flag
        {
            int *data = readDataPointer(stream);
            int *vtable = (int *)*thisPtr;
            if (data[2] == 0) // check flag at offset 8 of data
            {
                // Call virtual function at vtable offset 0x19c
                ((void (__thiscall *)(int *))vtable[0x67])(thisPtr);
            }
            else
            {
                // Call virtual function at vtable offset 0x198
                ((void (__thiscall *)(int *))vtable[0x66])(thisPtr);
            }
            break;
        }
        case 11: // int field from string conversion at this+0x1B0 (offset 0x6c)
        {
            readDataPointer(stream);
            char *str = readString(stream);
            thisPtr[0x6c] = stringToInt(str); // FUN_004dafd0
            break;
        }
        case 12: // int field at this+0x1B4 (offset 0x6d)
        {
            int *data = readDataPointer(stream);
            thisPtr[0x6d] = data[2];
            break;
        }
        case 13: // int field from float at this+0x1B8 (offset 0x6e)
        {
            int *data = readDataPointer(stream);
            float f = *(float *)(data + 2); // reinterpret as float
            thisPtr[0x6e] = (int)(f * g_floatScalar); // scaled by global DAT_00e445c8
            break;
        }
        }
        // Advance to next element in stream
        advanceToNext(stream);
        // Re-check stream end
    }
}