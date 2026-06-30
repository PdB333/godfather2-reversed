// FUNC_NAME: PlayerF2FSM::onStateUpdate

uchar __thiscall PlayerF2FSM::onStateUpdate(int* this, int someId, float deltaTime, int extra, int state, int extra2)
{
    uchar result = 1;
    int* piVar6;
    int iVar4;
    float fVar7;
    float local_8;
    int local_4;

    switch (state - 10) {
    case 0: // state 10
        break;

    case 1: // state 11
    {
        // +0x2c: vtable slot for animation callback?
        auto vtableFn = *(code**)(*this + 0x2c);
        this[0x2a]++;  // +0xa8: state entry count
        this[0x26] = 0; // +0x98: timer
        vtableFn(this[0x15], 1, 0, 0, 1.0f, 1.0f); // +0x54: animator?
        return 1;
    }

    case 2: // state 12
        this[0x26] = (int)((float)this[0x26] + deltaTime); // accumulate timer
        return 1;

    case 3: // state 13
    {
        this[0x2a] = 0; // reset count
        *(uchar*)(this + 0x25) = 0; // +0x94: some flag
        FUN_005512c0(2); // e.g., Camera::setMode(2)
        *(uint*)(this[0x1b] + 0xe4) |= 1; // +0x6c -> offset 0xe4: flags
        FUN_007f63e0(0x48); // e.g., Audio::playSound(72)
        FUN_0075ac30(); // some state transition
        uchar isAlive = FUN_0045eec0(this[0x16]); // +0x58: character entity
        if (isAlive == 0) {
            (**(code**)(*this + 0x2c))(this[0x16], 1, 1, 0, 1.0f, 1.0f);
            return 1;
        }
        break; // fall through to return 1
    }

    case 5: // state 15
        FUN_0075aea0(deltaTime); // e.g., update some timer
        return 1;

    case 6: // state 16
        FUN_005512c0(0); // e.g., Camera::setMode(0)
        // fall through to case 8

    case 8: // state 18
        *(uint*)(this[0x1b] + 0xe4) &= ~1; // clear flag
        // fall through to case 4

    case 4: // state 14
        FUN_007f6420(0x48); // e.g., Audio::stopSound(72)
        return 1;

    case 7: // state 17
        *(uint*)(this[0x1b] + 0xe4) |= 1;
        FUN_007f63e0(0x48);
        this[0x26] = 0;
        return 1;

    case 9: // state 19
    {
        // Get physics object position
        iVar4 = FUN_00471610(); // e.g., getPhysicsBody?
        // Read a 12-byte vector from offset 0x30 of that object
        float posX = *(float*)(iVar4 + 0x30);
        float posY = *(float*)(iVar4 + 0x34);
        float posZ = *(float*)(iVar4 + 0x38);
        float someComponent = posZ; // uVar5

        // Interpolate position using FUN_0075a380
        // This function seems to take a vector, target, and time, returning a displacement
        fVar7 = (float)FUN_0075a380(&posX, this + 0x17, deltaTime); // +0x5c: target position?

        if (ABS(fVar7) >= *DAT_00e44598) {
            // Modify the local position
            float newPosY = posY + fVar7;
            // Build a new vector (likely a Point3 interpreted as two doubles? This is fuzzy)
            double local_c = *(double*)&posX; // initial double from first 8 bytes
            // Actually reinterpreting the Vector3 as a double (first 8 bytes) and then modifying the upper part
            // For reconstruction, we treat this as modifying the Y component
            float local_8 = newPosY;
            int local_4 = someComponent; // unused

            // Get the physics body pointer
            if (this[0x12] == 0) { // +0x48: pointer to physics body? Actually offset -0x48 on this pointer
                piVar6 = 0;
            } else {
                piVar6 = (int*)(this[0x12] - 0x48); // +0x48 contains offset to parent object
            }
            // Call setPosition on physics body (vtable +0x1c)
            (**(code**)(*piVar6 + 0x1c))(&local_c); // pass modified vector
        }

        // Accumulate timer
        this[0x26] = (int)((float)this[0x26] + deltaTime);

        // Apply gravity? (global _DAT_00d6511c times deltaTime)
        FUN_00470130(this + 0x17, deltaTime * *(float*)0x00d6511c, 0);

        if (this[0x12] == 0) {
            (**(code**)(***(int***)0))(); // undefined: likely a vtable call on null? But corrected:
            // Actually (**(code**)(iRam00000000 + 0x164)) is bogus. Probably a vtable call on some static object.
            // For now, assume it's a safe return
            return 1;
        }
        (**(code**)(*(int*)(this[0x12] - 0x48) + 0x164))(); // vtable +0x164 call
        return 1;
    }

    case 10: // state 20
    {
        // Get the object at offset -0x48 from this[0x12] (if not null)
        int baseObj;
        if (this[0x12] == 0) {
            baseObj = 0;
        } else {
            baseObj = this[0x12] - 0x48;
        }

        // Look up some entity by hash? (0x18645cd9)
        iVar4 = FUN_007573b0(baseObj, 0x18645cd9);
        if ((iVar4 == 0) || (iVar4 = *(int*)(iVar4 + 0x44), iVar4 == 0)) {
            // No valid target; check inventory slot (this[0x21] = +0x84)
            int inventorySlot = this[0x21];
            if ((inventorySlot == 0) || (inventorySlot == 0x50)) {
                // Get something by hash (0x6862a74c) and call FUN_0075a260 (maybe equip)
                int item = FUN_00625050(0x6862a74c, this);
                FUN_0075a260(item);
            }
            inventorySlot = this[0x21];
            if (inventorySlot == 0) return 1;
            if (inventorySlot == 0x50) return 1;
            // Otherwise compute offset
            int somePtr;
            if (inventorySlot == 0) {
                somePtr = 0;
            } else {
                somePtr = inventorySlot - 0x50;
            }
            iVar4 = *(int*)(somePtr + 0xb0);
            if (iVar4 == 0) return 1;
        }

        // If we reach here, iVar4 is a valid entity pointer
        if (this[0x1f] != iVar4) { // +0x7c: current target?
            FUN_00601b10(iVar4); // e.g., setTarget(iVar4)
            return 1;
        }
        break; // fall through to return 1
    }

    default:
        result = FUN_004ac700(someId, deltaTime, extra, state, extra2);
    }

    return result;
}