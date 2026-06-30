// FUNC_NAME: DataChunk::parseFromBuffer
void DataChunk::parseFromBuffer(void* buffer) {
    bool isInline;
    uint32_t magic;
    char* decodedBuffer;
    int32_t iVar8;
    int32_t resultLength;
    RefCountedString* stringObj;

    // Allocate 0x38-byte working buffer
    decodedBuffer = (char*)malloc(0x38);
    if (!decodedBuffer) return;

    // Extract header from input buffer (param_2)
    char* srcString = *(char**)((int)buffer + 0xc);        // +0xc: source string pointer
    uint32_t srcLen = *(uint32_t*)((int)buffer + 0x10);    // +0x10: source string length

    // Check first byte: 0 = global reference, non-zero = inline data
    isInline = (srcString[0] != '\0');                      // +0x14: flag

    if (srcLen > 4) {
        // Read next 4 bytes as magic number
        magic = (srcString[1] << 24) | (srcString[2] << 16) | (srcString[3] << 8) | srcString[4];
        this->m_magic = magic;                              // +0x10

        // Decode remaining bytes (after first 5) into the working buffer
        if (decodeBuffer(srcString + 5, srcLen - 5, decodedBuffer) == 0) {
            this->m_decodedBuffer = decodedBuffer;         // +0x0c

            if (isInline) {
                // Inline data: create a ref-counted string from original source
                stringObj = allocateRefCountedString(0x18); // FUN_009c8e50
                if (stringObj != nullptr) {
                    stringObj->vtable = &PTR_LAB_00e42d64; // vtable for RefCountedString
                    stringObj->field_4 = 0;
                    stringObj->field_8 = 0;
                    stringObj->string = (char*)srcString;   // copy pointer
                    stringObj->length = srcLen;
                    stringObj->field_14 = 0;
                }
                // Replace previous string object (with ref-counting)
                if (this->m_stringObject != nullptr) {
                    if (--(this->m_stringObject->refCount) == 0) {
                        this->m_stringObject->destroy();
                    }
                }
                this->m_stringObject = stringObj;
                if (stringObj != nullptr) {
                    stringObj->refCount++;
                }
                updateState();   // FUN_0064b4e0
                this->m_state = 1;   // +0x20
            } else {
                // Global reference: store magic in global tag, then process
                g_chunkTag[0] = (magic >> 24) & 0xFF;
                g_chunkTag[1] = (magic >> 16) & 0xFF;
                g_chunkTag[2] = (magic >> 8) & 0xFF;
                g_chunkTag[3] = magic & 0xFF;

                resultLength = 0x7fb;  // initial code
                if (processGlobalChunk(&g_chunkData, &resultLength, 1, decodedBuffer) == 0) {
                    int32_t newLength = resultLength + 5;
                    stringObj = allocateRefCountedString(0x18);
                    if (stringObj != nullptr) {
                        stringObj->vtable = &PTR_LAB_00e42d64;
                        stringObj->field_4 = 0;
                        stringObj->field_8 = 0;
                        stringObj->string = &g_chunkTag[0];
                        stringObj->length = newLength;
                        stringObj->field_14 = 0;
                    }
                    finalizeGlobal();     // FUN_0065e0e0
                    updateState();        // FUN_0064b4e0
                    updateState();        // FUN_0064b4e0
                    this->m_state = 1;
                    return;
                } else {
                    // Error path?
                }
            }
        }
    }
    if (decodedBuffer) {
        free(decodedBuffer);
    }
}