// FUNC_NAME: UIComponent::buildDisplayString
void __thiscall UIComponent::buildDisplayString(UIComponent* this)
{
    // Check if data is available (offset +0x5c flags availability)
    if (*(int*)((uint8_t*)this + 0x5c) == 0)
        return;

    // Initialize a wide‑character string builder (FUN_0098a350)
    wchar_t* builder = nullptr;
    int builderLen = 0;
    int field_58 = 0;               // unused local
    FUN_0098a350(&builder, 1);       // builder created, capacity hint = 1

    wchar_t* finalString = nullptr;
    int finalLen = 0;                // may be used by building functions
    void* cleanupFunc = nullptr;     // pointer to free function

    if (builderLen != 0)             // builder was allocated
    {
        // Append two characters (probably newline or colour code)
        FUN_004dba80(&DAT_00e337cc, 1);   // append wide char at 0x00e337cc
        FUN_004dba80(&DAT_00e337cd, 1);   // append wide char at 0x00e337cd

        // Format some numbers into the builder (FUN_004dbf70 takes multiple args)
        FUN_004dbf70(local_10, local_c, builder, builderLen);   // format 1
        FUN_004dbf70(local_30, local_2c, local_20, local_1c);   // format 2

        wchar_t* appendSource = local_40;
        if (appendSource == nullptr)
            appendSource = &DAT_00e2df14;   // default empty wide string
        FUN_004dbb10(appendSource, 0, local_3c);  // append integer

        // Free temporary buffers
        if (local_40 != nullptr)
            (local_34)(local_40);
        if (local_30 != nullptr)
            (local_24)(local_30);

        // Finalize builder into finalString (FUN_004ddaf0)
        wchar_t* srcForFinal = builder;
        if (srcForFinal == nullptr)
            srcForFinal = &DAT_00e2df14;
        FUN_004ddaf0(srcForFinal, &finalString);

        // Free more temporaries
        if (local_20 != nullptr)
            (pcStack_14)(local_20);
        if (local_10 != nullptr)
            (pcStack_4)(local_10);

        // If no final string produced, use default global constant
        if (finalString == nullptr)
            finalString = &DAT_0120546e;
    }
    else
    {
        // Builder was empty, use default
        finalString = &DAT_0120546e;
    }

    // Store the constructed string at offset +0x140 (likely a wide string member)
    FUN_0059eb30((uint8_t*)this + 0x140, finalString);

    // Cleanup builder and final string if dynamically allocated
    if (finalString != nullptr && finalString != &DAT_0120546e)
        (local_44)(finalString);
    if (builder != nullptr)
        (pcStack_54)(builder);
}