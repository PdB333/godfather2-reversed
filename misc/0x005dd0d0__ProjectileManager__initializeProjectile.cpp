// FUNC_NAME: ProjectileManager::initializeProjectile
void ProjectileManager::initializeProjectile(float startX, float startY, float startZ) {
    struct ProjectileSlot {
        float field0;
        float field1; // +0x04
        float field2; // +0x08
        float field3; // +0x0C
        float field4; // +0x10
        float field5; // +0x14
        float field6; // +0x18
        float field7; // +0x1C
        uint8_t flagA; // +0x20
        uint8_t flagB; // +0x21
        uint8_t flagC; // +0x22
        uint8_t flagD; // +0x23
        float field9; // +0x24
        float startX; // +0x28
        float startY; // +0x2C
        float velocityX; // +0x30
        float velocityY; // +0x34
        float unused14; // +0x38
        float unused15; // +0x3C
        float startZ; // +0x40
        float field17; // +0x44
        float velocityZ; // +0x48
    };

    struct ProjectileTemplate {
        float maxRange; // +0x00 (compared with g_maxProjectileRange)
        float field1; // +0x04 (another threshold)
        float field2; // +0x08
        float targetX; // +0x0C (used when starting value is negative)
        float targetY; // +0x10 (when <=0, sets flagB)
        float gravityScale; // +0x14 (copied to field2)
        float field6; // +0x18 (only checked if gravityScale <=0)
        float field7; // +0x1C (copied to field3)
        float field8; // +0x20 (copied to field4)
        float field9; // +0x24 (copied to field5)
        float field10; // +0x28 (copied to field6)
        float field11; // +0x2C (copied to field7)
        uint8_t flagByte; // +0x30 (copied to flagA)
        uint32_t timeField; // +0x34 (as float, but treated as integer for sentinel check)
    };

    uint64_t ret = getProjectileSlot(); // Returns destination slot in low 32 bits, template in high 32 bits
    ProjectileSlot* dest = (ProjectileSlot*)(uint32_t)(ret & 0xFFFFFFFF);
    ProjectileTemplate* src = (ProjectileTemplate*)(uint32_t)(ret >> 32);

    float maxRange = g_maxProjectileRange; // DAT_00e2b1a4
    float gravityThreshold = g_gravityThreshold; // DAT_00e44598

    // Validation: source template must satisfy conditions
    if (src->maxRange <= maxRange &&
        src->field1 <= maxRange &&
        src->field2 <= maxRange &&
        (src->gravityScale > 0.0f || (src->gravityScale == 0.0f && (src->field6 > 0.0f || src->field6 == 0.0f))) &&
        src->targetX >= 0.0f &&
        (src->targetY > 0.0f || (src->targetY == 0.0f && src->timeField < 0x17701)))
    {
        // Initialize field0 and flagB
        if (src->maxRange < 0.0f) {
            dest->field0 = src->targetX;
        } else {
            dest->field0 = src->maxRange;
        }

        if (src->targetY <= 0.0f) {
            dest->flagB = 1;
        } else {
            dest->field1 = src->targetY;
            dest->flagB = 0;
        }

        // Initialize timeField (index 0x11) with sentinel check
        if (src->timeField < 0x17701) {
            dest->field17 = *(float*)&src->timeField; // Copy the integer as float
        } else {
            dest->field17 = 1.34525e-40f; // Sentinel value
        }

        // Clamp field0 to [0, maxRange]
        if (dest->field0 > maxRange) {
            dest->field0 = maxRange;
        } else if (dest->field0 < 0.0f) {
            dest->field0 = 0.0f;
        }

        // Clamp timeField sentinel again (note: 96000 vs 0x17701)
        if (*(uint32_t*)&dest->field17 > 96000) {
            dest->field17 = 1.34525e-40f;
        }

        // Copy gravity scale
        dest->field2 = src->gravityScale;

        bool useGravity = (dest->field2 < gravityThreshold);

        // Store starting position
        dest->startX = startX;
        dest->startY = startY;
        dest->startZ = startZ;
        dest->field9 = 0.0f;

        // Compute velocity if gravity is enabled
        if (useGravity) {
            dest->velocityX = 0.0f;
            dest->velocityY = 0.0f;
            dest->velocityZ = 0.0f;
        } else {
            float timeFactor = maxRange / dest->field2; // 1/time?
            float intTime = (float)(int)dest->field17;
            dest->velocityX = (dest->field0 - startX) * timeFactor;
            dest->velocityY = (dest->field1 - startY) * timeFactor;

            // Handle negative int conversions for time
            if ((int)dest->field17 < 0) {
                intTime += g_intToFloatOffset;
            }
            float intStartZ = (float)(int)startZ;
            if ((int)startZ < 0) {
                intStartZ += g_intToFloatOffset;
            }
            dest->velocityZ = (intTime - intStartZ) * timeFactor;
        }

        dest->flagC = 0;
        dest->flagD = 0;

        // Copy additional template data (fields 3-7 and flag byte)
        dest->field3 = src->field7;
        dest->field4 = src->field8;
        dest->field5 = src->field9;
        dest->field6 = src->field10;
        dest->field7 = src->field11;
        dest->flagA = src->flagByte;
    }
}