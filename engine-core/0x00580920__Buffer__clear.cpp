// FUNC_NAME: Buffer::clear
void __fastcall Buffer::clear(Buffer* this)
{
    // +0x0C: size of buffer in bytes
    // +0x10: start of buffer data
    int* data = (int*)((char*)this + 0x10);
    int dwordCount = *(int*)((char*)this + 0x0C) >> 2; // number of 16-byte groups

    // Clear 16 bytes (4 DWORDs) per iteration
    for (int i = dwordCount; i > 0; --i)
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
        data += 4;
    }

    // Handle remaining bytes (0-3)
    uint remainingBytes = *(uint*)((char*)this + 0x0C) & 3;
    if (remainingBytes != 0)
    {
        for (uint j = remainingBytes; j > 0; --j)
        {
            *(char*)data = 0;
            data = (int*)((char*)data + 1);
        }
    }
}