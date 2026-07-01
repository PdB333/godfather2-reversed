// FUNC_NAME: UIPopupTextManager::clearAllTextFields
// Function address: 0x0098e4f0
// Clears and resets all dynamic text fields in a popup UI.
// Loops over two sets of text fields by index: input fields (instance8/input) and static fields (instance3).
// Resets state variables and associated global UI focus.

void __fastcall UIPopupTextManager::clearAllTextFields(void* thisPtr)
{
    uint32_t itemIndex;
    char formattedPath[96]; // local_60, buffer for building UI path strings

    // Loop 1: Clear input text fields (instance8/input) for first mInputTextCount items
    itemIndex = 0;
    if (*(int32_t*)((uint8_t*)thisPtr + 0x74) != 0) { // mInputTextCount
        do {
            // Build path: /text/popup_root/popup/contentPlaceHolderMc/item%i/instance8/input
            formatString(formattedPath, "/text/popup_root/popup/contentPlaceHolderMc/item%d/instance8/input", itemIndex);
            // Get the text field object by path
            void* textField = findTextFieldByPath(formattedPath);
            // Clear or reset the text field
            clearTextField(textField);
            itemIndex++;
        } while (itemIndex < *(uint32_t*)((uint8_t*)thisPtr + 0x74));
    }

    // Loop 2: Clear static text fields (instance3) for remaining items (additional count)
    uint32_t startIndex = *(uint32_t*)((uint8_t*)thisPtr + 0x74); // mInputTextCount
    uint32_t totalItems = startIndex + *(int32_t*)((uint8_t*)thisPtr + 0x80); // mAdditionalTextCount
    while (startIndex < totalItems) {
        // Build path: /text/popup_root/popup/contentPlaceholderMc/item%i/instance3
        formatString(formattedPath, "/text/popup_root/popup/contentPlaceholderMc/item%d/instance3", startIndex);
        // Reset the text field (presumably no input handling)
        resetTextField(formattedPath);
        startIndex++;
    }

    // Global UI cleanup
    clearAllTextFieldsGlobal(); // FUN_0098bfe0
    releaseGlobalFocus((void*)0x00e2f044); // FUN_004d3d90, likely a global focus manager
    debugLog("Clear", 0, (const char*)0x00e3d7ac, 0); // FUN_005a04a0, logging

    // Reset state variables
    *(int32_t*)((uint8_t*)thisPtr + 0x8c) = 0; // mStateVar1
    *(int32_t*)((uint8_t*)thisPtr + 0x90) = 0; // mStateVar2
    *(int32_t*)((uint8_t*)thisPtr + 0x94) = 0; // mStateVar3

    // Additional cleanup
    resetInputHandlers(); // FUN_0098e2f0
    resetPopupContent();  // FUN_0098e3d0

    // Clear flag or reference
    *(int32_t*)((uint8_t*)thisPtr + 0x88) = 0; // mSomeFlag
}