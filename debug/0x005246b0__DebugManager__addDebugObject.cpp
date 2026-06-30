// FUNC_NAME: DebugManager::addDebugObject

// Global debug object storage (up to 24 entries)
static int g_debugObjectCount = 0; // DAT_01194d00
static void* g_debugObjectList[24]; // DAT_01197d10
static float g_debugPosX[24]; // DAT_01194b80
static float g_debugPosY[24]; // DAT_01194b84
static float g_debugPosZ[24]; // DAT_01194b88
static float g_debugMagnitude[24]; // DAT_01194b8c

// External constants
extern float g_speedScale; // DAT_00e2cd54
extern float g_timeScale; // DAT_00e44718

// Entity structure offsets (relative to this pointer)
// +0x1c: float unknown1
// +0x38: float radiusA
// +0x3c: float radiusB
// +0x70: float directionX
// +0x74: float directionY
// +0x78: float directionZ
// +0x7c: float directionW? (unused)
// +0x80: float positionX
// +0x84: float positionY
// +0x88: float positionZ
// +0x8c: float positionW? (unused)
// +0x451: char isActive
// +0x454: void* dataPtr (points to some data with +0xa4 float speed)
// +0x460: ushort flags

void DebugManager::addDebugObject(void* entity) {
    // Check conditions: flags bits 1-2 clear, count < 24, and entity active
    if (((*(byte*)((int)entity + 0x460) & 6) == 0) &&
        (g_debugObjectCount < 24) &&
        (*(char*)((int)entity + 0x451) != '\0')) {
        
        int index = g_debugObjectCount;
        g_debugObjectList[index] = entity;
        
        // Compute scaled velocity components
        float speed = *(float*)(*(int*)((int)entity + 0x454) + 0xa4) * g_timeScale;
        float dirX = *(float*)((int)entity + 0x70);
        float dirY = *(float*)((int)entity + 0x74);
        float dirZ = *(float*)((int)entity + 0x78);
        float posX = *(float*)((int)entity + 0x80);
        float posY = *(float*)((int)entity + 0x84);
        float posZ = *(float*)((int)entity + 0x8c);
        
        // Store predicted positions (velocity * direction + position)
        g_debugPosX[index] = speed * dirX + posX;
        g_debugPosY[index] = speed * dirY + posY;
        g_debugPosZ[index] = speed * dirZ + posZ;
        
        // Compute magnitude of velocity vector (using scaled radii)
        float radiusA = *(float*)((int)entity + 0x38);
        float radiusB = *(float*)((int)entity + 0x3c);
        float scale = *(float*)((int)entity + 0x1c) * g_speedScale;
        float diff = (radiusA - radiusB) * scale;
        float sum = (radiusA + radiusB) * scale;
        float speed2 = *(float*)(*(int*)((int)entity + 0x454) + 0xa4) * g_timeScale;
        g_debugMagnitude[index] = sqrtf(speed2 * speed2 + diff * diff + sum * sum);
        
        // Mark entity as processed (set bit 2)
        *(ushort*)((int)entity + 0x460) |= 4;
        g_debugObjectCount++;
    }
}