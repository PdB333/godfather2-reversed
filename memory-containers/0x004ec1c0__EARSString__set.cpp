// FUNC_NAME: EARSString::set
void __thiscall EARSString::set(EARSString* this, const char* newString)
{
    char* oldString = *(char**)(this + 0x20);
    size_t oldLen;
    if (oldString == nullptr) {
        oldLen = 0;
    } else {
        oldLen = strlen(oldString);
    }

    if (newString != nullptr) {
        size_t newLen = strlen(newString) + 1; // include null terminator
        if (oldLen < newLen) {
            if (oldString != nullptr) {
                // Free old buffer using allocator
                (*(void(__thiscall**)(void*, int))(*DAT_01194538 + 4))(oldString, 0);
                *(char**)(this + 0x20) = nullptr;
            }
            // Allocate new buffer with flags (allocation method, alignment, etc.)
            AllocFlags flags = {2, 0x10, 0}; // likely structure for allocation flags
            char* newBuffer = (*(char*(__thiscall*)(size_t, AllocFlags*))*DAT_01194538)(newLen, &flags);
            *(char**)(this + 0x20) = newBuffer;
            if (newBuffer == nullptr) {
                return;
            }
            // Copy string
            strcpy(newBuffer, newString);
            return;
        }
        // New string is not longer; copy into existing buffer
        if (newString != nullptr) {
            strcpy(oldString, newString);
            return;
        }
    }

    // newString is null, free existing buffer if any
    if (oldString != nullptr) {
        (*(void(__thiscall**)(void*, int))(*DAT_01194538 + 4))(oldString, 0);
        *(char**)(this + 0x20) = nullptr;
    }
}