// FUNC_NAME: registerCallbackFunction
void __cdecl registerCallbackFunction(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4)
{
    // Calls an initialization routine
    FUN_00557e20(); // likely some global setup

    // Build a small temporary structure on the stack
    // The structure contains: pointer to a static label pointer (PTR_LAB_00dcf974),
    // a global value (DAT_00e445dc), and param4.
    struct TempCallbackData {
        void** callbackTable;   // offset 0: pointer to static label pointer array
        uint32_t globalData;    // offset 4: some global constant or pointer
        uint32_t userParam;     // offset 8: the 4th parameter passed
    } tempData;
    tempData.callbackTable = &PTR_LAB_00dcf974;
    tempData.globalData = DAT_00e445dc;
    tempData.userParam = param4;

    // Call the actual registration function (likely from EARS framework)
    // Parameters: param2, param1, param3, pointer to the temp structure
    FUN_00c09cc0(param2, param1, param3, &tempData);
}