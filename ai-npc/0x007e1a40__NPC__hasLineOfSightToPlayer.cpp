// FUNC_NAME: NPC::hasLineOfSightToPlayer
bool __thiscall NPC::hasLineOfSightToPlayer(NPC* thisPtr)
{
    // Context: AI visibility check from NPC to the player
    // Offsets:
    // +0x58: pointer to motion state (or transform component)
    // +0x1f68: maxSightDistanceSquared (float)
    // +0x1f6c: targetIdentifier (int, probably player index)
    // +0x8e3: flags (bit0: useAimOffset)

    MotionState* motionState = *(MotionState**)(thisPtr + 0x58);
    TransformInfo* playerTransform = FUN_00471610(); // global player transform
    float buffer[4]; // local_e0, likely a rotation/quaternion

    // Copy player's rotation into buffer
    FUN_00793b50(buffer, playerTransform + 0x30); // player rotation offset

    // Some global check (possibly if targeting is enabled)
    char targetingEnabled = FUN_007961a0();
    if (targetingEnabled == 0) {
        return false;
    }

    float sightDistanceSq = *(float*)(motionState + 0x1f68);
    float playerPos[3];
    // Load player position from buffer? Actually FUN_004702b0 seems to convert buffer to a position
    FUN_004702b0(buffer);

    // Check distance squared
    if (extraout_ST0 <= sightDistanceSq * sightDistanceSq) { // ST0 is the result of FUN_004702b0? Actually it's a floating point compare
        playerTransform = FUN_00471610();
        int playerId = FUN_00471610();
        // Check line of sight between player and NPC using some transform data and target ID
        char losResult = FUN_007f7f30(buffer, playerId + 0x30, playerTransform + 0x20, *(int*)(motionState + 0x1f6c));
        if (losResult != 0) {
            playerTransform = FUN_00471610();
            float targetPos[3];
            targetPos[2] = *(float*)(playerTransform + 0x38); // z component
            // The following is reading a 64-bit value at playerTransform+0x30 as two floats (x and y?)
            uint64 rawBits = *(uint64*)(playerTransform + 0x30);
            targetPos[1] = (float)(rawBits >> 32); // y component
            targetPos[0] = (float)rawBits; // x component

            // Accumulate time delta (DAT_00d5ef50 is likely frame time)
            float timeDelta = DAT_00d5ef50;
            targetPos[2] += timeDelta; // Not sure why add time to z? Possibly a time-dependent offset
            float tempY = targetPos[1] + timeDelta;
            targetPos[1] = tempY;
            targetPos[0] += timeDelta; // Actually targetPos[0] not used after? Wait, there is local_ec = (float)*(undefined8 *)(iVar2+0x30); This sets targetPos[0] as first float of the 64-bit

            // Adjusted: Actually the code does:
            // local_ec = (float)*(undefined8 *)(iVar2+0x30); // as first float
            // fStack_e8 = (float)((ulonglong)*(undefined8 *)(iVar2+0x30) >> 0x20); // second float
            // local_e4 = *(float*)(iVar2+0x38); // third float
            // So the 64-bit at +0x30 holds two floats packed.

            // Check if aim offset flag is set (bit0)
            if ((*(byte*)(motionState + 0x8e3) & 1) != 0) {
                playerTransform = FUN_00471610();
                float aimOffsetScale = DAT_00d6f9b4;
                // Apply aim offset from NPC's own transform (iVar4) - note iVar4 is motionState
                targetPos[0] += *(float*)(motionState + 0x20) * aimOffsetScale;
                targetPos[1] += *(float*)(motionState + 0x24) * aimOffsetScale; // fStack_e8 gets incremented first
                targetPos[2] += *(float*)(motionState + 0x28) * aimOffsetScale;
            }

            // Perform raycast from player to target (or vice versa?)
            // FUN_00542650 likely: bool LineOfSightCheck(Vector3* start, Matrix4* worldToLocal?, int collideMask, uint flags, void*, void*)
            // Here it uses &targetPos (first three floats) as start, buffer as transform, 2 as collision group, 0x10000 as flags
            RaycastResult result;
            FUN_00542650(&targetPos, buffer, 2, 0x10000, 0, 0);

            // Setup a hit result structure
            HitResult hitStruct;
            hitStruct.vtable = &PTR_FUN_00e32a8c; // some vtable
            hitStruct.hit = false (local_70=0);
            hitStruct.unknown1 = 0;
            hitStruct.field_0x8 = _DAT_00d5780c; // global data
            hitStruct.field_0x14 = 0;
            hitStruct.field_0x18 = _DAT_00d5780c;

            // Process raycast result
            FUN_009e5ed0(&resultBuffer, &hitStruct);

            // Return true if no collision (hitStruct.hit == 0)
            return hitStruct.hit == 0;
        }
    }
    return false;
}