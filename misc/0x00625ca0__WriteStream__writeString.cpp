// FUNC_NAME: WriteStream::writeString
// Address: 0x00625ca0
// Appends a string entry (type=4) to the write stream buffer
void WriteStream::writeString(char *str)
{
    // param_1 = this
    // +0x08: current write pointer (uint32_t*)
    // +0x10: pointer to buffer descriptor struct (with size +0x20 and capacity +0x24)
    uint32_t *writePtr = *(uint32_t **)(this + 8);
    
    if (str == nullptr) {
        // Write null entry: type 0, data 0
        *writePtr = 0;
        *(uint32_t *)(this + 8) = (uint32_t)writePtr + 8;
        return;
    }
    
    // Calculate string length (excluding null terminator)
    char *p = str;
    while (*p != '\0') {
        p++;
    }
    int strLen = (int)(p - (str + 1)); // Wait: Ghidra's formula: (p - str - 1) ??? Actually: (int)pcVar3 - (int)(param_2 + 1) = (p) - (str+1) = len - 1? That's off. Let's check: p points after null, so p - (str+1) = (str+len+1) - (str+1) = len. That's correct.
    // Actually: pcVar3 = p (points to null terminator +1?), but the loop increments before checking, so after loop pcVar3 points to char after null? No, do-while: after loop, pcVar3 points to one past the null. So p - (str+1) = (str+len+1) - (str+1) = len. Good.
    
    // Access buffer descriptor
    uint32_t *bufDesc = *(uint32_t **)(this + 0x10);
    // +0x20: current size, +0x24: capacity
    uint32_t size = *(uint32_t *)(bufDesc + 0x20 / 4);
    uint32_t capacity = *(uint32_t *)(bufDesc + 0x24 / 4);
    if (size >= capacity) {
        // Expand or flush buffer (FUN_00627360)
        FUN_00627360(); // likely reserveGrow()
    }
    
    // Write type tag (4 = string)
    *writePtr = 4;
    // Write string data reference/handle (from FUN_00638920)
    writePtr[1] = FUN_00638920(this, str, strLen);
    
    // Advance write pointer
    *(uint32_t *)(this + 8) = (uint32_t)writePtr + 8;
}