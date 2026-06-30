// FUNC_NAME: convertIntToStringAndSet

void convertIntToStringAndSet(void* thisPtr, int value)
{
    char buffer[256];
    __snprintf(buffer, sizeof(buffer), "%d", value);
    // Call underlying string setter at 0x00604c10
    // Signature: void __thiscall someSetter(void* thisPtr, const char* str)
    ((void(__thiscall*)(void*, const char*))0x00604c10)(thisPtr, buffer);
}