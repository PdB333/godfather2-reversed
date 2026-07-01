// FUNC_NAME: UIInputHandler::handleInputCommand
// Address: 0x00960cd0
// Role: Compares input string wchar_t* against stored command strings at offsets 0x4, 0x204, 0x404, 0x604.
// If a match is found, dispatches action via FUN_005a04a0 and returns true. Sets a flag at +0xa08 for "StartScrolling".

bool __thiscall UIInputHandler::handleInputCommand(int thisPtr, wchar_t* inputString)
{
    // Offset 0x4: command string for "ScrollUp"
    wchar_t* storedString1 = (wchar_t*)(thisPtr + 0x4);
    if (wcscmp(storedString1, inputString) == 0) {
        FUN_005a04a0(L"ScrollUp", 0, &DAT_00d8d668, 0);
        return true;
    }

    // Offset 0x204: command string for "ScrollDown"
    wchar_t* storedString2 = (wchar_t*)(thisPtr + 0x204);
    if (wcscmp(storedString2, inputString) == 0) {
        FUN_005a04a0(L"ScrollDown", 0, &DAT_00d8d668, 0);
        return true;
    }

    // Offset 0x404: command string for "StartScrolling"
    wchar_t* storedString3 = (wchar_t*)(thisPtr + 0x404);
    if (wcscmp(storedString3, inputString) == 0) {
        FUN_005a04a0(L"StartScrolling", 0, &DAT_00d8d668, 0);
        // +0xa08: scrolling flag (1 = active)
        *(byte*)(thisPtr + 0xa08) = 1;
        return true;
    }

    // Offset 0x604: command string for "PageUpDown"
    wchar_t* storedString4 = (wchar_t*)(thisPtr + 0x604);
    if (wcscmp(storedString4, inputString) == 0) {
        FUN_005a04a0(L"PageUpDown", 0, &DAT_00d8d668, 0);
        return true;
    }

    return false;
}