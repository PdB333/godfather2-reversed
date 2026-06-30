// FUNC_NAME: hashStringCaseInsensitive
int hashStringCaseInsensitive(int hash, byte* data, int length)
{
    byte* end;
    uint c;

    if (data == (byte*)0x0) {
        return hash;
    }
    end = data + length;
    if (data < end) {
        do {
            c = (uint)*data;
            // Convert uppercase letters (A-Z, 0x41-0x5A) to lowercase (a-z)
            if (c - 0x41 < 0x1a) {
                c = c + 0x20;
            }
            data = data + 1;
            // Simple hash: mult by 0x1003F and add character
            hash = hash * 0x1003f + c;
        } while (data < end);
    }
    return hash;
}