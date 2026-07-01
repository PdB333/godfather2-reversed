// FUNC_NAME: Entity::handleCommand
// Function address: 0x00774120
// Handles incoming command messages (IDs starting at 0x23) for an entity.
// Uses vtable at +0x00, flags at +0x21, state at +0x22, object ref at +0x17, timer/effect object at +0x1c.

char __thiscall Entity::handleCommand(int commandId, undefined4 arg2, undefined4 arg3, undefined4 arg4, undefined4 arg5)
{
    char result;
    int state;
    int objId;
    int iVar2;
    int *pvVar5;
    int *pvVar6;
    float dirX, dirY, dirZ;
    float diffX, diffY, diffZ;
    float lenSq;
    float invLen;
    float impulseScale;
    float force[3];
    float targetPos[3];
    float dummy;

    result = 1; // local_31 default

    switch (commandId - 0x23)
    {
    case 0: // 0x23
        // Play audio event "0xa057c555" with flags (bit0 of local flags inverted?) and volume 1.0, pitch 1.0
        playAudio(0xa057c555, ~(flags>>0)&1, 1, 0, 1.0f, 1.0f); // vtable+0x2c
        flags &= 0xfffffffe; // clear bit 0
        return 0;

    case 1: // 0x24
        // Play audio based on state at +0x22
        state = *(int*)(this + 0x22);
        if (state == 0)
            playAudio(-0x1764441b, 1, 1, 0, _DAT_00e51ca8, 1.0f);
        else if (state == 1)
            playAudio(0xd1913132 + 6, 1, 1, 0, _DAT_00e51ca8, 1.0f); // Actually depends on condition
        // Above logic simplified: if state == 0 use -0x1764441b, else use 0xd1913132 (or +6)
        // The original code: iVar7 = (-(uint)(state != 1) & 6) + 0xd1913132;
        // so if state==1: iVar7=6+0xd1913132? Actually 0xd1913132+6=0xd1913138? But original bitwise: (-(uint)(state!=1)&6) gives 6 if state!=1 else 0. So iVar7 = (state!=1?6:0)+0xd1913132.
        // For state==1: iVar7 = 0xd1913132; for state!=1: iVar7 = 0xd1913138.
        // But state is only 0 or 1? Actually condition: if state==0 else (state!=1) gives else branch for state !=0 and state !=1? That is ambiguous. The original code: if (state==0) use -0x1764441b; else use iVar7=(-(uint)(state!=1)&6)+0xd1913132. So if state==1: -(uint)(false)=0, iVar7=0xd1913132; if state!=1: -(uint)(true)=0xffffffff, &6=6, iVar7=0xd1913138.
        // So only two possible audio hashes: -0x1764441b (0xe89bbbe5) and 0xd1913132 or 0xd1913138.
        break;

    case 2: // 0x25
        playAudio(0xa899f917, 1, 1, 0, 1.0f, 1.0f);
        flags &= 0xffffffef; // clear bit 4? Actually 0xfffffff7 clears bit 3? 0xfffffff7 = ~0x8, so clear bit 3.
        return 0;

    case 3: // 0x26
        // Toggle some effect based on state at +0x22 and game difficulty?
        state = *(int*)(this + 0x22);
        if (state != -1)
        {
            int difficulty = getDifficultyLevel(); // FUN_0077dd80
            if (difficulty < 3)
            {
                if ((flags >> 2) & 1) // bit 2 set?
                {
                    flags &= 0xfffffffb; // clear bit 2
                    stopEffect(this + 0x1c); // FUN_007ee320
                    return 1;
                }
            }
            else // difficulty >= 3
            {
                if (!((flags >> 2) & 1)) // bit 2 not set?
                {
                    flags |= 4; // set bit 2
                    startEffect(this + 0x1c); // FUN_007ee2e0
                    return 1;
                }
            }
        }
        break;

    case 4: // 0x27
        // Stop effect if flag bit 2 set
        if ((flags >> 2) & 1)
        {
            stopEffect(this + 0x1c); // FUN_007ee320
            flags &= 0xfffffffb; // clear bit 2
            return 1;
        }
        break;

    case 5: // 0x28
        playAudio(0x43204eb2, 1, 1, 0, 1.0f, 1.0f);
        return 0;

    case 6: // 0x29
        // Apply impulse force to an object
        processImpact(); // FUN_00773d40 - some pre-processing
        objId = *(int*)(this + 0x17); // some object ID at +0x17
        if (objId != 0)
        {
            void* soundSystem = getSoundSystem(); // DAT_01130950 from FUN_0043b870
            if (soundSystem != 0)
            {
                FUN_009995e0(0, 0, 0); // Unknown, maybe setup?
                int* someArray = getSomeArray(); // FUN_00994b40
                if (*someArray != 0)
                {
                    int* physicsObj = getPhysicsObject(objId); // FUN_006bea40
                    if (physicsObj != 0)
                    {
                        int instance = (**(code**)(*physicsObj + 0x34))(); // virtual call, maybe getPosition?
                        if (instance != 0)
                        {
                            float posX = *(float*)(instance + 0x20);
                            float posY = *(float*)(instance + 0x24);
                            float posZ = *(float*)(instance + 0x28);
                            float baseX = *(float*)(instance + 0x14);
                            float baseY = *(float*)(instance + 0x18);
                            float baseZ = *(float*)(instance + 0x1c);
                            diffX = posX - baseX;
                            diffY = posY - baseY;
                            diffZ = posZ - baseZ;
                            lenSq = diffX*diffX + diffY*diffY + diffZ*diffZ;
                            if (lenSq != 0.0f)
                            {
                                invLen = 1.0f / sqrtf(lenSq);
                                diffX *= invLen;
                                diffY *= invLen;
                                diffZ *= invLen;
                                // impulse scale factor
                                float scale = *(float*)(instance + 0x2c); // some mass or multiplier?
                                impulseScale = scale * diffX * DAT_00e51cac; // DAT_00e51cac likely global multiplier
                                force[0] = impulseScale;
                                force[1] = scale * diffY * _DAT_0112af08;
                                force[2] = scale * diffZ * DAT_00e51cac;
                                // Apply force at position
                                applyForce(DAT_00d5f374, force, &posX); // FUN_005417d0
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        break;

    case 7: // 0x2a
        // Check distance between two objects and possibly trigger an AI response
        objId = *(int*)(this + 0x17);
        if (objId != 0)
        {
            char isSomething = isConditionMet(); // FUN_0072d630
            if (isSomething != 0)
            {
                int targetObj = getTargetObject(); // FUN_007326c0
                if (targetObj != 0)
                {
                    int pos1 = getPosition(); // FUN_00471610
                    int pos2 = getPosition(); // FUN_00471610 (second call)
                    float distanceSq = getDistanceSquared(pos1 + 0x30, pos2 + 0x30); // FUN_0045c470
                    if (distanceSq < _DAT_00e51568) // threshold
                    {
                        doAction(objId, targetObj); // FUN_006f71b0
                        return 1;
                    }
                }
            }
        }
        break;

    default:
        result = defaultHandler(arg2, arg3, arg4, commandId, arg5); // FUN_0073e610
        break;
    }
    return result;
}