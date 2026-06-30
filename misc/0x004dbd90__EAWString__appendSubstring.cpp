// FUNC_NAME: EAWString::appendSubstring
struct EAWString {
    uint16_t* data;          // +0x00
    int length;              // +0x04 (number of 16-bit characters)
    int capacityBytes;       // +0x08 (allocated byte size)
    void (*dealloc)(void*);  // +0x0C
};

EAWString* EAWString::appendSubstring(const uint16_t* src, int srcOffset, int count) {
    int oldLen = this->length;
    if (oldLen != 0) {
        int newNeededBytes = (oldLen + count) * 2;           // new total size in bytes
        if (newNeededBytes < this->capacityBytes) {
            // fits in existing buffer
            memcpy(this->data + oldLen, src + srcOffset, count * 2);
        } else {
            // need reallocation
            // compute new allocation size: (newLength+1)*2, with overflow guard
            int newAllocBytes = ((oldLen + count) & 0x7FFFFFFF) + 1) * 2;
            uint16_t* newData = (uint16_t*)FUN_009c8e50(newAllocBytes);
            memcpy(newData, this->data, oldLen * 2);
            memcpy(newData + oldLen, src + srcOffset, count * 2);
            if (this->data != nullptr) {
                this->dealloc(this->data);
            }
            this->data = newData;
            this->capacityBytes = newNeededBytes;            // store usable bytes (excluding null terminator)
            this->dealloc = thunk_FUN_009c8eb0;              // set deallocator to standard free
        }
        this->length = oldLen + count;
        this->data[this->length] = 0;                       // null terminate
        return this;
    } else {
        // empty string: delegate to alternate initialisation from substring
        FUN_004dbb10(src, srcOffset, count);
        return this;
    }
}