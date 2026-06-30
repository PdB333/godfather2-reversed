// FUNC_NAME: IsMessageType6
bool IsMessageType6(const char* message)
{
    bool bResult = false;

    if (*message != '\0')
    {
        // Global network manager at address 0x012233f4, stream at offset +0x18
        NetworkStream* pStream = *(NetworkStream**)((char*)0x012233f4 + 0x18);

        // Write the message string into the stream (e.g., for encoding/hashing)
        pStream->WriteString(message);

        // Get a writable buffer from the stream, positioned at (pStream->buffer + 0x40) 
        // and size = (pStream->currentSize - 8) bytes.
        uint32_t* pBuffer = (uint32_t*)pStream->GetWriteBuffer(
            (uint32_t)(pStream + 0x40),  // offset 0x40 from stream base (likely internal buffer start)
            *(int*)((char*)pStream + 8) - 8,  // currentSize - 8
            0
        );

        // Write the first two dwords from the obtained buffer back to the stream's end-8 location
        // (This effectively ensures the header is stored correctly)
        int currentSize = *(int*)((char*)pStream + 8);
        *(uint32_t*)(currentSize - 8) = *pBuffer;
        *(uint32_t*)(currentSize - 4) = pBuffer[1];

        // Read the first dword as a type identifier
        int* pType = (int*)(currentSize - 8);
        if (pType != nullptr)
        {
            bResult = (*pType == 6);
        }

        // Finalize the stream operation (e.g., pop context, free temp)
        pStream->FinishStreamOperation();
    }

    return bResult;
}