// FUNC_NAME: SimNpc::handleNetworkMessage
void __thiscall SimNpc::handleNetworkMessage(int thisPtr, NetworkMessage* msg) {
    bool playerIsClose;
    uint msgHash;
    int iVar4;
    float fVar5, fVar6, fVar7;

    // Call the virtual function table based dispatch (likely msg->getType)
    msgHash = (**(code (__thiscall **)(NetworkMessage*))*msg)(); // Could be msg->getHash()

    if (msgHash < 0x44be8ae3) {
        if (msgHash == 0x44be8ae2) {
            // Handle "SetAllegiance" or similar
            msg->field_0x1f = 2;
            msg->field_0x23 |= 1;
            FUN_0076c290(*(uint *)(thisPtr + 0x60) >> 6 & 0xffffff01); // Clear bit 6? Possibly update flag
            return;
        }
        if (msgHash == 0x1b2d5c51) {
            // Handle "GetCrewLeader" or similar
            iVar4 = *(int *)(*(int *)(thisPtr + 0x110) + 0x24cc); // Access playerState->crewLeaderRoot
            if (iVar4 == 0) {
                iVar4 = 0;
            } else {
                iVar4 = iVar4 + -0x48; // Adjust to some sub-struct
            }
            FUN_0073d590(iVar4); // Some function on that sub-struct
            msg->field_0x1e = FUN_00716100(); // Return something
            return;
        }
        if (msgHash == 0x211bc9c1) {
            // Handle "GetHealth" or similar
            msg->field_0x20 = FUN_007161a0(); // Return health
            return;
        }
    } else if (msgHash == 0x6862a74c) {
        // Handle "SetPosition" or "Spawn"
        // Embed function pointers and data into the message
        *(ulonglong *)(msg + 0x24) = CONCAT44(&LAB_0074fb50, thisPtr); // likely a callback fcn &ptr
        *(undefined8 *)(msg + 0x26) = uStack_10; // uninitialized stack - probably leak
        *(ulonglong *)(msg + 0x28) = CONCAT44(&LAB_0074fc00, uStack_8);
        *(ulonglong *)(msg + 0x1e) = CONCAT44(FUN_0074fb30, thisPtr);
        *(undefined8 *)(msg + 0x20) = uStack_10;
        *(ulonglong *)(msg + 0x22) = CONCAT44(&LAB_0074fc00, uStack_8);
        msg->field_0x2a = msg->field_0x2a & 0xfffffffe; // Clear bit 0

        iVar4 = *(int *)(*(int *)(thisPtr + 0x110) + 0x24cc);
        if (iVar4 == 0) {
            iVar4 = 0;
        } else {
            iVar4 = iVar4 + -0x48;
        }
        FUN_0074a210(iVar4); // Some setup
        FUN_0075cd50(thisPtr + 100); // Initialize position at offset 100 (x,y,z?)
    } else if (msgHash == 0xf33262ca) {
        // Handle "UpdatePosition" or "Move"
        FUN_0075fa80((float *)(thisPtr + 100)); // Write current position to maybe a buffer
        msg->field_0x17 = *(float *)(thisPtr + 0x70); // Some value like speed or yaw
        iVar4 = *(int *)(*(int *)(thisPtr + 0x110) + 0x24cc);
        if (iVar4 == 0) {
            iVar4 = 0;
        } else {
            iVar4 = iVar4 + -0x48;
        }
        FUN_0074fc70(iVar4); // Update some system

        playerIsClose = false;
        if ((*(uint *)(thisPtr + 0x60) >> 6 & 1) != 0) { // Check if bit 6 of flags is set
            // Get player position from singleton
            iVar4 = FUN_00471610(); // Returns player transform (likely Player::getTransform)
            if (iVar4) {
                fVar5 = *(float *)(thisPtr + 100) - *(float *)(iVar4 + 0x30); // dx
                fVar6 = *(float *)(thisPtr + 0x68) - *(float *)(iVar4 + 0x34); // dy (note thisPtr+0x68 is y)
                fVar7 = *(float *)(thisPtr + 0x6c) - *(float *)(iVar4 + 0x38); // dz
                if (fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5 < DAT_00d64928) { // distance squared check
                    playerIsClose = true;
                }
            }
        }
        if (playerIsClose) {
            msg->field_0x22 |= 4; // Set bit 2 (close to player)
            return;
        }
        msg->field_0x22 &= 0xfffffffb; // Clear bit 2
        return;
    }
    return;
}