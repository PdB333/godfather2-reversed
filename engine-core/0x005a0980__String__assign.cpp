// FUNC_NAME: String::assign
void String::assign(const char* src)
{
    // +0x00: length (size_t)
    // +0x04: capacity (size_t)
    // +0x08: buffer pointer (char*)
    // +0x0C: inline buffer (16 bytes)
    // +0x1C: ? (unused?)
    size_t* psVar1;
    char* pcVar3;
    size_t sVar4;
    size_t* thisPtr; // unaff_ESI
    const char* srcStr; // unaff_EDI

    // Initialize string state (SSO: pointer points to inline buffer)
    psVar1 = thisPtr + 3;               // +0x0C (inline buffer start)
    thisPtr[0] = 0;                     // length = 0
    thisPtr[1] = 0;                     // capacity = 0
    thisPtr[2] = (size_t)psVar1;       // buffer = inline buffer
    psVar1[0] = 0;                     // inline buffer[0..3] = 0
    psVar1[1] = 0;                     // inline buffer[4..7] = 0
    thisPtr[5] = 0;                    // +0x14 unknown, zeroed
    thisPtr[6] = 0;                    // +0x18 unknown, zeroed

    // Handle null source (throw exception or abort)
    if (src == nullptr) {
        FUN_0059c140();                // likely error handler
    }

    // Measure source length
    size_t srcLen = 0;
    pcVar3 = const_cast<char*>(src);
    while (*pcVar3 != '\0') {
        srcLen++;
        pcVar3++;
    }

    // Store length
    thisPtr[0] = srcLen;

    // If length exceeds inline buffer (15 characters), allocate heap storage
    if (srcLen > 15) {
        sVar4 = srcLen + 1;
        if (sVar4 != 0) {
            sVar4 = (*DAT_0119caf0)(sVar4, 0);   // allocator function (new/malloc)
        }
        thisPtr[2] = sVar4;                     // update buffer pointer
    }

    // Copy string content (including final null)
    _memcpy((void*)thisPtr[2], src, srcLen);
    *(char*)(thisPtr[2] + srcLen) = '\0';

    // Set capacity to current length (or stored length for later realloc checks)
    thisPtr[1] = thisPtr[0];
    return;
}