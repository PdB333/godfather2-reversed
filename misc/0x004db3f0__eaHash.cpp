// FUNC_NAME: eaHash
int eaHash(int initialHash, const byte* data, int length)
{
    if (data != nullptr)
    {
        const byte* end = data + length;
        while (data < end)
        {
            byte b = *data;
            data++;
            initialHash = initialHash * 0x1003f + b;  // EA's standard hash (often called "EAHash")
        }
    }
    return initialHash;
}