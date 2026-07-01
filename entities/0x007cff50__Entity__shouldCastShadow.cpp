// FUNC_NAME: Entity::shouldCastShadow
// Function address: 0x007cff50
// Role: Determines if an entity should cast a shadow based on global shadow toggle, entity-specific flag, and distance comparison.

#include <cstdint>

// Global shadow distance threshold (from game data)
extern float gShadowDistance; // _DAT_00d577a0

// Global function to check if shadow rendering is enabled
extern bool isGlobalShadowEnabled(); // FUN_004ac260

// Entity class (partial)
class Entity {
public:
    // +0x30: Maximum shadow casting distance
    float mShadowCullDistance;
    // +0xAC: Bitfield of entity flags, bit 1 (0x2) forces shadow cast
    uint32_t mFlags;

    bool shouldCastShadow() {
        // Check if global shadow is enabled
        bool castShadow = isGlobalShadowEnabled();
        
        if (!castShadow) {
            // If global disabled, allow shadow only if entity has forced flag
            if ((mFlags & 0x2) == 0) {
                castShadow = false;
            } else {
                castShadow = true;
            }
        }
        
        // Final check: only cast shadow if active and the entity's cull distance exceeds global threshold
        if (castShadow && (gShadowDistance < mShadowCullDistance)) {
            return true;
        }
        return false;
    }
};