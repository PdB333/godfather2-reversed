// FUNC_NAME: FollowPathStateMachine::updateCurrentTarget
// Function at 0x005ffeb0
// Updates the current path target node, computes distance to goal
// Returns: 1 if path node found, 2 if target reached (or should stop), 0 if no path
int __thiscall FollowPathStateMachine::updateCurrentTarget(int this, undefined4 param_1, undefined4 param_2, float* param_3, undefined4 param_4) {
    int iVar6;
    int* puVar7;
    uint local_5c;
    uint local_54[2];
    float local_48;
    float local_3c;
    // local_44, local_4c, local_40, local_38, local_34, local_30, etc.

    // Attempt to get a path node (maybe next waypoint)
    iVar6 = FUN_005f6ee0(param_1, param_2, 0, param_4, param_3[1]); // unknown: findNode?
    if (iVar6 != 0) {
        // A node was found
        *(byte*)(this + 0x40) = 1; // set flag at +0x40

        // Manage a linked list of nodes at +0x44
        int iVar1 = *(int*)(this + 0x44);
        if (iVar1 != iVar6) {
            if (iVar1 != 0) {
                FUN_004daf90((int*)(this + 0x44)); // release old node? (freeNode)
            }
            *(int*)(this + 0x44) = iVar6; // store new node
            // Insert node into linked list (head insertion)
            *(int**)(iVar6 + 4) = (int*)(this + 0x44); // next pointer points to list head
            // Also store original next? Actually:
            *(undefined4*)(this + 0x48) = *(undefined4*)(iVar6 + 4); // likely tail or store old next
        }

        bool bVar8 = *(int*)(this + 0x88) == 0; // some flag or pointer

        // Choose source for target position based on flag at +0x7c
        float vec[4]; // temporary array for target
        if (*(int*)(this + 0x7c) == 0) {
            vec[0] = param_3[0];
            vec[1] = param_3[1];
            vec[2] = param_3[2];
            vec[3] = param_3[3]; // fourth component (unused?)
        } else {
            int* puVar2 = *(int**)(this + 0x84);
            vec[0] = *(float*)puVar2;
            vec[1] = *(float*)(puVar2 + 1);
            vec[2] = *(float*)(puVar2 + 2);
            // vec[3] not copied? Possibly set from elsewhere later
        }

        // Set local_20, uStack_1c, uStack_18 from vec (unused later?)
        // Actually these locals are written but never read clearly – might be debug info

        // Another source for target position based on flag at +0x88
        float vec2[3];
        if (bVar8) {
            vec2[0] = param_3[0];
            vec2[1] = param_3[1];
            vec2[2] = param_3[2];
        } else {
            int* puVar7Alt = *(int**)(this + 0x90);
            vec2[0] = *(float*)puVar7Alt;
            vec2[1] = *(float*)(puVar7Alt + 1);
            vec2[2] = *(float*)(puVar7Alt + 2);
        }

        // Prepare bitfield flag from +0xb4
        local_5c = (local_5c & 0xffffff00) | (*(uint*)(this + 0xb4) >> 0xb & 0xff); // bit 11? Actually shift right 11 bits and mask low byte

        // Get position of the found node (iVar6)
        puVar7 = (undefined4*)FUN_005f6ae0(local_54, param_1, param_2, iVar6, param_4, 0, local_5c, 0);
        undefined4 nodePosX = *puVar7; // node x
        float nodePosY = *(float*)(puVar7 + 1); // node y
        undefined4 nodePosZ = *(undefined4*)(iVar6 + 0xc); // node z from node structure
        // local_40, local_4c, local_48, etc. set up

        // Try to find a path node from this position (recursive? or just validate)
        local_54[0] = FUN_005f6ee0(param_1, &nodePosX, 0, param_4, param_3[1]); // attempt to find again
        float fVar11 = nodePosY;
        if (local_54[0] == 0) {
            FUN_005fd8d0(&nodePosX); // release the node reference
            fVar11 = nodePosY;
        }

        // Random check (maybe for deviation or obstacle avoidance)
        float fVar10 = (float)FUN_005fe710(); // random float 0..1
        if ((local_54[0] != 0) || (fVar10 * fVar10 < fVar11)) {
            // Toggle a flag at bit 11 of +0xb4
            if ((*(uint*)(this + 0xb4) >> 0xb & 1) == 0) {
                *(uint*)(this + 0xb4) |= 0x800;
            } else {
                *(uint*)(this + 0xb4) &= 0xFFFFF7FF;
            }

            // Re-fetch node position with toggled flag
            local_54[0] = (local_54[0] & 0xffffff00) | (*(uint*)(this + 0xb4) >> 0xb & 0xff);
            puVar7 = (undefined4*)FUN_005f6ae0(local_54, param_1, param_2, iVar6, param_4, 0, local_54[0], 0);
            nodePosX = *puVar7;
            float altNodeY = *(float*)(puVar7 + 1);
            nodePosZ = *(undefined4*)(iVar6 + 0xc);
            // local_48 = altNodeY etc.

            iVar6 = FUN_005f6ee0(param_1, &nodePosX, 0, param_4, param_3[1]);
            if (iVar6 != 0) {
LAB_006001f2:
                // If a new node found, set flag and return 2 (should stop or target reached)
                *(undefined4*)(this + 0xe0) = 0;
                return 2;
            }
            FUN_005fd8d0(&nodePosX);
            if (fVar10 * fVar10 < altNodeY) goto LAB_006001f2;
        }

        // Update current position and target vectors in this object
        *(undefined4*)(this + 0x10) = nodePosX; // current x
        *(float*)(this + 0x18) = nodePosY; // current z? Actually offset 0x18 was used as z
        // Store the original target (param_3) to offsets +0x60, +0x64, +0x68, +0x6c
        *(float*)(this + 0x60) = param_3[0];
        *(float*)(this + 0x64) = param_3[1];
        *(float*)(this + 0x68) = param_3[2];
        *(float*)(this + 0x6c) = param_3[3];
        // Compute distance from current to target (stored at +0xc4)
        float dx = *(float*)(this + 0x60) - *(float*)(this + 0x10);
        float dy = *(float*)(this + 0x64) - *(float*)(this + 0x14);
        float dz = *(float*)(this + 0x68) - *(float*)(this + 0x18);
        *(float*)(this + 0xc4) = sqrt(dx*dx + dy*dy + dz*dz);
        // Reset some counters
        *(int*)(this + 0xc0) = 0;
        *(int*)(this + 0xe0) = 0;

        return 1; // success, path node found
    }
    return 0; // no path node found
}