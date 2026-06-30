// FUNC_NAME: AudioZone::checkEntity
// Address: 0x004f8f60
// This function checks if an entity's position is within a defined distance range
// from the current audio listener, and triggers an event if so.
// It belongs to an audio zone/trigger system, likely part of the EARS engine.

void __thiscall AudioZone::checkEntity(int entity, unsigned int param_3)
{
    // Pointer to the zone's internal data (offset +0x04 from this)
    ZoneData* pZoneData = *(ZoneData**)(this + 4);

    // Read entity's position (at offsets +0x100, +0x104, +0x108)
    Vector3 entityPos;
    entityPos.x = *(float*)(entity + 0x100);
    entityPos.y = *(float*)(entity + 0x104);
    entityPos.z = *(float*)(entity + 0x108);

    // Global time/scale factor (used as w-component in some calculations)
    float worldW = DAT_00e2b1a4;

    // Obtain the listener's position from thread-local storage.
    // FS segment base +0x2C points to a per-thread data structure.
    // At [data + 8] we get the listener array, then offset by 0x80 and pZoneData->offsetIndex.
    float* listenerPos = (float*)( *(int*)( **(int**)(__readfsdword(0x2C) ) + 8 ) + 0x80 + *(int*)(pZoneData + 0x10) );

    // Compute delta = entityPos - listenerPos (only x,y,z used for distance)
    Vector3 delta;
    delta.x = entityPos.x - listenerPos[0];
    delta.y = entityPos.y - listenerPos[1];
    delta.z = entityPos.z - listenerPos[2];
    float deltaW = worldW - listenerPos[3]; // w-component not used in distance

    // Squared distance
    float distSq = delta.x*delta.x + delta.y*delta.y + delta.z*delta.z;

    // pZoneData+0x30 = minDistSq, pZoneData+0x34 = maxDistSq
    if (distSq >= *(float*)(pZoneData + 0x30) && distSq < *(float*)(pZoneData + 0x34))
    {
        float dist = sqrtf(distSq);

        // Pre-trigger effect (occlusion/state preparation)
        FUN_004f8980();

        // Global threshold (DAT_00e2e210) – possibly a maximum distance for trigger
        if (g_fExtraDistanceThreshold < dist)
        {
            // Execute the actual trigger, passing entity, position reference, distance, user data, and -1
            FUN_004f8aa0(entity, &entityPos, dist, param_3, 0xffffffff);
        }
    }
}