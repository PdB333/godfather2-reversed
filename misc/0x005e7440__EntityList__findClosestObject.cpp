// FUNC_NAME: EntityList::findClosestObject
#include <cstdint>

class Entity {
public:
    float positionX; // +0x40
    float positionY; // +0x44
    float positionZ; // +0x48
};

class EntityList {
public:
    bool findClosestObject(float* point, float* outBestDistSq);
private:
    // Layout:
    // +0x04: Entity* m_entities[4];
    // +0x18: uint8_t m_slotFlags[4];   // nonzero if slot occupied
    // +0x1c: uint8_t m_count;          // number of valid slots
    Entity* m_entities[4];
    uint8_t m_slotFlags[4];
    uint8_t m_count;
};

bool EntityList::findClosestObject(float* point, float* outBestDistSq) {
    // Global search radius squared (initial threshold)
    const float g_searchRadiusSq = *(float*)0x00e2e50c;
    *outBestDistSq = g_searchRadiusSq;

    uint8_t count = m_count;
    bool found = false;

    for (uint32_t i = 0; i < count; ++i) {
        // Reload count each iteration (as in original)
        count = m_count;
        if (i >= 4 || i >= count) break; // original check: (byte)uVar4 < 4 and (uVar4 & 0xff) < uVar3

        if (m_slotFlags[i] != 0) {
            Entity* ent = m_entities[i];
            if (ent != nullptr) {
                float dx = point[0] - ent->positionX;
                float dy = point[1] - ent->positionY;
                float dz = point[2] - ent->positionZ;
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq < *outBestDistSq) {
                    *outBestDistSq = distSq;
                    found = true;
                }
            }
        }
    }
    return found;
}