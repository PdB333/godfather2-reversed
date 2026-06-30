// FUNC_NAME: CompressedStringWriter::addString
void __thiscall CompressedStringWriter::addString(int thisPtr, char* inputStr, uint inputLen)
{
    void* newBuffer;
    byte* bitPtr;
    char changeFlag;
    byte byteInd;
    uint newSize;
    uint newCap;
    uint matchLen;
    
    // Use default string if input is null
    if (inputStr == (char*)0x0) {
        inputStr = &DAT_00e2f044;  // Global empty string or placeholder
    }
    
    // Find length of common prefix between input and stored string (at this+0x38)
    byteInd = 0;
    if ((byte)inputLen != 0) {
        do {
            if ((*(char*)(byteInd + 0x38 + thisPtr) != inputStr[byteInd]) || (inputStr[byteInd] == '\0')) break;
            byteInd = byteInd + 1;
        } while (byteInd < (byte)inputLen);
    }
    
    inputLen = inputLen & 0xff; // Clamp to byte length
    matchLen = (uint)byteInd;
    
    // Copy the non-matching suffix into the stored string buffer
    _strncpy((char*)(matchLen + 0x38 + thisPtr), inputStr + matchLen, inputLen - matchLen);
    *(char*)(inputLen + 0x38 + thisPtr) = '\0';  // Null-terminate
    
    // Set flag if match length > 2 (triggers compressed encoding)
    changeFlag = (2 < byteInd);
    inputLen = CONCAT31(inputLen._1_3_, (2 < byteInd));  // Not exactly clear, but flag is preserved
    
    // Check if bit buffer needs expansion
    if (*(uint*)(thisPtr + 0x30) < *(int*)(thisPtr + 0x18) + 1U) {
        // Calculate new size in bytes: ((currentBitCapacity + 8) / 8) + 1500
        newSize = (*(uint*)(thisPtr + 0x30) + 8 >> 3) + 0x5dc;
        if (*(uint*)(thisPtr + 0x10) < newSize) {
            // Reallocate if current allocated size is too small
            if (*(char*)(thisPtr + 0x14) != '\0') {
                *(uint*)(thisPtr + 0x10) = newSize;
                newBuffer = _realloc(*(void**)(thisPtr + 0xc), newSize);
                *(void**)(thisPtr + 0xc) = newBuffer;
                *(uint*)(thisPtr + 0x2c) = newSize * 8;  // Update bit capacity
                *(uint*)(thisPtr + 0x30) = newSize * 8;  // Update max bit index
                changeFlag = (byte)inputLen;
                goto LAB_0064c841;
            }
        }
        else {
            *(uint*)(thisPtr + 0x10) = newSize;
        }
        // Set flag to indicate that buffer needs resizing on next write
        *(char*)(thisPtr + 0x1c) = 1;
    }
    else {
LAB_0064c841:
        // Write the match flag bit to the bitstream
        bitPtr = (byte*)((*(uint*)(thisPtr + 0x18) >> 3) + *(int*)(thisPtr + 0xc));
        byteInd = 1 << ((byte)*(uint*)(thisPtr + 0x18) & 7);
        if (changeFlag == '\0') {
            *bitPtr = *bitPtr & ~byteInd;  // Clear bit (no match)
        }
        else {
            *bitPtr = *bitPtr | byteInd;   // Set bit (match found)
        }
        *(int*)(thisPtr + 0x18) = *(int*)(thisPtr + 0x18) + 1;  // Increment bit position
        
        if (changeFlag != '\0') {
            // Compressed encoding: write match length as 8 bits, then suffix bytes
            inputLen = matchLen;
            FUN_0064b810(8, &inputLen);  // Write match length
            FUN_0065afb0(inputStr + matchLen, inputLen - matchLen);  // Write suffix
            return;
        }
    }
    
    // Uncompressed: write entire string as raw bytes
    FUN_0065afb0(inputStr, inputLen);
    return;
}