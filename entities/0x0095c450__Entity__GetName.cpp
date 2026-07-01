// FUNC_NAME: Entity::GetName

// Extract the name string from the internal buffer (offset +0x9c, char[0x80]) into a caller-provided buffer.
// Uses a safe string copy with explicit length to avoid overflow.
void __thiscall Entity::GetName(char* dest) const
{
    const char* src = reinterpret_cast<const char*>(this + 0x9c); // +0x9c: name buffer (char[128])
    int len = 0;
    while (src[len] != '\0')
    {
        len++;
    }
    // Safe copy function: EARS_strncpy(dest, src, maxLen, actualLen)
    EARS_strncpy(dest, src, 0x80, len);
}