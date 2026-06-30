// FUNC_NAME: FileStream::~FileStream

void __fastcall FileStream::~FileStream(void* thisPtr)
{
    // +0x18: Windows handle (INVALID_HANDLE_VALUE = 0xFFFFFFFF)
    HANDLE hFile = *(HANDLE*)((char*)thisPtr + 0x18);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        *(uint32_t*)((char*)thisPtr + 0x18) = 0xFFFFFFFF;
    }

    // +0x14: pointer to an intermediate read buffer
    void* readBuffer = *(void**)((char*)thisPtr + 0x14);
    if (readBuffer != nullptr)
    {
        FUN_009c8eb0(readBuffer);   // deallocate read buffer
        *(uint32_t*)((char*)thisPtr + 0x14) = 0;
    }

    // +0x2c: pointer to another buffer (likely decompression or staging)
    void* stagingBuffer = *(void**)((char*)thisPtr + 0x2c);
    if (stagingBuffer != nullptr)
    {
        FUN_009c8f10(stagingBuffer); // deallocate staging buffer
        *(uint32_t*)((char*)thisPtr + 0x2c) = 0;
    }

    // +0x04: pointer to the actual data buffer (raw file data)
    void* dataBuffer = *(void**)((char*)thisPtr + 0x04);
    // +0x08: duplicate of data buffer pointer (maybe for iteration)
    *(void**)((char*)thisPtr + 0x08) = dataBuffer;
    if (dataBuffer != nullptr)
    {
        FUN_009c8f10(dataBuffer);   // deallocate data buffer
    }

    return;
}