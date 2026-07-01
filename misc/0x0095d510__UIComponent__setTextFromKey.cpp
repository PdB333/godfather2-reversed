// FUNC_NAME: UIComponent::setTextFromKey
void __thiscall UIComponent::setTextFromKey(int param_2, int param_3)
{
    char *buffer = nullptr;
    int unknownFlag = 0;                // local_c
    code *freeFunc = nullptr;           // local_4, deallocator (never set, potential bug or decompiler omission)

    // Retrieve string using key stored at this+0x20 (likely a string table ID)
    FUN_00604000(*(int *)(this + 0x20), &buffer, 1);

    // Use default empty string if retrieval fails
    const char *str = (buffer != nullptr) ? buffer : &DAT_0120546e;

    // Pass string to another function (likely UI text setter or logging)
    FUN_005c4660(param_2, str, param_3, unknownFlag);

    // Deallocate buffer if allocated (freeFunc should be operator delete or similar)
    if (buffer != nullptr && freeFunc != nullptr)
    {
        freeFunc(buffer);
    }
}