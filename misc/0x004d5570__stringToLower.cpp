// FUNC_NAME: stringToLower
void __fastcall stringToLower(int *stringMeta) // stringMeta[0] = char* buffer, stringMeta[1] = length
{
    uint i = 0;
    if (stringMeta[1] != 0) {
        char *buffer = (char *)stringMeta[0];
        do {
            char ch = buffer[i];
            // Convert uppercase letters (A-Z) to lowercase by adding 0x20
            if ((uint)(ch - 'A') < 0x1A) {
                ch += ' ';
            }
            buffer[i] = ch;
            i++;
        } while (i < (uint)stringMeta[1]);
    }
}