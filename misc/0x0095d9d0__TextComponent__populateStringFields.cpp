// FUNC_NAME: TextComponent::populateStringFields
void __thiscall TextComponent::populateStringFields(
    int* outDirectHandle,            // param_2: output for raw handle at +0x24
    void* outText0,                  // param_3: output for string from handle at +0x28
    void* outText1,                  // param_4: output for string from handle at +0x2c
    void* outText2,                  // param_5: output for string from handle at +0x1c
    void* outText3,                  // param_6: output for string from handle at +0x20
    int someParam                    // param_7: passed through to string copy (e.g., max length)
)
{
    // +0x24: direct handle (not a string resource)
    *outDirectHandle = *(int*)(this + 0x24);

    const char* resolvedText = nullptr;
    // Note: local_c and local_8 are unused; cleanup function pointer (local_4) is never set - likely a decompilation artifact
    int unknownFlag = 0;            // always 0

    // Resolve string from handle at +0x28
    resolveStringFromHash(*(int*)(this + 0x28), &resolvedText, 1);
    if (resolvedText == nullptr)
        resolvedText = "";          // DAT_0120546e is empty string
    copyStringToOutput(outText0, resolvedText, someParam, unknownFlag);

    // Resolve string from handle at +0x2c
    resolveStringFromHash(*(int*)(this + 0x2c), &resolvedText, 1);
    if (resolvedText == nullptr)
        resolvedText = "";
    copyStringToOutput(outText1, resolvedText, someParam, unknownFlag);

    // Resolve string from handle at +0x1c
    resolveStringFromHash(*(int*)(this + 0x1c), &resolvedText, 1);
    if (resolvedText == nullptr)
        resolvedText = "";
    copyStringToOutput(outText2, resolvedText, someParam, unknownFlag);

    // Resolve string from handle at +0x20
    resolveStringFromHash(*(int*)(this + 0x20), &resolvedText, 1);
    if (resolvedText == nullptr)
        resolvedText = "";
    copyStringToOutput(outText3, resolvedText, someParam, unknownFlag);

    // Potential cleanup if a function pointer was set (unused here, but present in binary)
    if (resolvedText != nullptr && s_cleanupFunc != nullptr)
        s_cleanupFunc(resolvedText);
}