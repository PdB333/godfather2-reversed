// Xbox PDB: EARS_Apt_UIHud_ShowPressureMeter
// FUNC_NAME: UIHud::displayNpcInfo
void __thiscall UIHud::displayNpcInfo(UIHud *this, int *someNpcData)
{
    char cVar1;
    int managerPtr;
    undefined4 *puVar3;
    undefined1 *puVar4;
    float fVar5;

    if ((someNpcData != (int *)0x0) &&
        (managerPtr = FUN_0043b870(DAT_0112afb8), managerPtr != 0) &&
        (cVar1 = FUN_0078a7d0(), cVar1 != '\0')) {
        // Begin display update
        FUN_006e61a0(someNpcData);
        *(undefined4 *)(this + 0x100) = 2; // set state to active
        fVar5 = FUN_0078ae90();            // get screen X position
        *(float *)(this + 0x124) = fVar5;
        fVar5 = FUN_0078aee0();            // get screen Y position
        *(float *)(this + 0x128) = fVar5;
        *(undefined4 *)(this + 300) = *(undefined4 *)(managerPtr + 0x40); // something id from manager
        **(undefined1 **)(this + 0x130) = 0; // clear string buffer?
        *(undefined4 *)(this + 0x138) = 0;
        puVar3 = (undefined4 *)(**(code **)(*someNpcData + 0x1d4))(); // get NPC name pointer
        puVar4 = (undefined1 *)*puVar3;
        if (puVar4 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e; // "??" or empty default
        }
        FUN_005c4660(*(undefined4 *)(this + 0x108), puVar4, 0x80, 0); // copy name to buffer
        FUN_0093ad10(someNpcData); // maybe prepare rendering
        // Show HUD elements
        FUN_005a04a0("ShowNPCInfo", 0, &DAT_00d8a64c, 0);
        FUN_005a04a0("ShowPressureMeter", 0, &DAT_00d8a64c, 0);
        FUN_00939ee0(managerPtr); // maybe update pressure bar
        *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0xa00; // set flags

        cVar1 = FUN_0078af40(); // check auto-hide setting
        if (cVar1 == '\0') {
            FUN_005a04a0("EnableAutoHidePressureStr", 0, &DAT_00d8a64c, 0);
        } else {
            FUN_005a04a0("DisableAutoHidePressureStr", 0, &DAT_00d8a64c, 0);
            FUN_0093b970(someNpcData, managerPtr, 0); // show pressure instantly
        }
        FUN_0093b840(); // finalize display

        if ((*(uint *)(managerPtr + 0x3c) >> 2 & 1) == 0) {
            *(undefined4 *)(this + 0x134) = 0;
            FUN_005c0260(this + 0x10, &LAB_0093b440, 1); // start hide timer
            *(uint *)(managerPtr + 0x3c) = *(uint *)(managerPtr + 0x3c) | 4; // mark timer active
            return;
        }
        FUN_005a04a0("HideBreakingPoint", 0, &DAT_00d8a64c, 0);
        FUN_005c02f0(this + 0x10, &LAB_0093b440, 1); // cancel hide timer
    }
    return;
}