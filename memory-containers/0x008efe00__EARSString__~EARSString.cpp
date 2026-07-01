// FUNC_NAME: EARSString::~EARSString
void __fastcall EARSString::~EARSString(EARSString* this)
{
    // Temporary 8-byte buffer for possible small string optimization transfer
    char tempBuffer[8];

    // Internal helper that copies string data to the stack buffer before freeing
    // param1: destination buffer (tempBuffer)
    // param2: this pointer (EARSString object)
    // param3: first 4 bytes of the heap-allocated data (may encode size/flag)
    // param4: this pointer again
    // param5: pointer to the heap data (this->mData)
    unknownHelper(tempBuffer, this, *(uint32_t*)this->mData, this, this->mData);

    // Free the heap-allocated data buffer previously stored at +0x04
    memoryDeallocate(this->mData);

    // Reset pointer and size/length fields
    this->mData = 0;   // +0x04: previously owning data pointer
    this->mSize = 0;   // +0x08: likely string size or capacity
}