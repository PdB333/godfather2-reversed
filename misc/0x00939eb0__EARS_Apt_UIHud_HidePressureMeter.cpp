// Xbox PDB: EARS_Apt_UIHud_HidePressureMeter
// FUNC_NAME: PlayerHUD::hidePressureMeter
void __thiscall PlayerHUD::hidePressureMeter() {
    // Send UI command to hide the pressure meter
    UIManager::sendUICommand("HidePressureMeter", 0, &g_pressureMeterData, 0); // 0x00d8a64c
    // Clear pressure meter visibility flags (bits 0x200 and 0x800 at +0x5c)
    this->flags &= 0xFFFFF5FF;
}