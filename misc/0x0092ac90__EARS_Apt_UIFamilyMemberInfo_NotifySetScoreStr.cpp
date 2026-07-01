// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_NotifySetScoreStr
// FUNC_NAME: RapSheetStat::updateDisplay
void __fastcall RapSheetStat::updateDisplay(int this) // this = param_1
{
    char cVar1;
    undefined4 uVar2;
    char *pcVar4;
    float value;
    longlong totalSeconds;
    char *formattedString;
    undefined4 uStack_c;
    undefined4 uStack_8;
    // Pointer to allocated string buffer (heap allocated, freed via function pointer)
    void *pBuffer;

    // Get the value source (e.g. from a control)
    uVar2 = (*(code **)(*(int *)(this + 0x6c)))[0](); // vtable[0] returns something
    uVar2 = FUN_004dafd0(uVar2); // convert to a value?
    value = 0.0f;
    cVar1 = FUN_008934e0(uVar2, &value); // retrieve the actual float
    if (cVar1 == '\0') {
        return;
    }

    pBuffer = nullptr;
    uStack_c = 0;
    uStack_8 = 0;
    // Custom deallocator function pointer (often stored in a register or structure)
    void (*deallocFn)(void*) = nullptr;

    switch (*(int *)(this + 0x68)) { // m_formatType
    case 0:
        FUN_00603d30(value, &pBuffer, 1); // format as plain float (no unit)
        break;
    case 1:
        totalSeconds = (longlong)ROUND(value);
        FUN_00604250(
            (int)(totalSeconds / 0xe10),            // hours
            (int)((totalSeconds / 0x3c) % 0x3c),    // minutes
            (int)(totalSeconds % 0x3c),              // seconds
            &pBuffer
        ); // format as HH:MM:SS
        break;
    case 2:
        FUN_00603da0(value, 1, &pBuffer, 1); // format with 1 decimal?
        pcVar4 = " $rapsheet_mph"; // unit suffix
        goto LAB_0092adaf;
    case 3:
        FUN_00603da0(value, 1, &pBuffer, 1);
        pcVar4 = " $rapsheet_miles";
LAB_0092adaf:
        FUN_004d4300(pcVar4); // append unit to the formatted string (in pBuffer)
        break;
    default:
        goto switchD_0092acf3_default;
    }

    formattedString = (char *)pBuffer;
    if (pBuffer == nullptr) {
switchD_0092acf3_default:
        formattedString = &DAT_0120546e; // default empty/error string
    }

    // Update the UI control
    uVar2 = (*(code **)(*(int *)(this + 0x6c) + 4))(uStack_c); // vtable[1] (maybe setSomething)
    uVar2 = (*(code **)(*(int *)(this + 0x6c)))[0](formattedString, uVar2); // vtable[0] (setText?)
    FUN_005c4660(uVar2); // refresh/redraw

    if (pBuffer != nullptr) {
        deallocFn(pBuffer); // free the temporary string buffer
    }
    return;
}