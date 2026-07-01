// FUNC_NAME: Entity::getLocalizedText

void __thiscall Entity::getLocalizedText(char* outName, char* outDescription, char* outTip, int maxLen)
{
    const char* str;
    
    // Get localized name from resource handle at offset 0x14
    getResourceString(*(uint*)((uint)this + 0x14), &str, 1);
    if (str == (const char*)0x0) {
        str = &DAT_0120546e;  // default empty string
    }
    copyStringSafe(outName, str, maxLen, 0);
    
    // Get localized description from resource handle at offset 0x30
    getOtherResourceString(*(uint*)((uint)this + 0x30), &str, 1);
    if (str == (const char*)0x0) {
        str = &DAT_0120546e;
    }
    copyStringSafe(outDescription, str, maxLen, 0);
    
    // Get localized tip from resource handle at offset 0x34
    getOtherResourceString(*(uint*)((uint)this + 0x34), &str, 1);
    if (str == (const char*)0x0) {
        str = &DAT_0120546e;
    }
    copyStringSafe(outTip, str, maxLen, 0);
    
    // Note: Original code had an uninitialized function pointer check here,
    // likely a decompilation artifact – omitted.
}