// FUNC_NAME: UIScrollList::handleInput
bool __thiscall UIScrollList::handleInput(const wchar_t* inputString)
{
    // Offsets in this object:
    // +0x4: wchar_t string for scroll-up trigger (256 chars max, 0x200 bytes)
    // +0x204: wchar_t string for scroll-down trigger
    // +0x404: wchar_t string for alternative scroll up/down (when m_isReversed != 0)
    // +0x604: wchar_t string for page-up/down trigger
    // +0xa08: bool m_isReversed (1 = reversed scroll order)

    bool m_isReversed = *(char *)(this + 0xa08) != 0;

    if (!m_isReversed) {
        // Normal scroll: first check scroll-up trigger at +0x4
        if (wcscmp((const wchar_t *)(this + 0x4), inputString) == 0) {
            FUN_005a04a0(L"ScrollUp", 0, &DAT_00d8d668, 0);
            return true;
        }
        // Then check scroll-down trigger at +0x204
        if (wcscmp((const wchar_t *)(this + 0x204), inputString) == 0) {
            FUN_005a04a0(L"ScrollDown", 0, &DAT_00d8d668, 0);
            return true;
        }
        // Then check page-up/down trigger at +0x604
        if (wcscmp((const wchar_t *)(this + 0x604), inputString) == 0) {
            FUN_005a04a0(L"PageUpDown", 0, &DAT_00d8d668, 0);
            return true;
        }
        return false;
    } else {
        // Reversed scroll: first check reversed trigger at +0x404
        bool matched = (wcscmp((const wchar_t *)(this + 0x404), inputString) == 0);
        if (!matched) {
            // If not matched, check page-up/down trigger at +0x604
            matched = (wcscmp((const wchar_t *)(this + 0x604), inputString) == 0);
        }
        // If either matched, send UpdateScrolling
        if (matched) {
            FUN_005a04a0(L"UpdateScrolling", 0, &DAT_00d8d668, 0);
        }
        return matched;
    }
}