// FUNC_NAME: StringTableManager::GetString
void __thiscall StringTableManager::GetString(void *this, char *destBuffer)
{
    // +0x1c: stringIndex (int)
    int index = *(int *)((char *)this + 0x1c);
    // Global table: array of 16-byte entries (first DWORD: string pointer, second DWORD: possibly length/flags)
    uintptr_t *entry = (uintptr_t *)(g_stringTableArray + index * 0x10);
    char *src = (char *)*entry;
    if (src == (char *)0x0) {
        src = (char *)&defaultString; // DAT_0120546e
    }
    // Copy up to 0x80 bytes (128) from src to destBuffer
    // FUN_005c4660 is likely a strncpy or memcpy
    stringCopy(destBuffer, src, 0x80, entry[1]);
}