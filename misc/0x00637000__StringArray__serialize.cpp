// FUNC_NAME: StringArray::serialize

void StringArray::serialize(StreamContext& stream)
{
    int count = *(int*)(this + 0x24);         // +0x24: number of strings
    int localCount = count;

    // Write total count (4 bytes) to the stream
    stream.write(&localCount, 4);

    if (count <= 0)
        return;

    // Iterate over each string entry
    for (int i = 0; i < count; i++)
    {
        int* stringPtr = *(int**)(this + 0x1c + i * 4); // +0x1c: array of pointers to string structs

        if (stringPtr == nullptr)
        {
            // Write zero length for null entries
            int zero = 0;
            stream.write(&zero, 4);
        }
        else
        {
            // String struct layout: +0x0c = length (including null terminator), +0x10 = data
            int length = *(int*)(stringPtr + 0x0c);   // +0x0c: length field
            length++;                                   // Include null terminator in output
            char* data = (char*)(stringPtr + 0x10);    // +0x10: string data

            // Write length then data
            stream.write(&length, 4);
            stream.write(data, length);
        }
    }
}