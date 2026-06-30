// Function: 0x00422770 - Getter/setter for a pointer field at offset +0x178
// This simple pattern is common in EA EARS engine for property access.
// FUNC_NAME: setUnknownPointerAtOffset178

void* __thiscall setUnknownPointerAtOffset178(void* thisPtr, void* newValue)
{
    void* oldValue = *(void**)((char*)thisPtr + 0x178);
    *(void**)((char*)thisPtr + 0x178) = newValue;
    return oldValue;
}