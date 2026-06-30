// FUNC_NAME: EnemyBehavior::updateState
// Function at 0x00751560 - State machine for enemy NPC behavior. Handles states 10-16 (offset by 10).
// This __thiscall method is called each frame with the current state ID in param_5 (actual switch value = param_5 - 10).

__thiscall char EnemyBehavior::updateState(int state, int unk1, int unk2, int unk3, int unk4, void* unk5)
{
    char result = 1;
    switch (state - 10) {
    case 0: // State == 10 (e.g., "Enter" or "Initiate")
        if ((m_flags & 0x40) != 0) {
            setAnimFlag(1);
            m_flags |= 0x80;
        }
        int vtable1 = *(int*)m_vtable;
        char retVal = 0x3f;
        int animHandle = requestAnim(1, 0, 0, 1.0f, 1.0f);
        (*(void (__thiscall **)(int))(vtable1 + 0x2c))(animHandle);
        return retVal;

    case 1: // State == 11 (e.g., "Exit")
        if ((m_flags & 0x80) != 0) {
            setAnimFlag(0);
            m_flags &= 0xffffff7f;
            return 1;
        }
        break;

    case 2: // State == 12 (unused)
    case 6: // State == 16 (unused)
        break;

    case 3: // State == 13 (e.g., "Reset")
        resetState();
        return 1;

    case 4: // State == 14? Actually case 4 comes from param5=14, but case 4 falls through to case 5? 
            // Actually case 4 does not have a break; it falls through to case 5.
        m_someCounter1 = 0;
        m_someCounter2 = (int)(someGlobal1 + someGlobal2);
        // fall through
    case 5: // State == 15 (e.g., "Disable")
        m_flags &= 0xfffffffe;
        return 1;

    case 7: // State == 17 (e.g., "Chase")
        {
            int playerPos = getPlayerPosition();
            char isActive = isBehaviorActive();
            if (isActive && m_hasTarget) {
                char flag1 = someCheck(3);
                char flag2 = someCheck(4);
                char flag3 = someCheck(5);
                if (flag1 == 0 || (flag2 == 0 || flag3 == 0)) {
                    int entity1 = getSomeEntity();
                    int entity2 = getSomeEntity();
                    float distance = calcDistance(entity2 + 0x30, entity1 + 0x30);
                    int* target = &m_targetPos;
                    int steer = computeSteeringAngle(distance * someFloat, playerPos, target);
                    m_steerHandle = steer;
                    char normalized = normalizeVector(target, target);
                    if (normalized) {
                        releaseSteeringHandle(m_steerHandle);
                    }
                    m_chaseCounter = 0;
                    return 1;
                }
            }
            if (m_hasTarget) {
                float speed = getDesiredSpeed();
                int* target = &m_targetPos;
                int steer = computeSteeringAngle(speed * someOtherFloat, playerPos, target);
                m_steerHandle = steer;
                char normalized = normalizeVector(target, target);
                if (normalized) {
                    releaseSteeringHandle(m_steerHandle);
                }
                m_chaseCounter++;
                return 1;
            }
        }
        break;

    case 8: // State == 18 (e.g., "Approach")
        {
            getDesiredSpeed();
            int* target = &m_targetPos;
            int* target2 = target; // seems redundant
            int playerPos = getPlayerPosition(target); // note: passes target as argument? Might be a bug in decompilation
            // Actually FUN_0074fcd0 is called with no argument in first call, then with target in second call? 
            // The decompiled code shows: uVar6 = FUN_0074fcd0(piVar1); where piVar1 = param_1 + 0x19 (m_targetPos).
            // So getPlayerPosition may take a vector to fill.
            // Let's restructure:
            int playerPos = getPlayerPosition(); // first call without argument
            // Then second call with &m_targetPos used as output? But then it's used as input to computeSteeringAngle.
            // Actually the code: uVar6 = FUN_0074fcd0(piVar1); and then iVar4 = FUN_0078cb10((float)extraout_ST0_00, uVar6, piVar10);
            // extraout_ST0_00 comes from the previous getDesiredSpeed() call.
            // So likely:
            // getPlayerPosition returns something (maybe a position?) and the second call fills m_targetPos?
            // I'll keep it as: getPlayerPosition() to get player pos, and then computeSteeringAngle with m_targetPos as target.
            int steer = computeSteeringAngle(speedFromDesired, playerPos, target);
            m_steerHandle = steer;
            char normalized = normalizeVector(target, target);
            if (normalized) {
                releaseSteeringHandle(m_steerHandle);
                return 1;
            }
        }
        break;

    case 9: // State == 19 (e.g., "Attack")
        if (someGlobal1 < (float)m_someCounter3 && (playerPos = getPlayerPosition(), playerPos != 0)) {
            int someData = m_somePointer + 0x2194; // large offset, likely a member of a derived class
            int entity1 = getSomeEntity();
            int entity2 = getSomeEntity2();
            int* target = &m_targetPos;
            doSomeAnimation(entity1 + 0x30); // may be setAnimationTransform?
            if (m_someIndex >= 0) {
                char coverCheck = isInCover();
                if (coverCheck == 0) {
                    goto LAB_ATTACK_END;
                }
                if (entity2 != 0) {
                    int playerPos = getPlayerPosition(0);
                    char coverResult = checkCover(playerPos);
                    if (coverResult != 0) goto LAB_ATTACK_END;
                }
            }
            if ((m_someIndex < 0) && (char visible = isTargetVisible(), visible != 0)) {
                doCoverAction();
                char vehicleState = isInVehicle();
                if (vehicleState == 0) {
                    getPlayerPosition();
                    int entity1 = getSomeEntity();
                    copyVector(&m_savedPos, entity1 + 0x30);
                    if (someDistance > 1.0f) {
                        (*(void (__thiscall **)(int*))(*target + 0x1c))(target);
                        return 1;
                    }
                }
            }
        }
        break;

    case 10: // State == 20 (e.g., "Approach2")
        if (m_someIndex < 0) {
            doCoverAction();
            setSomeFlag(0, unk5);
            int entity = getSomeEntity();
            char result = getPathData(&state, &unk5); // reusing state variable as output? weird
            if (result != 0) {
                m_destination.x = *(float*)unk5; // assuming undefined8* is two floats? Actually copied as 8 bytes
                m_destination.y = *(float*)((char*)unk5 + 4);
                m_destination.z = *(float*)((char*)unk5 + 8); // third float from int at unk5+1? Actually param_1[0x1b] is set from *(int *)(param_6 + 1)
                int entity1 = getSomeEntity();
                float dx = (float)m_destination.x - *(float*)(entity1 + 0x30);
                float dy = (float)m_destination.y - *(float*)(entity1 + 0x34);
                float dz = (float)m_destination.z - *(float*)(entity1 + 0x38);
                normalizeVector(&dx, &dx);
                int steer = computeSteeringAngle(&dx);
                m_steerHandle = steer;
            }
        }
        (*(void (__thiscall **)(int))(m_subComponent + 0x1c))(m_subComponent);
        return 1;

    case 11: // State == 21 (e.g., "Escape")
        {
            int playerPos = getPlayerPosition();
            if (playerPos != 0 && m_hasTarget) {
                void* path = getAttractorPath();
                if (path != 0) {
                    float* dest = &m_targetPos;
                    *(undefined8*)dest = *(undefined8*)path; // copy 8 bytes (first two floats)
                    m_targetPos.z = *(float*)((char*)path + 8); // third float
                    int entity1 = getSomeEntity();
                    float dx = *dest - *(float*)(entity1 + 0x30);
                    float dy = m_targetPos.y - *(float*)(entity1 + 0x34);
                    float dz = m_targetPos.z - *(float*)(entity1 + 0x38);
                    normalizeVector(&dx, &dx);
                    int steer = computeSteeringAngle(&dx);
                    m_steerHandle = steer;
                    normalizeVector(dest, dest);
                    return 1;
                }
            }
        }
        break;

    default:
        result = baseStateHandler(state, unk2, unk3, unk4, unk5); // default handler from base class
        break;

    case 14: // State == 24 (e.g., "Wait")
        m_someCounter3 = (int)(someGlobal1 + someGlobal3);
        return 1;

    case 15: // State == 25 (e.g., "Hold")
        {
            int entity1 = getSomeEntity();
            void* pos = entity1 + 0x30;
            if ((m_flags & 0x20) == 0) {
                m_flags |= 0x20;
                m_holdPos.x = *(float*)pos;
                m_holdPos.y = *(float*)((char*)pos + 4);
                m_holdPos.z = *(float*)((char*)pos + 8);
                m_holdCounter = 0;
                return 1;
            }
            copyVector(&m_holdPos, pos);
            if (someDistance < 1.0f) {
                m_holdCounter++;
                return 1;
            }
            m_holdCounter = 0;
            m_holdPos.x = *(float*)pos;
            m_holdPos.y = *(float*)((char*)pos + 4);
            m_holdPos.z = *(float*)((char*)pos + 8);
            return 1;
        }

    case 16: // State == 26 (e.g., "Cover")
        char isInVehicle = isInVehicle();
        if (isInVehicle != 0) {
            startCover(m_coverData);
            return 1;
        }
        break;
    }
    return result;
}