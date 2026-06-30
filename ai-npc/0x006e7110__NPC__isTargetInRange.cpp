// FUNC_NAME: NPC::isTargetInRange
// Function address: 0x006e7110
// Role: Determines if a given target entity is within engagement range for this NPC.
// The function checks a flag, then compares the target handle with the current target.
// If the target is different and the NPC has an active target, it calculates distances
// from this NPC to two reference positions (likely the player and the target) and
// checks if the target is within an adaptive threshold.

#include <cmath>

// Forward declaration of a position provider (e.g., player entity or anchor)
struct PositionProvider {
    char pad_0x30[0x30]; // padding to offset
    float x; // +0x30
    float y; // +0x34
    float z; // +0x38
};

// Global constant from data section 0x00d5fb0c
extern float g_fRangeOffset;

// External function that returns a pointer to a position provider (likely the player)
PositionProvider* __stdcall getPlayerPositionProvider();

int __thiscall NPC::isTargetInRange(NPC* this, int aTargetEntity) {
    // Check flag at +0x8a, bit 0 (maybe "hasTarget" or "engaged")
    if ((this->m_flags & 1) != 0) {
        // Get the current target handle from +0x60
        int* pCurrentTargetHandle = this->m_pTargetHandle;
        int currentEntity;
        if (pCurrentTargetHandle == 0) {
            currentEntity = 0;
        } else {
            // The handle points to a structure that is 0x48 bytes into the entity;
            // subtracting 0x48 gives the entity base pointer
            currentEntity = reinterpret_cast<int>(pCurrentTargetHandle) - 0x48;
        }
        // If the given target is the same as the current one, no need to re-evaluate
        if (currentEntity != aTargetEntity) {
            // Need to evaluate range
            if (this->m_pTargetHandle == 0) {
                return 0; // No target handle means cannot reach
            }
            if (this->m_pTargetHandle != reinterpret_cast<int*>(0x48)) {
                // Get first reference position (e.g., player)
                PositionProvider* posProv1 = getPlayerPositionProvider();
                float dx1 = posProv1->x - this->m_position.x; // +0x44
                float dy1 = posProv1->y - this->m_position.y; // +0x48
                float dz1 = posProv1->z - this->m_position.z; // +0x4c
                // Get second reference position (could be target or another anchor)
                PositionProvider* posProv2 = getPlayerPositionProvider(); // same call? Might be different in actual code
                float dx2 = posProv2->x - this->m_position.x;
                float dy2 = posProv2->y - this->m_position.y;
                float dz2 = posProv2->z - this->m_position.z;
                float thresholdSq = 0.0f;
                float dist2 = std::sqrt(dz2 * dz2 + dy2 * dy2 + dx2 * dx2);
                float adjustedDist = dist2 - g_fRangeOffset;
                if (adjustedDist > 0.0f) {
                    thresholdSq = adjustedDist * adjustedDist;
                }
                float dist1Sq = dz1 * dz1 + dy1 * dy1 + dx1 * dx1;
                if (dist1Sq < thresholdSq) {
                    return 1;
                }
            }
            return 0;
        }
    }
    return 1;
}