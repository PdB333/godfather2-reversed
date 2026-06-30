// FUNC_NAME: ConfigFileReader::skipCommentLines
void __thiscall ConfigFileReader::skipCommentLines(uint param1, uint param2)
{
    // Structure offsets (relative to 'this'): 
    // +0x00: currentByte (uint) - last read byte
    // +0x04: someFlag1 (uint)
    // +0x08: someFlag2 (uint)
    // +0x14: typeID (uint) - set to 0x11f
    // +0x1C: zeroed field
    // +0x20: param1 (uint) - initial buffer size or similar
    // +0x24: pointer to underlying buffered stream (InputStream*)
    // +0x2C: param2 (uint)
    this[0x20/4] = param1;   // +0x20
    this[0x2C/4] = param2;   // +0x2C
    this[0x14/4] = 0x11f;    // +0x14
    this[0x24/4] = (uint)in_EAX; // underlying stream object (this in EAX)
    this[0x1C/4] = 0;        // +0x1C
    this[0x04/4] = 1;        // +0x04
    this[0x08/4] = 1;        // +0x08

    // Read first byte from underlying stream
    uint currentByte = readByteFromStream();
    this[0x00/4] = currentByte; // +0x00

    // If the first byte is '#', skip the rest of the line
    if (currentByte == 0x23) // '#'
    {
        do {
            currentByte = readByteFromStream();
            this[0x00/4] = currentByte;
        } while ((currentByte != 0x0A) && (currentByte != 0xFFFFFFFF)); // newline or EOF
    }
}

// Helper: reads one byte from the buffered input stream (pointed by this[0x24])
uint ConfigFileReader::readByteFromStream()
{
    uint result;
    int* streamObj = (int*)this[0x24/4]; // underlying stream pointer
    int count = *streamObj; // streamObj[0] = remaining count

    if (count == 0) {
        // Buffer empty: call virtual read method
        int* params = streamObj + 1; // streamObj[1] = buffer pointer, streamObj[2] = function, streamObj[3] = context
        byte* buffer = (byte*)(*(code*)params[1])(); // This is a simplified version – actual call:
        // The real call is (*(code*)piVar2[2])(0, piVar2[3], &param_2);
        // We'll simulate it as a function that fills a buffer and returns pointer.
        // For simplicity, we treat it as VirtualRead(0, context, &size).
        // Here we just use the decompiled logic directly.
        // (Inline the decompiled logic for accuracy)
        int iVar1 = *streamObj;
        *streamObj = iVar1 - 1;
        if (iVar1 == 0) {
            int* piVar2 = (int*)this[0x24/4];
            byte* pbVar3;
            uint tempSize;
            pbVar3 = (byte*)(*(code*)piVar2[2])(0, piVar2[3], &tempSize);
            if ((pbVar3 == (byte*)0x0) || (tempSize == 0)) {
                result = 0xFFFFFFFF;
            } else {
                piVar2[1] = (int)pbVar3;
                *piVar2 = tempSize - 1;
                result = (uint)*pbVar3;
                piVar2[1] = (int)(pbVar3 + 1);
            }
        } else {
            byte* pbVar3 = *(byte**)(this[0x24/4] + 4);
            result = (uint)*pbVar3;
            *(byte**)(this[0x24/4] + 4) = pbVar3 + 1;
        }
    } else {
        // Read directly from buffer
        byte* bufferPos = *(byte**)(this[0x24/4] + 4);
        result = (uint)*bufferPos;
        *(byte**)(this[0x24/4] + 4) = bufferPos + 1;
        *streamObj = count - 1;
    }
    return result;
}