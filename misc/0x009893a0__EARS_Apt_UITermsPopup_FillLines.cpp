// Xbox PDB: EARS_Apt_UITermsPopup_FillLines
// FUNC_NAME: DebugConsole::addLines
void __thiscall DebugConsole::addLines(int this, int count)
{
    char *lineText;
    int i;
    uint currentLine;
    
    FUN_005a04a0("ClearLines", 0, &DAT_00d9158c, 0);
    currentLine = *(uint *)(this + 0x5c); // +0x5c: current line index in buffer
    if (currentLine < currentLine + count) {
        i = currentLine << 4;
        do {
            lineText = *(char **)(*(int *)(this + 100) + i); // +100: line buffer array (16 bytes per entry)
            if (lineText == (char *)0x0) {
                lineText = &DAT_0120546e; // empty string placeholder
            }
            FUN_005a04a0("AddLine", 0, &DAT_00d9158c, 1, lineText);
            currentLine = currentLine + 1;
            i = i + 0x10;
        } while (currentLine < (uint)(*(int *)(this + 0x5c) + count));
    }
    FUN_005a04a0("UpdateScrollBar", 0, &DAT_00d9158c, 0);
    return;
}