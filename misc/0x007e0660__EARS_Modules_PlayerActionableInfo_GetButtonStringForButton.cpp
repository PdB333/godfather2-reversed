// Xbox PDB: EARS_Modules_PlayerActionableInfo_GetButtonStringForButton
// FUNC_NAME: getButtonString
// Address: 0x007e0660
// Role: Converts an internal button enum ID to a UI button string identifier (e.g., "[b=RDUp]")
// Used extensively by FUN_0090bdc0 for building button display strings.

const char* getButtonString(int buttonId)
{
    const char* result = 0;
    switch (buttonId) {
    case 1:
        return "[b=RDUp]";
    case 2:
        return "[b=LSTop]";
    case 3:
        return "[b=RSTop]";
    case 4:
        return "[b=LSBottom]";
    case 5:
        return "[b=RSBottom]";
    case 6:
        return "[b=AnimLSUp]";
    case 7:
        return "[b=AnimLSLeft]";
    case 8:
        return "[b=AnimLSRight]";
    case 9:
        return "[b=AnimRSUp]";
    case 10:
        return "[b=AnimRSDepressed]";
    case 11:
        return "[b=AnimLSDepressed][b=AnimRSDepressed]";
    case 12:
        return "[b=AnimCtrlForward]";
    case 13:
        return "[b=AnimCtrlLeft]";
    case 14:
        return "[b=AnimCtrlRight]";
    case 15:
        result = "[b=AnimCtrlRotate]";
    }
    return result;
}