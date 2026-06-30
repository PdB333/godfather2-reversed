// FUNC_NAME: PlayerCCTVariables::updateMovement
void __thiscall PlayerCCTVariables::updateMovement(int this, float deltaTime)
{
    uint *puVar4;
    int iVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;
    
    // Check thread safety flag (FS segment offset 0x2c)
    puVar4 = (uint *)(*(int *)(this + 0x10) + *(int *)(**(int **)(*(int *)(__readfsdword(0x2c)) + 8)));
    if ((*puVar4 & 1) == 0) {
        iVar5 = *(int *)(this + 0x50); // movement parameters pointer
        
        // Check if elapsed time is within valid range (0 < elapsed < maxTime)
        if ((0.0 < *(float *)(iVar5 + 0x1c)) && (*(float *)(iVar5 + 0x1c) < *(float *)(this + 0x60))) {
            *puVar4 = *puVar4 | 1;
            return;
        }
        
        if (*(char *)(iVar5 + 0x10) == '\x01') { // Simple movement mode
            if (*(int *)(this + 0x54) == 0) {
                fStack_14 = 0.0;
                fStack_18 = 0.0;
                fStack_1c = 0.0;
                local_20 = 0.0;
            }
            else {
                FUN_00536020(&local_20); // Get simple movement vector
            }
        }
        else { // Complex movement calculation
            fVar6 = (*(float *)(iVar5 + 0x50) + *(float *)(this + 0x60)) * *(float *)(this + 0x6c);
            FUN_00501030(fVar6); // Clamp or normalize value
            iVar5 = *(int *)(this + 0x50);
            fVar8 = *(float *)(iVar5 + 0x30) * fVar6 * DAT_00e2cd54;
            fVar9 = (fVar6 + DAT_00e2b1a4) * DAT_00e2cd54;
            
            // Clamp fVar9 to [0, DAT_00e2b1a4]
            if (0.0 < fVar9) {
                if (DAT_00e2b1a4 <= fVar9) {
                    fVar9 = DAT_00e2b1a4;
                }
            }
            else {
                fVar9 = 0.0;
            }
            
            fVar9 = DAT_00e2b1a4 - (DAT_00e2b1a4 - fVar9) * fVar9 * DAT_00e2d99c;
            fVar6 = ((DAT_00e2b1a4 - fVar9 * fVar9 * fVar9) * *(float *)(iVar5 + 0x3c) +
                    (DAT_00e2b1a4 - *(float *)(iVar5 + 0x3c))) *
                    (*(float *)(iVar5 + 0x38) * fVar6 + DAT_00e2b1a4);
            
            fVar9 = DAT_00e2b1a4;
            if ((*(byte *)(iVar5 + 0x18) & 1) != 0) { // Bit 0: use alternate calculation
                fVar9 = DAT_00e2b1a4 / ((float)((uint)fVar6 & DAT_00e44680) + DAT_00e44560);
            }
            
            fVar7 = (*(float *)(iVar5 + 0x4c) + *(float *)(this + 100)) * *(float *)(this + 0x68);
            FUN_00501030(fVar7);
            local_20 = fVar7 * *(float *)(iVar5 + 0x2c) * fVar6 * DAT_00e2cd54;
            
            if (*(char *)(iVar5 + 0x12) == '\x02') { // Special movement type
                fVar7 = (*(float *)(iVar5 + 0x4c) + *(float *)(this + 100)) * *(float *)(this + 0x68)
                        + DAT_00e35654;
            }
            else {
                fVar7 = (*(float *)(iVar5 + 0x54) + *(float *)(this + 100)) * *(float *)(this + 0x70);
            }
            
            iVar5 = *(int *)(this + 0x50);
            fStack_1c = fVar8;
            FUN_00501030(fVar7);
            fStack_18 = fVar8 * *(float *)(iVar5 + 0x34) * fVar6 * DAT_00e2cd54;
            fStack_14 = 0.0;
            *(float *)(this + 100) = fVar9 * deltaTime + *(float *)(this + 100);
        }
        
        deltaTime = deltaTime + *(float *)(this + 0x60);
        *(float *)(this + 0x40) = *(float *)(this + 0x30) + local_20; // Update position X
        *(float *)(this + 0x44) = *(float *)(this + 0x34) + fStack_1c; // Update position Y
        *(float *)(this + 0x48) = *(float *)(this + 0x38) + fStack_18; // Update position Z
        *(float *)(this + 0x4c) = *(float *)(this + 0x3c) + fStack_14; // Update position W
        *(float *)(this + 0x60) = deltaTime; // Update elapsed time
        
        // Handle time wrap-around if needed
        if ((*(char *)(iVar5 + 0x11) == '\x01') && (*(float *)(iVar5 + 0x44) < deltaTime)) {
            *(float *)(this + 0x60) = deltaTime - *(float *)(iVar5 + 0x44);
        }
        
        // Add base position offset
        *(float *)(this + 0x40) = *(float *)(iVar5 + 0x20) + *(float *)(this + 0x40);
        *(float *)(this + 0x44) = *(float *)(iVar5 + 0x24) + *(float *)(this + 0x44);
        *(float *)(this + 0x48) = *(float *)(iVar5 + 0x28) + *(float *)(this + 0x48);
        *(float *)(this + 0x4c) = DAT_00e2b1a4; // Set W to 1.0
        
        // Store final position
        uVar1 = *(undefined4 *)(this + 0x44);
        uVar2 = *(undefined4 *)(this + 0x48);
        uVar3 = *(undefined4 *)(this + 0x4c);
        
        if ((*(byte *)(iVar5 + 0x18) & 2) != 0) { // Bit 1: store to global
            _DAT_01194a70 = *(undefined4 *)(this + 0x40);
            _DAT_01194a74 = uVar1;
            _DAT_01194a78 = uVar2;
            _DAT_01194a7c = uVar3;
            return;
        }
        
        // Store to object at offset +4
        iVar5 = *(int *)(this + 4);
        *(undefined4 *)(iVar5 + 0x60) = *(undefined4 *)(this + 0x40);
        *(undefined4 *)(iVar5 + 100) = uVar1;
        *(undefined4 *)(iVar5 + 0x68) = uVar2;
        *(undefined4 *)(iVar5 + 0x6c) = uVar3;
    }
    return;
}