// FUNC_NAME: WheeledVehicle::processContactPoints

void __thiscall WheeledVehicle::processContactPoints(WheeledVehicle *this, CollisionContact *contactInfo, WheelContact *contacts, float contactCount)
{
    int componentCount;
    int *componentArray;
    int componentIndex;
    int wheelDataIndex;
    int entityHandle;
    int wheelEntity;
    int *typePtr;
    int componentType;
    undefined4 typeId;
    float *positionPtr;
    float relVelX, relVelY, relVelZ;
    float springForce;
    float forceScale;
    float crossX, crossY, crossZ;
    float invDenom;
    float forceVector[3];
    float springCompression;
    float damping;
    int listenerCount;
    void **listenerArray;
    int listenerIndex;

    typeId = *(undefined4 *)(contactInfo + 8);
    springCompression = 0.0f;
    if ((int)contactCount > 0)
    {
        wheelDataIndex = 0;
        contacts = contacts;
        contactCount = contactCount;
        do
        {
            entityHandle = *(int *)(*(int *)(this + 100) + 0x28 + wheelDataIndex);
            wheelEntity = entityHandle;
            componentCount = *(int *)(*(int *)(*(int *)(wheelEntity + 0x10) + 0x78) + wheelEntity);
            componentIndex = 0;
            if (componentCount > 0)
            {
                componentArray = *(int **)(*(int *)(wheelEntity + 0x10) + wheelEntity + 0x74);
                do
                {
                    componentType = *componentArray;
                    if (componentType == 0x1300)
                    {
                        typeId = *(undefined4 *)FUN_004af8c0(componentType, 0x1300);
                        listenerCount = *(int *)(this + 0x74);
                        listenerArray = *(void ***)(this + 0x70);
                        while (listenerCount-- > 0)
                        {
                            if (*listenerArray != NULL)
                            {
                                (**(code **)(**(int **)(listenerArray) + 0xc))(this, typeId, *(int *)(this + 100) + wheelDataIndex);
                            }
                        }
                    }
                    componentIndex++;
                    componentArray++;
                } while (componentIndex < componentCount);
            }
            wheelDataIndex = *(int *)(this + 100) + wheelDataIndex;
            wheelEntity = *(int *)(wheelDataIndex + 0x28);
            if ((*(char *)(wheelEntity + 0x18) == '\x01') &&
                (wheelEntity = *(char *)(wheelEntity + 0x10) + wheelEntity, wheelEntity != 0))
            {
                componentIndex = 0;
                if (*(int *)(wheelEntity + 0x78) > 0)
                {
                    componentArray = *(int **)(wheelEntity + 0x74);
                    do
                    {
                        if (*componentArray == 0x2004)
                        {
                            if ((((*contacts != '\0') ||
                                 (*(float *)(wheelDataIndex + 0x1c) - *(float *)(this + 0x58) < DAT_00e44598)) &&
                                (*(char *)(wheelEntity + 0xd8) != '\a')) && (*(char *)(wheelEntity + 0xd8) != '\x06'))
                            {
                                positionPtr = *(float **)(this + 100);
                                float localX = positionPtr[wheelDataIndex];
                                float localY = positionPtr[wheelDataIndex + 1];
                                float localZ = positionPtr[wheelDataIndex + 2];
                                float localW = positionPtr[wheelDataIndex + 7];
                                float localVelX = positionPtr[wheelDataIndex + 4];
                                float localVelY = positionPtr[wheelDataIndex + 5];
                                float localVelZ = positionPtr[wheelDataIndex + 6];
                                springCompression = localW;

                                relVelX = localX - *(float *)(wheelEntity + 0x130);
                                relVelY = localY - *(float *)(wheelEntity + 0x134);
                                relVelZ = localZ - *(float *)(wheelEntity + 0x138);

                                float invMass = *(float *)(wheelEntity + 0x19c);
                                float crossTerm1 = *(float *)(wheelEntity + 0x1b0) * relVelY - *(float *)(wheelEntity + 0x1b4) * relVelX;
                                float crossTerm2 = *(float *)(wheelEntity + 0x1b8) * relVelX - *(float *)(wheelEntity + 0x1b0) * relVelZ;
                                float crossTerm3 = *(float *)(wheelEntity + 0x1b4) * relVelZ - *(float *)(wheelEntity + 0x1b8) * relVelY;

                                float netForceX = *(float *)(wheelEntity + 0x1a8) + crossTerm1 - *(float *)(this + 0x18);
                                float netForceY = *(float *)(wheelEntity + 0x1a4) + crossTerm2 - *(float *)(this + 0x14);
                                float netForceZ = *(float *)(wheelEntity + 0x1a0) + crossTerm3 - *(float *)(this + 0x10);

                                float forceDot = netForceX * localVelX + netForceY * localVelY + netForceZ * localVelZ;

                                springForce = *(float *)(contactInfo + 0xc) * localW * DAT_00e2cd14 - forceDot * DAT_0110a440;

                                int entityHold = wheelEntity;
                                if (springForce <= DAT_00e2b05c)
                                {
                                    (**(code **)(*(int *)(wheelEntity + 0xd0) + 0x28))(someStackBuffer);

                                    float diffX = localX - *(float *)(wheelEntity + 0x134);
                                    float diffY = localY - *(float *)(wheelEntity + 0x138);
                                    float diffZ = contactCount - *(float *)(wheelEntity + 0x130);

                                    crossX = diffX * localVelY - diffY * localVelX;
                                    crossY = diffY * localVelZ - localVelY * diffZ;
                                    crossZ = localVelX * diffZ - diffX * localVelZ;

                                    FUN_00aa2d50(normalizedOut, &crossX);

                                    int listenerCount2 = *(int *)(this + 0x74);
                                    float invDenom = *(float *)(wheelEntity + 0x19c) + 
                                                     someFloat5 * crossZ + someFloat6 * crossY + crossX * localFloat64;

                                    float scale = forceDot / invDenom;

                                    float springForceX = localW * scale;
                                    float springForceY = localVelX * scale;
                                    float springForceZ = localVelY * scale;
                                    float springForceW = localVelZ * scale;

                                    float impulseX = contactCount;
                                    float impulseY = localX;
                                    float impulseZ = localY;
                                    float impulseW = localZ;

                                    while (listenerCount2-- > 0)
                                    {
                                        if (*(int *)(*(int *)(this + 0x70) + listenerCount2 * 4) != 0)
                                        {
                                            (**(code **)(**(int **)(*(int *)(this + 0x70) + listenerCount2 * 4) + 0x10))
                                                (this, &contactCount, &springForceX);
                                        }
                                    }

                                    FUN_009f2000();
                                    (**(code **)(*(int *)(wheelEntity + 0xd0) + 0x4c))(&springForceX, &impulseX);

                                    *(float *)(this + 0x10) = *(float *)(this + 0x10) + impulseW * springCompression;
                                    *(float *)(this + 0x14) = *(float *)(this + 0x14) + impulseZ * springCompression;
                                    *(float *)(this + 0x18) = *(float *)(this + 0x18) + impulseY * springCompression;
                                    *(float *)(this + 0x1c) = *(float *)(this + 0x1c) + impulseX * springCompression;
                                }
                                break;
                            }
                        }
                        componentIndex++;
                        componentArray++;
                    } while (componentIndex < *(int *)(wheelEntity + 0x78));
                }
            }
            contacts = (WheelContact *)((char *)contacts + 0x10);
            wheelDataIndex += 0x30;
            contactCount = contactCount - 1.0f;
        } while (contactCount != 0.0f);
    }
}