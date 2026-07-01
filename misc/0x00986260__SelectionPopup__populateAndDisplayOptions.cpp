// FUNC_NAME: SelectionPopup::populateAndDisplayOptions
void __fastcall SelectionPopup::populateAndDisplayOptions(int thisPtr) // 0x00986260
{
    uint optionIndex;
    char* optionString;
    char** optionArray;

    // +0x50: number of options
    uint optionCount = *(uint*)(thisPtr + 0x50);
    optionIndex = 0;

    if (optionCount != 0) {
        // +0x6c: array of char* option strings (4 bytes each)
        optionArray = (char**)(thisPtr + 0x6c);
        do {
            optionString = *optionArray;
            if (optionString == (char*)0x0) {
                optionString = (char*)0x0120546e; // Default empty string constant
            }
            // AddOption: internal UI call to register a selectable option
            FUN_005a04a0("AddOption", 0, 0x00d90d34, 1, optionString);
            optionIndex = optionIndex + 1;
            optionArray = optionArray + 1;
        } while (optionIndex < optionCount);
    }

    // +0x54: title/instruction string for the popup
    optionString = *(char**)(thisPtr + 0x54);
    if (optionString == (char*)0x0) {
        optionString = (char*)0x0120546e;
    }
    // DisplaySelPupup: show the popup with the given message
    FUN_005a04a0("DisplaySelPupup", 0, 0x00d90d34, 1, optionString);
    
    return;
}