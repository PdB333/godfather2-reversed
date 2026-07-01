// FUNC_NAME: WheeledVehicle::applyExternalForces
void __thiscall WheeledVehicle::applyExternalForces(int this, undefined4 *forcePacket)
{
    undefined4 *puVar1;
    int componentIndex;
    int iVar3;
    uint uVar4;
    int *piVar5;
    float forceScale;
    float fVar7;
    float fVar8;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    puVar1 = forcePacket;
    // Get component index from first element of packet
    componentIndex = getForceComponentIndex(*forcePacket); // FUN_0084aea0
    
    // Accumulate linear and angular forces from packet (indices 2-8,10,11)
    // Offsets 0x160-0x180 form a 9-element force/torque accumulator
    *(float *)(this + 0x160) = (float)puVar1[2] + *(float *)(this + 0x160);
    *(float *)(this + 0x164) = (float)puVar1[3] + *(float *)(this + 0x164);
    *(float *)(this + 0x168) = (float)puVar1[4] + *(float *)(this + 0x168);
    *(float *)(this + 0x16c) = (float)puVar1[5] + *(float *)(this + 0x16c);
    *(float *)(this + 0x170) = (float)puVar1[6] + *(float *)(this + 0x170);
    *(float *)(this + 0x174) = (float)puVar1[7] + *(float *)(this + 0x174);
    *(float *)(this + 0x178) = (float)puVar1[8] + *(float *)(this + 0x178);
    *(float *)(this + 0x17c) = (float)puVar1[10] + *(float *)(this + 0x17c);
    *(float *)(this + 0x180) = (float)puVar1[0xb] + *(float *)(this + 0x180);
    
    iVar3 = *(int *)(this + 0x1d0); // physics body pointer
    // Update force scale from packet index 13 (0xd)
    *(float *)(this + 0x188) = (float)puVar1[0xd] + *(float *)(this + 0x188);
    forceScale = 0.0f;
    if (iVar3 == 0) {
        forcePacket = (undefined4 *)0x0;
    } else {
        forcePacket = (undefined4 *)(*(float *)(iVar3 + 0x58) * *(float *)(this + 0x188));
        // body->mass * forceScale
    }
    
    // Convert signed int at +0x13c to float (with sign handling for negative values)
    fVar7 = (float)*(int *)(this + 0x13c);
    if (*(int *)(this + 0x13c) < 0) {
        fVar7 = fVar7 + DAT_00e44578; // adjust for sign (likely 0x80000000 as float?
    }
    
    fVar8 = (float)puVar1[0xd] * *(float *)(this + 0x188);
    *(float *)(this + 0x188) = fVar8;
    
    if (iVar3 != 0) {
        forceScale = *(float *)(iVar3 + 0x58) * fVar8;
    }
    
    // Compute acceleration (force / mass) and apply to speed
    forcePacket = (undefined4 *)(fVar7 * (float)forcePacket - fVar7 * forceScale);
    
    // Debug logging if flag set
    if (*(int *)(this + 0x230) != 0) {
        logDebug(forcePacket, 6); // FUN_00892490
    }
    
    // Clamp speed at +0x104
    fVar7 = (float)forcePacket + *(float *)(this + 0x104);
    forceScale = DAT_00d7bcac; // lower clamp
    if ((DAT_00d7bcac < fVar7) && (forceScale = fVar7, DAT_00d7bca8 <= fVar7)) {
        forceScale = DAT_00d7bca8; // upper clamp
    }
    *(float *)(this + 0x104) = forceScale;
    
    // Handle packet index 12 (0xc) – likely a reference or ID
    releaseForceReference(puVar1[0xc]); // FUN_008be720
    
    if (componentIndex != 0) {
        uVar4 = 0;
        if (*(int *)(componentIndex + 8) != 0) {
            do {
                iVar3 = getComponentChild(uVar4); // FUN_0084a3c0
                if (iVar3 != 0) {
                    updateChild(); // FUN_006b3220
                }
                uVar4 = uVar4 + 1;
            } while (uVar4 < *(uint *)(componentIndex + 8));
        }
        iVar3 = getComponentValue(); // FUN_0084a5b0
        forcePacket = (undefined4 *)(float)iVar3;
        
        if (*(int *)(this + 0x230) != 0) {
            logDebug(forcePacket, 0); // FUN_00892490
        }
        
        fVar7 = (float)forcePacket + *(float *)(this + 0x104);
        forceScale = DAT_00d7bcac;
        if ((fVar7 <= DAT_00d7bcac) || (forceScale = DAT_00d7bca8, DAT_00d7bca8 <= fVar7)) {
            fVar7 = forceScale;
        }
        *(float *)(this + 0x104) = fVar7;
    }
    
    // Handle force source pointer at packet index 19 (0x13)
    forcePacket = (undefined4 *)puVar1[0x13];
    if (forcePacket != (undefined4 *)0x0) {
        uVar4 = 0;
        if (*(uint *)(this + 0x128) != 0) {
            piVar5 = *(int **)(this + 0x124);
            do {
                if ((undefined4 *)*piVar5 == forcePacket) {
                    if (-1 < (int)uVar4) goto LAB_008c320f;
                    break;
                }
                uVar4 = uVar4 + 1;
                piVar5 = piVar5 + 1;
            } while (uVar4 < *(uint *)(this + 0x128));
        }
        // If not found in list, remove reference and handle removal
        removeForceSource(&forcePacket); // FUN_004866e0
        processForceRemoval(puVar1, 1); // FUN_008c0d10
    }
    
LAB_008c320f:
    // Capture current time and zero out local timestamp
    local_c = *(undefined4 *)(this + 0x21c);
    local_8 = 0;
    local_4 = 0;
    serializeTimestamp(&local_c, 0); // FUN_00408a00
    return;
}