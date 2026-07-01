// FUNC_NAME: StreamReader::read20Ints
int __thiscall StreamReader::read20Ints(void* this, int unused, int buffer)
{
    int value;
    int* dst = (int*)this; // treat this as array of 20 ints
    int* src = (int*)buffer; // but buffer is byte offset? Actually buffer is int, used as byte address
    int i;

    // Read first 8 values directly
    dst[0] = readInt32(buffer);
    dst[1] = readInt32(buffer + 4);
    dst[2] = readInt32(buffer + 8);
    dst[3] = readInt32(buffer + 12);
    dst[4] = readInt32(buffer + 16);
    dst[5] = readInt32(buffer + 20);
    dst[6] = readInt32(buffer + 24);
    dst[7] = readInt32(buffer + 28);

    // Read remaining 12 values in a loop
    dst += 8;
    for (i = 0; i < 12; i++)
    {
        dst[i] = readInt32(buffer + 32 + i * 4);
    }

    // Return number of elements read (20)
    return 20;
}