// FUNC_NAME: AudioManager::updateListenerPosition
void __fastcall AudioManager::updateListenerPosition(uint param_1, uint param_2)
{
    uint in_EAX;
    undefined1 *puVar1;
    float local_20;
    float local_1c;
    float local_18;
    float local_14;
    
    DAT_0121b8c0 = in_EAX; // +0x8C0: listener entity ID
    DAT_0121b8c4 = param_2; // +0x8C4: second entity ID (maybe listener or source)
    
    if ((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b754 == DAT_0121bbbc)) {
        // Check if audio system is initialized and in valid state
        if (DAT_0121bb70 != 0) {
            FUN_006063b0(); // Stop/clear sound on channel 0
        }
        if (DAT_0121bb74 != 0) {
            FUN_006063b0(); // Stop/clear sound on channel 1
        }
        if (DAT_0121bb78 != 0) {
            // Get sound data for first entity (index < 4096)
            if (DAT_0121b8c0 < 0x1000) {
                puVar1 = &DAT_011a0f28 + DAT_0121b8c0 * 0x38; // Sound data array, 0x38 bytes per entry
            }
            else {
                puVar1 = (undefined1 *)0x0;
            }
            // Calculate scale factor: base frequency / sound's frequency
            local_20 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 2); // +2: frequency field
            
            if (DAT_0121b8c0 < 0x1000) {
                puVar1 = &DAT_011a0f28 + DAT_0121b8c0 * 0x38;
            }
            else {
                puVar1 = (undefined1 *)0x0;
            }
            local_1c = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 4); // +4: another frequency field
            
            // Same for second entity
            if (DAT_0121b8c4 < 0x1000) {
                puVar1 = &DAT_011a0f28 + DAT_0121b8c4 * 0x38;
            }
            else {
                puVar1 = (undefined1 *)0x0;
            }
            local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 2);
            
            if (DAT_0121b8c4 < 0x1000) {
                puVar1 = &DAT_011a0f28 + DAT_0121b8c4 * 0x38;
            }
            else {
                puVar1 = (undefined1 *)0x0;
            }
            local_14 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 4);
            
            // Update 3D audio position with calculated scale factors
            FUN_0060add0(DAT_0121bbbc, DAT_0121bb78, &local_20);
        }
    }
    return;
}