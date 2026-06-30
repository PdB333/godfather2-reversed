// FUNC_NAME: String::assign
int* __thiscall String::assign(int* this, char* src)
{
    char c;
    char* pSrc;
    char* pDst;
    uint newLen;
    int allocResult;
    
    // If src is null or empty, just set length to 0 and null-terminate if buffer exists
    if ((src == (char*)0x0) || (*src == '\0')) {
        this[1] = 0;  // +0x04: length
        if ((char*)*this != (char*)0x0) {
            *(char*)*this = '\0';  // +0x00: buffer pointer
            return this;
        }
    }
    else {
        pDst = (char*)*this;  // +0x00: current buffer
        if (src != pDst) {
            pSrc = src;
            do {
                c = *pSrc;
                pSrc = pSrc + 1;
            } while (c != '\0');
            newLen = (int)pSrc - (int)(src + 1);  // strlen without null terminator
            
            // +0x08: capacity, +0x0C: deallocator function pointer
            if ((uint)this[2] <= newLen) {
                if (pDst != (char*)0x0) {
                    (*(code*)this[3])(pDst);  // free old buffer
                }
                allocResult = FUN_009c8e50(newLen + 1);  // allocate new buffer
                *this = allocResult;  // +0x00: new buffer
                this[2] = newLen;     // +0x08: new capacity
                this[3] = (int)thunk_FUN_009c8eb0;  // +0x0C: deallocator
            }
            _memcpy((void*)*this, src, newLen);  // copy string data
            *(char*)(newLen + *this) = '\0';  // null-terminate
            this[1] = newLen;  // +0x04: set length
        }
    }
    return this;
}