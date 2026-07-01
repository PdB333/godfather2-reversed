// FUNC_NAME: SomeGameObject::updateTextDisplay
void __thiscall SomeGameObject::updateTextDisplay(void *param_2, int param_3)
{
    // Struct returned by string retrieval (pointer + deallocator)
    struct StringData {
        char *buffer;            // +0x00
        uint32_t size;           // +0x04 (unused here)
        uint32_t unused;         // +0x08
        void (*deallocator)(char*); // +0x0C
    };

    StringData strData;
    strData.buffer = nullptr;
    strData.size = 0;
    strData.unused = 0;
    strData.deallocator = nullptr;

    // Retrieve string from internal resource (offset 0x28 is likely a string ID or resource handle)
    FUN_00603d30(*(uint32_t*)(this + 0x28), &strData, 1);

    char *textPtr = strData.buffer;
    if (textPtr == nullptr) {
        textPtr = &DAT_0120546e; // Default fallback string
    }

    // Set the text on the target UI element or string buffer
    FUN_005c4660(param_2, textPtr, param_3, strData.size);

    // Free allocated string if present
    if (strData.buffer != nullptr) {
        strData.deallocator(strData.buffer);
    }
}