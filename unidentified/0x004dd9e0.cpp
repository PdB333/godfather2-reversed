// FUN_NAME: BinaryBuffer::parseTokenBuffer
void BinaryBuffer::parseTokenBuffer() {
    // param_1 is the 'this' pointer pointing to a BinaryBuffer structure.
    // Structure layout: +0x00 data pointer, +0x04 length (int)
    char* current = *(char**)this; // +0x00
    if (current == nullptr) {
        current = &DAT_0120546e; // default buffer (global)
    }
    char* end = current + *(int*)(this + 4); // +0x04 length

    while (current < end) {
        // Token header: first 2 bytes = type/size? Actually token length is computed by helper, and a short flag is returned.
        short tokenFlag = 0;
        int tokenSize = FUN_004dd960(&current, &tokenFlag); // returns size to advance, also sets flag
        if ((short)tokenFlag != 0) {
            // Process token: address of current token (before advancing) is passed as pointer-to-pointer
            char* tokenPtr = current;
            FUN_004dbd90(&tokenPtr, 0, 1);
        }
        current += tokenSize;
    }
}