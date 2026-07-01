// FUNC_NAME: PresentationManager::handleTrickleTextUpdateAndShowMenu
// Function address: 0x00985590
// Calls helper to retrieve trickle text data (string + callback), updates UI text, shows menu, clears flags.
// Member offsets: m_trickleTextPtr at +0x5C (int), m_flags at +0x68 (ushort)

void __fastcall PresentationManager::handleTrickleTextUpdateAndShowMenu(int* this)
{
    // Locals for callback result structure (filled by getTrickleTextData)
    char* textPtr = nullptr;           // offset +0 (string pointer)
    int   textLengthOrFlag = 0;        // offset +4 (maybe length or valid flag)
    int   unkInt = 0;                  // offset +8 (unused)
    void (*callback)(char*) = nullptr; // offset +12 (function pointer to call with text)

    // Call helper to fill the result structure
    char result = getTrickleTextData(&textPtr);  // FUN_0098f850

    // Decide which text to use: if helper failed or length/flag indicates invalid, use default empty string
    if ((result == 0) || (textLengthOrFlag == 0)) {
        this[0x17] = (int)g_emptyString;   // PTR_DAT_00e575fc  (probably empty)
    } else {
        // Use the retrieved text (or a fallback if null)
        char* finalText = (textPtr != nullptr) ? textPtr : (char*)"";
        this[0x17] = (int)finalText;
    }

    // Notify system that trickle text update is happening
    sendUIEvent("UpdateTrickleText", 0, &DAT_00d873d4, 0);   // FUN_005a04a0

    // Revert the text pointer to empty (reset after update)
    this[0x17] = (int)g_emptyString;

    // Execute callback if text was valid
    if (textPtr != nullptr) {
        callback(textPtr);
    }

    // Call virtual function at vtable+8 (probably update/render after text change)
    (*(void (**)(void))(*this + 8))();

    // Clear bit 1 of m_flags (flag indicating trickle text active)
    *(ushort*)(this + 0x1a) &= 0xFFFD;

    // Notify system to show the menu
    sendUIEvent("MenuShow", 0, &DAT_00d873d4, 0);

    // Clear bit 0 of m_flags (flag indicating menu shown)
    *(ushort*)(this + 0x1a) &= 0xFFFE;
}