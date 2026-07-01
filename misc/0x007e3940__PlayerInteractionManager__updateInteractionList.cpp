// FUNC_NAME: PlayerInteractionManager::updateInteractionList

void __thiscall PlayerInteractionManager::updateInteractionList(void *this)
{
    int *excludeEntity; // local_4
    int *entity; // local_8
    int objectIndex;
    int *objectPtr;
    char ok;
    float dx, dy, dz;
    float distSq;

    excludeEntity = *(int **)((int)this + 0x58);
    *(char *)((int)this + 0x81) = 0; // clear interaction flag (byte at +0x81)

    // get player reference position (e.g., player’s world position)
    playerPosStruct = (PlayerPositionStruct *)FUN_00471610(); // returns ptr to player/camera position struct

    int count = *(int *)((int)this + 0x90); // number of objects in list (+0x90)
    if (count != 0) {
        for (objectIndex = 0; objectIndex < count; objectIndex++) {
            objectPtr = *(int *)(*(int *)((int)this + 0x8c) + objectIndex * 8); // each slot is 8 bytes (pointer + maybe another)
            if ((objectPtr != NULL) && (objectPtr != excludeEntity)) {
                // objectPtr points to an object with a vtable; object has a -0x48 offset to get to the actual entity? 
                // Actually: entity = objectPtr - 0x48; so the stored pointer points to something inside the entity.
                int *entityBase = objectPtr - 0x48; // offset to base of entity? Assume entity has vtable at base.
                if (entityBase != NULL) {
                    entity = 0;
                    // call virtual function at vtable[0x10] (probably getEntityOfType or checkInteraction)
                    ok = (*(code **)(*entityBase + 0x10))(0xa7039c8, &entity); // constant likely a type hash
                    if ((ok != 0) && (entity != 0)) {
                        // Check if entity's flags (at +0x18c) have bit 15 set (e.g., alive, not busy)
                        if (((*(uint *)(entity + 0x18c) >> 0xf) & 1) != 0) {
                            // Compute squared distance from player to this object
                            // playerPosStruct is the result of first call to FUN_00471610 (constant for loop)
                            // objectPosStruct is result of second call? Actually inside loop, it calls FUN_00471610 again.
                            int *objectPosStruct = (int *)FUN_00471610(); // get this object's position?
                            dx = *(float *)(playerPosStruct + 0x30) - *(float *)(objectPosStruct + 0x30);
                            dy = *(float *)(playerPosStruct + 0x34) - *(float *)(objectPosStruct + 0x34);
                            dz = *(float *)(playerPosStruct + 0x38) - *(float *)(objectPosStruct + 0x38);
                            distSq = dz*dz + dy*dy + dx*dx;
                            if (distSq < DAT_00e44634) { // global interaction distance threshold
                                FUN_007e34f0(entity); // trigger interaction for this entity
                            }
                        }
                    }
                }
            }
        }
    }

    // Update some state (maybe HUD element, or clear old interactions)
    FUN_007e2ba0();

    // If interaction flag is still set, do something (e.g., display/hide prompt)
    if (*(char *)((int)this + 0x81) != 0) {
        FUN_0081d010(); // likely hide the interaction prompt
    }
}