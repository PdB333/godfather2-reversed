// FUNC_NAME: Entity::getHealthBarValue

#include <cstdint>

// Forward declarations (assumed types based on EA EARS engine)
struct EntityData; // core entity data
struct HealthComponent; // health component

// External globals (from game data)
extern float g_fHealthMin;      // DAT_00e2b05c
extern float g_fHealthMax;      // DAT_00e2b1a4
extern float g_fHealthBarScale; // _DAT_00e44670

// External function: gets a component pointer given an identifier (offset 0x18)
HealthComponent* __stdcall getHealthComponent(uint32_t componentId); // FUN_005dc670

// Class definition (incomplete, only relevant members shown)
class Entity {
public:
    // Offset 0x00: pointer to entity data (first member)
    EntityData* m_pEntity;

    // Decompiled function: compute health bar value (0-127) from current health
    short getHealthBarValue() const;
};

// Reconstructed function
short Entity::getHealthBarValue() const {
    short result = 0;

    // Validate this pointer and entity data
    if (!this || !m_pEntity)
        return 0;

    EntityData* pEntity = m_pEntity;

    // Check bit 2 (value 4) of flags at offset 0x07 – if set, entity is dead/inactive
    // +0x07: flags byte
    if (pEntity->flags & 4)  // assuming a flags field at +7
        return 0;

    // Get the health component via identifier at offset 0x18
    // +0x18: component handle or ID
    uint32_t componentId = *(uint32_t*)((uint8_t*)pEntity + 0x18);
    HealthComponent* pHealth = getHealthComponent(componentId);
    if (!pHealth)
        return 0;

    // Read health value at offset 0x280
    // +0x280: health float
    float health = *(float*)((uint8_t*)pHealth + 0x280);

    // Range check: health must be between min and max globals
    if (health < g_fHealthMin || health > g_fHealthMax)
        return 0;

    // Scale health to 0-127 range
    int scaled = static_cast<int>(health * g_fHealthBarScale);
    if (scaled < 1)
        return 0;
    if (scaled >= 0x7F)
        return 0x7F;

    return static_cast<short>(scaled);
}