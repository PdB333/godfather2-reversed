// FUNC_NAME: Player::evaluateMeleeAttack
void __thiscall Player::evaluateMeleeAttack(int *thisPtr, int *outActionType, float *outDistance, char *outFlag1, int *outFlag2)
{
    float threshold;
    int selfTransform;
    int targetTransform;
    float diffX, diffY, diffZ;
    float dummy;
    float dot;
    float forwardX, forwardY, forwardZ;
    float magnitude;
    float temp;
    int *component;

    // Default threshold
    threshold = _DAT_00d5780c; // 0.0f

    // Check bit 1 of flags at offset 0xC88 (0x322*4)
    if ((thisPtr[0x322] >> 1) & 1) {
        threshold = DAT_00e540ec; // alternate threshold
    }

    // Condition: must be within attack range? (timers and counters)
    if ((float)thisPtr[0x3da] < threshold &&
        (float)thisPtr[0x3d7] < _DAT_00d5780c &&
        thisPtr[0x3e4] < 1) {

        // Must have bit 11 set (maybe "inCombat" flag)
        if (!((thisPtr[0x322] >> 0xb) & 1)) {
            return;
        }

        // Get self and target transforms (likely ID handles or pointers)
        selfTransform = FUN_00471610();
        targetTransform = FUN_00471610();

        // Compute vector from self to target (position offsets +0x30, +0x34, +0x38)
        diffX = *(float *)(targetTransform + 0x30) - *(float *)(selfTransform + 0x30);
        diffY = *(float *)(targetTransform + 0x34) - *(float *)(selfTransform + 0x34);
        diffZ = *(float *)(targetTransform + 0x38) - *(float *)(selfTransform + 0x38);

        // Normalize direction vector
        dummy = 0.0f;
        FUN_0056afa0(&diffX, &diffX); // in-place normalize

        // Get forward direction of self
        FUN_008750c0(&forwardX); // returns (forwardX, forwardY, forwardZ)

        // Dot product: is target in front?
        dot = diffY * forwardY + diffX * forwardX + diffZ * forwardZ;

        if (dot < 0.0f) {
            // Target is behind
            if (_DAT_00d5780c <= (float)thisPtr[0x3db]) {
                goto LAB_00861e0f; // timer expired? exit
            }

            if (FUN_007f7c60()) { // maybe isPlayerControlled?
                component = (int *)FUN_007ff880(); // get combat component
                if (component == 0) {
                    return;
                }
                // Virtual call at vtable+0x1b0 (e.g., getMeleeRange)
                temp = (float)(**(code **)(*component + 0x1b0))();
                if ((float)DAT_00d68260 < temp) { // if range > threshold
                    selfTransform = FUN_00471610();
                    magnitude = (float)FUN_004702b0(selfTransform + 0x30); // distance to target?
                    if (magnitude <= (float)DAT_00e448f0) {
                        return;
                    }
                    // Issue melee attack command
                    *outActionType = 0;
                    *outDistance = _DAT_00d5780c;
                    *outFlag1 = 0;
                    *outFlag2 = 0;
                    return;
                }
                // Update timer
                thisPtr[0x3db] = (int)((float)thisPtr[0x3db] + DAT_012067e8);
                return;
            } else {
                // Not player controlled
                if (dot < DAT_00d75884) {
                    thisPtr[0x3db] = (int)_DAT_00d5780c; // reset timer
                    return;
                }
            }
        } else {
            // Target in front
            thisPtr[0x3db] = DAT_00d75880; // set timer
            return;
        }
    }

LAB_00861e0f:
    // Call virtual function on this (state exit?)
    (**(code **)(*thisPtr + 0x298))();

    // If bit 11 not set, perform cleanup
    if (!((thisPtr[0x322] >> 0xb) & 1)) {
        FUN_0087d560(0); // maybe stop animation?
        int soundFlag = _DAT_00d5c458;
        thisPtr[0x3ca] &= 0xffffbfff; // clear some flag
        FUN_005fea00(_DAT_00d7575c, soundFlag); // play sound
    }

    // Default output: no action
    *outActionType = 0;
    *outDistance = _DAT_00d578c;
    *outFlag2 = 0;
    *outFlag1 = 0;
}