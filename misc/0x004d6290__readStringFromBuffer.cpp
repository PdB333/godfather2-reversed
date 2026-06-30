// FUNC_NAME: readStringFromBuffer
bool readStringFromBuffer(char* dest, char** outNextPos, uint maxLen)
{
    char* src = (char*)allocTempBuffer(1, 0);               // internal buffer allocation (FUN_004d5e10)
    int result = readToken(src, 1, outNextPos);               // parse token, update outNextPos to end (FUN_004d5fd0)
    *outNextPos = (char*)result;                             // store pointer after the string
    size_t count = (char*)result - src;                      // length of the string (excluding null terminator)

    // Cap length to leave room for null terminator if maxLen is specified
    if (maxLen <= count && maxLen != 0) {
        count = maxLen - 1;
    }

    if (count != 0) {
        strncpy(dest, src, count);
        dest[count] = '\0';
        return true;
    }

    dest[0] = '\0';
    return false;
}