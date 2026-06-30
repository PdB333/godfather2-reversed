// FUNC_NAME: AudioManager::playSoundEvent
void __thiscall AudioManager::playSoundEvent(int this, int param_2, int soundEventId, undefined4 param_4, int param_5, char param_6)
{
    uint uVar1;
    bool bVar2;
    float fVar3;
    int iVar4;
    uint uVar5;
    uint uVar6;
    undefined1 local_8;
    undefined1 uStack_7;
    undefined2 uStack_6;
    undefined1 uStack_4;
    undefined1 uStack_3;
    
    // Check if we need to stop previous sound event
    if ((*(int *)(this + 0x40) == soundEventId) || (bVar2 = true, *(int *)(this + 0x19c) == 0)) {
        bVar2 = false;
    }
    
    // Store new sound event ID
    *(int *)(this + 0x40) = soundEventId;
    
    // Reset timing/state variables
    *(undefined4 *)(this + 0x68) = 0;  // +0x68: some timer
    *(undefined4 *)(this + 0x74) = 0;  // +0x74: accumulated time
    *(undefined4 *)(this + 0x5c) = 0;  // +0x5c: some state
    
    // If param_2 is set, call some initialization
    if (param_2 != 0) {
        FUN_008c4250(this);
    }
    
    // Handle specific sound event (0x637b907 appears to be a special ID)
    if ((*(int *)(this + 0x40) == 0x637b907) &&
       (*(undefined4 *)(this + 0x60) = 0, param_6 != '\0')) {
        FUN_008c29a0(*(undefined4 *)(this + 200), 1);  // +0xC8: some handle
    }
    
    // If no custom data, use default
    if (param_5 == 0) {
        FUN_006b3cc0(param_4);
    }
    
    // Check if sound event has a callback
    if (*(int *)(this + 0xc0) != 0) {
        FUN_0084a910(*(undefined4 *)(this + 0x40));
    }
    
    // Handle timing based on whether we have custom data
    if (param_5 == 0) {
        iVar4 = *(int *)(this + 0x60);  // +0x60: duration
        *(int *)(this + 0x74) = *(int *)(this + 0x74) + iVar4;
        fVar3 = _DAT_00d577a0;  // Global time variable
        *(int *)(this + 0x6c) = iVar4;  // +0x6c: some duration
        *(int *)(this + 0x58) = iVar4;  // +0x58: another duration
        
        // Check if we need to update sound position
        if ((fVar3 < *(float *)(this + 0x80)) || ((*(uint *)(this + 0x34) >> 0x1d & 1) != 0)) {
            FUN_006b2f70();  // Update 3D position
        } else {
            FUN_006b59f0();  // Update 2D position
        }
    } else {
        // Use custom data for timing
        iVar4 = *(int *)(param_5 + 0x20);
        *(int *)(this + 0x60) = iVar4;
        *(undefined4 *)(this + 100) = *(undefined4 *)(param_5 + 0x40);  // +0x64: some value
        *(undefined4 *)(this + 0x6c) = *(undefined4 *)(param_5 + 0x28);
        *(int *)(this + 0x74) = *(int *)(this + 0x74) + iVar4;
        fVar3 = _DAT_00d577a0;
        *(int *)(this + 0x58) = iVar4;
        
        // Update position
        if ((fVar3 < *(float *)(this + 0x80)) || ((*(uint *)(this + 0x34) >> 0x1d & 1) != 0)) {
            FUN_006b2f70();
        } else {
            FUN_006b59f0();
        }
        
        // Handle looping/streaming
        if (param_2 != 0) {
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | 0x20000000;
            FUN_008c0b10(*(undefined4 *)(this + 0x38), *(undefined4 *)(param_5 + 0x1c), 0);
            *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xdfffffff;
        }
        
        // Handle overflow/loop timing
        uVar1 = *(uint *)(this + 0x74);
        if (*(uint *)(param_5 + 0x2c) < uVar1) {
            uVar6 = uVar1 - *(uint *)(param_5 + 0x2c);
            uVar5 = uVar6;
            if (uVar1 < uVar6) {
                uVar5 = uVar1;
            }
            *(uint *)(this + 0x74) = uVar1 - uVar5;
            FUN_006b2f70();
            for (; uVar6 != 0; uVar6 = uVar6 - 1) {
                FUN_006b4da0();
            }
        }
    }
    
    // Handle sound event completion callback
    if ((((bVar2) && ((*(byte *)(this + 0x34) & 1) == 0)) && (*(int *)(this + 0x40) != 0)) &&
       ((iVar4 = FUN_008c74d0(*(int *)(this + 0x40)), iVar4 != 0 &&
        ((~(byte)(*(uint *)(iVar4 + 0x84) >> 5) & 1) != 0)))) {
        FUN_006b5170();
    }
    
    // Handle streaming audio
    if (*(int *)(this + 0x19c) != 0) {
        FUN_008c76a0(&local_8, *(undefined4 *)(this + 0x40));
        FUN_0094ac00(*(undefined4 *)(this + 0x19c), CONCAT22(uStack_6, CONCAT11(uStack_7, local_8)),
                     CONCAT13(uStack_4, CONCAT21(uStack_6, uStack_7)),
                     CONCAT13(uStack_3, CONCAT12(uStack_4, uStack_6)));
    }
    
    // Final cleanup if no custom data
    if (param_5 == 0) {
        FUN_006b4910(param_4);
    }
    
    return;
}