// FUNC_NAME: InputManager::releaseControllerSlot
void __fastcall InputManager::releaseControllerSlot(int this)
{
    byte bVar1;
    uint uVar2;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    uVar2 = *(uint *)(this + 0x14); // +0x14: controller slot flags/state
    bVar1 = *(byte *)(this + 0x14); // +0x14: low byte of flags
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) & 0xfffffffc; // Clear bits 0 and 1 (slot in use flags)
    
    if ((uVar2 >> 1 & 1) != 0) { // Check if bit 1 was set (slot 1 active?)
        local_c = DAT_0112feb8; // Some global string or identifier
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c, 0); // Likely release/disconnect function
    }
    
    local_c = DAT_0112fedc; // Another global identifier
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // Release primary slot
    
    local_8 = 0;
    local_4 = 0;
    if ((bVar1 & 1) != 0) { // Check if bit 0 was set (slot 0 active?)
        local_c = DAT_0112fec4; // Another global identifier
        FUN_00408a00(&local_c, 0); // Release slot 0
        return;
    }
    
    local_c = DAT_0112fecc; // Fallback identifier
    FUN_00408a00(&local_c, 0); // Release fallback
    return;
}