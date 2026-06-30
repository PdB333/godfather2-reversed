// FUNC_NAME: DebugManager::drawDebugLineWithGlobalPosition
// Function address: 0x71c720
// Role: Retrieves a global Vector3 from DebugManager singleton and forwards to debug draw function (FUN_0071c440) with extra parameters.
// Assumes FUN_00471610 returns pointer to DebugManager instance (singleton).
// Offsets: +0x30 = debugPosition (Vector3 of 3 floats, 12 bytes)

struct DebugVector3 {
    float x;
    float y;
    float z;
};

// Forward declaration
void DebugManager::drawDebugLine(DebugVector3* pos, undefined4 param1, undefined4 param2, undefined4 param3); // FUN_0071c440

class DebugManager {
public:
    static DebugManager* getInstance(); // FUN_00471610

    // +0x30: debug position used for drawing markers, etc.
    DebugVector3 m_debugPosition;
};

void __cdecl DebugManager::drawDebugLineWithGlobalPosition(undefined4 param1, undefined4 param2, undefined4 param3) {
    DebugManager* mgr = DebugManager::getInstance();
    // Extract the vector (x,y packed in 8 bytes, z as separate 4 bytes)
    DebugVector3 pos;
    pos.x = reinterpret_cast<float*>(&mgr->m_debugPosition)[0];
    pos.y = reinterpret_cast<float*>(&mgr->m_debugPosition)[1];
    pos.z = reinterpret_cast<float*>(&mgr->m_debugPosition)[2];
    // Alternative: memcpy or direct assignment using the known layout.
    // The decompiled code fetches an 8-byte (x,y) and a 4-byte (z) from consecutive offsets.
    // We can simply pass &pos (which is same as &mgr->m_debugPosition) after constructing.
    // However, the original does a stack copy, so we emulate that.
    DebugManager::drawDebugLine(&pos, param1, param2, param3);
}