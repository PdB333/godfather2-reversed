// FUNC_NAME: duplicateMemberString
void __fastcall duplicateMemberString(void* thisObj) {
    // Get pointer to string stored at offset 0xF8 in the object
    const char* srcStr = *(const char**)((char*)thisObj + 0xF8);
    int length = 0;
    char c = *srcStr;
    while (c != '\0') {
        ++length;
        c = srcStr[length];
    }
    int copySize = length + 1;
    char* destBuf = (char*)allocateTempBuffer();  // Allocate a temporary buffer
    char* destPtr = destBuf;
    if (copySize != 0) {
        do {
            // Copy character from source to destination; break early if source null (redundant)
            if (destPtr[(int)srcStr - (int)destBuf] == '\0')
                break;
            *destPtr = destPtr[(int)srcStr - (int)destBuf];
            ++destPtr;
            --copySize;
        } while (copySize != 0);
    }
    *destPtr = '\0';
    destBuf[length] = '\0'; // Ensure null termination at original length position
}