// FUNC_NAME: EARSString::assignFromWide
uint __thiscall EARSString::assignFromWide(int *this, short *wideStr)
{
    short currentChar;
    short *ptr;
    uint wideLen;
    uint i;

    if (wideStr == (short *)0x0) {
        FUN_004d4060(0, 0);
        return this[1];
    }
    currentChar = *wideStr;
    ptr = wideStr;
    while (currentChar != 0) {
        ptr = ptr + 1;
        currentChar = *ptr;
    }
    wideLen = (int)ptr - (int)wideStr >> 1;
    FUN_004d3fe0(wideLen + 1);
    i = 0;
    if (wideLen != 0) {
        do {
            *(char *)(i + *this) = (char)wideStr[i];
            i = i + 1;
        } while (i < wideLen);
    }
    *(undefined1 *)(wideLen + *this) = 0;
    this[1] = wideLen;
    return wideLen;
}