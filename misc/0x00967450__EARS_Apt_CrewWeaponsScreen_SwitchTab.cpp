// Xbox PDB: EARS_Apt_CrewWeaponsScreen_SwitchTab
// FUNC_NAME: UIManager::toggleTab
void __fastcall UIManager::toggleTab(int this)
{
    uint uVar1;
    undefined4 *puVar2;
    undefined1 *puVar3;
    int local_10;
    code *local_4;
    
    // Toggle the tab enabled flag at offset +0x04
    uVar1 = (uint)(*(int *)(this + 0x4) == 0);
    *(uint *)(this + 0x4) = uVar1;
    
    // Look up the tab string based on the new state
    puVar2 = (undefined4 *)getTabString(uVar1); // FUN_004d3b00
    puVar3 = (undefined1 *)*puVar2;
    if (puVar3 == (undefined1 *)0x0) {
        puVar3 = &defaultTabString; // DAT_0120546e
    }
    
    // Send the switch tab command (likely to Lua or UI script)
    sendUIEvent("SwitchTab", 0, &globalTabData, 1, puVar3); // FUN_005a04a0
    
    // SEH epilog (compiler-generated cleanup)
    if (local_10 != 0) {
        (*local_4)(local_10);
    }
    return;
}