// FUNC_NAME: UIElement::loadTextFromResources
void __thiscall UIElement::loadTextFromResources(int this, char* outStr1, char* outStr2, char* outStr3, int maxLen)
{
    const char* tempStr;
    const char* defaultStr = &DAT_0120546e; // likely empty string or placeholder

    // Retrieve first string from resource at offset +0x14
    tempStr = nullptr;
    FUN_00604000(*(int*)(this + 0x14), &tempStr, 1); // get resource string (resourceID, out ptr, flags)
    if (tempStr == nullptr) {
        tempStr = defaultStr;
    }
    FUN_005c4660(outStr1, tempStr, maxLen, 0); // copy string to output buffer

    // Retrieve second string from resource at offset +0x3C
    tempStr = nullptr;
    FUN_00603d30(*(int*)(this + 0x3C), &tempStr, 1);
    if (tempStr == nullptr) {
        tempStr = defaultStr;
    }
    FUN_005c4660(outStr2, tempStr, maxLen, 0);

    // Retrieve third string from resource at offset +0x40
    tempStr = nullptr;
    FUN_00603d30(*(int*)(this + 0x40), &tempStr, 1);
    if (tempStr == nullptr) {
        tempStr = defaultStr;
    }
    FUN_005c4660(outStr3, tempStr, maxLen, 0);

    // Dead code: local_4 was never assigned (function pointer set to 0)
    // If local_4 had been set, it would call tempStr as a function.
    // This is likely a leftover from an inline or optimized construct.
    return;
}