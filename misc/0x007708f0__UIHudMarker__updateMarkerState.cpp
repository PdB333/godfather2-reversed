// FUNC_NAME: UIHudMarker::updateMarkerState
void __thiscall UIHudMarker::updateMarkerState(int *thisPtr, char param_bool1, char param_bool2, undefined4 markerArg1, undefined4 markerArg2)
{
    char checkResult;

    // If first bool is false, check if we are in a state that prevents marker updates
    if (param_bool1 == '\0') {
        checkResult = UIHudMarker::isUpdateBlocked(); // FUN_00770820
        if (checkResult != '\0') {
            UIHudMarker::resetAllMarkers(); // FUN_00770710
            return;
        }
        // If second bool is true, show markerArg1
        if (param_bool2 != '\0') {
            (*(void (__thiscall **)(undefined4, int, int, int, float, float))(*thisPtr + 0x2c))(markerArg1, 1, 1, 0, 1.0f, 1.0f);
            *(char *)(thisPtr[0x14] + 0x1e08) = 1; // visibility flag
            return;
        }
    }
    // Default or else: hide markerArg2
    (*(void (__thiscall **)(undefined4, int, int, int, float, float))(*thisPtr + 0x2c))(markerArg2, 1, 1, 0, 1.0f, 1.0f);
    *(char *)(thisPtr[0x14] + 0x1e08) = 0; // visibility flag
    return;
}