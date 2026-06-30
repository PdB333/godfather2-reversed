// FUNC_NAME: stringCopyN
// Bounded string copy that always null-terminates. Copies up to maxLen characters from src to dst, then appends null terminator.
// The function uses __fastcall convention: dst in ECX, src in EDX, maxLen on stack.
void __fastcall stringCopyN(char *dst, const char *src, int maxLen)
{
    if (maxLen != 0) {
        do {
            if (*src == '\0') break;
            *dst = *src;
            dst++;
            src++;
            maxLen--;
        } while (maxLen != 0);
    }
    *dst = '\0';
}