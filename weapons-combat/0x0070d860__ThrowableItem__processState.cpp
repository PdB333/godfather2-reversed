// FUNC_NAME: ThrowableItem::processState
char __thiscall ThrowableItem::processState(int* thisPtr, int throwerEntity, int state, undefined4 param4)
{
    bool bVar1;
    byte flags;
    char cVar3;
    char cVar4;
    int iVar5;
    int *piVar6;
    undefined4 uVar7;
    float10 fVar8;
    undefined4 uVar9;
    float local_20;
    undefined4 local_1c;
    float local_18;
    undefined4 local_14;

    // Profiling marker start with key 0xca
    Profile::begin(0xca);

    flags = *(byte*)((int)thisPtr + 0x39e);  // State flags at +0x39e
    cVar3 = '\x01';

    // Check bit 1 (0x02): if not set, handle thrower attachment
    if ((flags >> 1 & 1) == 0) {
        // If no thrower or thrower is still valid, skip detachment
        if ((throwerEntity == 0) || (cVar3 = EntityManager::isThrowableValid(throwerEntity, param3, param4), cVar3 != '\0'))
            goto LAB_0070db2f;
    }
    else {
        // Bit 1 set: check if attached via offset +0xe7
        if ((char)thisPtr[0xe7] == '\0') {
            // Not attached: check if we can detach from current thrower
            if ((((flags >> 2 & 1) == 0) && (throwerEntity != 0)) && (-1 < *(char*)(throwerEntity + 0x15e))) {
                // Get current holder (handle at +0xb5)
                if (thisPtr[0xb5] == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = thisPtr[0xb5] + -0x48;  // Convert handle to entity pointer offset
                }
                if ((iVar5 != throwerEntity) && (cVar3 = Entity::isAlive(throwerEntity), cVar3 != '\0')) {
                    ThrowableItem::detachFromThrower(throwerEntity, 1);  // Release from thrower
                }
            }
            cVar3 = '\0';
        }
        else {
            // Attached: handle rolling / impact logic
            if ((throwerEntity != 0) && (-1 < *(char*)(throwerEntity + 0x15e))) {
                iVar5 = thisPtr[0xb5];
                if ((iVar5 != 0) && ((iVar5 != 0x48 && (iVar5 + -0x48 == throwerEntity)))) goto LAB_0070db2f;
                if (((flags >> 2 & 1) == 0) && (cVar3 = Entity::isAlive(throwerEntity), cVar3 != '\0')) {
                    ThrowableItem::detachFromThrower(throwerEntity, 1);
                }
            }
            bVar1 = true;
            fVar8 = (float10)Physics::getSpeed(param4);  // Magnitude of movement
            if ((float10)0 < fVar8) {
                bVar1 = false;
                // Play bottle rolling animation
                (**(code **)(*thisPtr + 0xac))("bottle_roll.emx", 0);
                cVar3 = Animation::isPlaying(thisPtr, 9);  // Check if animation slot 9 is active
                if (cVar3 == '\0') {
                    ThrowableItem::setGravity((float)fVar8);  // Set gravity scale
                }
                // If the current holder is valid, retrieve its physics component
                if ((thisPtr[0xb5] != 0) && (thisPtr[0xb5] != 0x48)) {
                    if (thisPtr[0xb5] == 0) {
                        iVar5 = 0;
                    }
                    else {
                        iVar5 = thisPtr[0xb5] + -0x48;
                    }
                    piVar6 = (int*)Entity::getComponent(iVar5, 0x383225a1);  // Physics component hash
                    if (piVar6 != 0) {
                        (**(code **)(*piVar6 + 0x24))(0);  // Disable physics simulation
                        uVar9 = 0;
                        uVar7 = Audio::getHandle(0, 0);
                        Audio::setPosition(0, 0, uVar7, uVar9);  // Update audio source position
                        Audio::stop(uVar7);
                    }
                }
            }
            cVar3 = '\0';
            if ((bVar1) && (cVar4 = Entity::isAlive(throwerEntity), cVar4 != '\0')) {
                ThrowableItem::stopRolling(param4);
            }
        }
    }

    // Handle state == 2: update velocity based on movement
    if (state == 2) {
        // Get current velocity from physics component
        if (thisPtr[0xb5] == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = thisPtr[0xb5] + -0x48;
        }
        if (((iVar5 != throwerEntity) && ((*(byte*)((int)thisPtr + 0x39e) >> 1 & 1) != 0)) &&
            (iVar5 = thisPtr[0x6c], iVar5 != 0)) {
            // Read velocity (x,z) at offset 0x1a0,0x1a8
            local_20 = *(float*)(iVar5 + 0x1a0);
            local_1c = *(undefined4*)(iVar5 + 0x1a4);
            local_18 = *(float*)(iVar5 + 0x1a8);
            local_14 = *(undefined4*)(iVar5 + 0x1ac);
            // Clamp speed if too high
            if (DAT_00d5e288 < local_20 * local_20 + local_18 * local_18) {
                local_20 = local_20 * DAT_00e44890;
                local_18 = local_18 * DAT_00e44890;
            }
            Physics::applyVelocity(&local_20);  // Apply velocity vector
        }
        cVar3 = '\x01';
    }

LAB_0070db2f:
    Profile::end(0xca);
    return cVar3;
}