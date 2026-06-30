// FUNC_NAME: OptionManager::getCurrentOptionDisplayString
// Function at 0x006e53b0: Returns a pointer to a localized string or constant based on current game setting
void OptionManager::getCurrentOptionDisplayString(int param_1, int param_2, int* outValue)
{
    int option = getCurrentOptionIndex(); // Calls FUN_00806440, returns enum (0-3)
    switch(option)
    {
    case 0:
        *outValue = 0;
        return;
    case 1:
        *outValue = optionString1; // _DAT_00d5780c
        return;
    case 2:
        *outValue = optionString2; // DAT_00d5eee4
        return;
    case 3:
        *outValue = optionString3; // DAT_00e445ac
        return;
    default:
        *outValue = 0;
        return;
    }
}