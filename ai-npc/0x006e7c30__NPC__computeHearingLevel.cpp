// FUNC_NAME: NPC::computeHearingLevel
/* Address: 0x006e7c30
 * Role: Computes hearing level of an NPC towards a sound source.
 * Checks various conditions (flags, line of sight, distance, direction)
 * and accumulates a scalar value representing loudness/perception.
 * Returns 1 if the hearing is significant enough to trigger a reaction.
 */
bool NPC::computeHearingLevel(NPC* npc, HearingConfig* config, float* outHearing) {
    bool result = false;
    float distanceSq;
    float dot;
    float temp;
    float vec[3]; // local_18, local_14, local_10

    // Check: valid NPC, flags match between NPC and config, and config state allows hearing
    if (npc != nullptr &&
        (*(byte*)((uint)config + 0x0A) & *(byte*)((uint)npc + 0x88)) != 0 &&
        FUN_006e7110(config->someObject) != 0 &&
        (*(byte*)((uint)npc + 0x8A) & 8) != 0) {

        // Get sound source position from config (index 3)
        float* sourcePos = (float*)config->fields[3];
        vec[0] = npc->posX - sourcePos[0]; // Could be world position
        vec[1] = npc->posY - sourcePos[1];
        vec[2] = npc->posZ - sourcePos[2];
        distanceSq = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];

        // Check if within hearing range (min and max squared distances)
        if (distanceSq < config->maxDistSq && distanceSq >= config->minDistSq) {
            // Dot product with forward direction? (config->fields[5])
            float* dir = (float*)config->fields[5];
            dot = dir[0]*vec[0] + dir[1]*vec[1] + dir[2]*vec[2];

            if (dot <= 0.0f || dot <= config->dotThreshold - DAT_00e445ac) {
                float baseHearing = 0.0f;

                // Compute initial hearing based on distance difference
                float invSqrtVal = (float)FUN_006b6f90(1.0f); // likely inv sqrt of 1 = 1, but could be sqrt? We keep as sqrt(1)=1
                *outHearing = fabs(sqrtf(distanceSq) - invSqrtVal * config->referenceDist);

                // Additional hearing if certain flags (player related?)
                if (FUN_00690150(0x2e) != 0 || FUN_00717d00() != 0) {
                    float extra = (float)FUN_0045c470(config->fields[4], (int)npc + 0x44);
                    *outHearing = fabs(extra - config->referenceDist) + *outHearing;

                    // Transform direction? FUN_0054ba20 writes to local_c, local_8, local_4
                    FUN_0054ba20(&local_c, &local_18, 0); // local_18 = vec[0]? Actually locals mismatch, but we can assume it modifies globals
                    // Then compute dot with another direction
                    float* dir2 = (float*)config->fields[2];
                    baseHearing = (dir2[0]*local_c + dir2[1]*local_8 + dir2[2]*local_4) * _DAT_00d5fb48;
                }

                if (FUN_006e5bb0(config->fields[4]) == 0) {
                    baseHearing += DAT_0112a9a8;
                }

                *outHearing += baseHearing;

                // Call virtual function on config (first field is vtable?)
                if ((**(code**)(config->fields[0]))(npc) != 0) {
                    *outHearing += _DAT_0112a9ac;
                }

                // Final check: hearing within max threshold, and line of sight/pathing checks
                if (*outHearing <= config->maxHearingTrue && config->maxHearingTrue != *outHearing) {
                    if (FUN_006e7470(config->someObject) != 0 &&
                        FUN_00718d40((int)npc + 0x44) != 0 &&
                        FUN_006e7a40(npc, config->fields[8], config->fields[9]) == 0) {
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}

// Hypothetical structures:
struct HearingConfig {
    void** vtable; // used for function call at offset 0 (virtual method)
    float* direction1; // offset 2 (index 2)
    float* sourcePos; // offset 3
    void* someHandle; // offset 4
    float* direction2; // offset 5
    void* someObject; // offset 7
    void* objA; // offset 8
    void* objB; // offset 9
    uint8 flags; // offset 0x0A
    float minDistSq; // offset 0x0B (index 11)
    float maxDistSq; // offset 0x0C (index 12)
    float dotThreshold; // offset 0x0D (index 13)
    float maxHearingTrue; // offset 0x0E (index 14)
    float referenceDist; // offset 0x0F (index 15)
};