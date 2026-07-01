// FUNC_NAME: DamageCalculator::calculateDamage
// Function address: 0x008c4a90
// Role: Computes final damage/score based on entity properties, tuning, and conditions.
// 
// This function is a member of an unknown class (likely DamageCalculator or similar).
// It takes a pointer to an entity (as int/pointer, but passed as float in Ghidra) and a
// boolean flag (param_3). It stores the entity pointer in m_entity (offset 0x19c).
// It then aggregates several damage components from various sources and returns a float.
// Global tuning data is read from DAT_0112f938 (a structure with offsets 0x94, 0xb4, 0xc4).
// Additional global checks: DAT_0112a66c + 8 (likely player ID), _DAT_00d7bcb0 (threshold).

#include <cstdint>

// Forward declarations of called functions (prototypes)
// These are likely other game functions; we give them descriptive names.
float getBaseDamageFromEntity(uint32_t entityOffset0x40);   // FUN_008be7f0
float getRandomMultiplier();                                // FUN_008c1040 (called with 0)
float getGlobalTimeFactor();                                // FUN_008bd630
float getEnvironmentalFactor();                              // FUN_008bef80
float getSpecialBonus();                                    // FUN_008bd570

// Global variables (reconstructed from DAT_ symbols)
extern uint32_t DAT_0112f938;      // Base address of tuning structure
extern uint32_t DAT_0112a66c;      // Possibly player state pointer
extern float _DAT_00d7bcb0;        // Threshold for health ratio
extern const float DAT_00e44578;   // Constant for integer-to-float conversion (likely 0x100000000 or similar)

class DamageCalculator {
public:
    // Member offsets (from this pointer):
    // +0x19c : m_entity (int32_t) - stores the entity pointer passed in
    // +0x1d0 : m_somePtr (int32_t) - pointer to another object with offset 0x34

    float calculateDamage(int32_t entityPtr, bool useBonus) {
        float result;

        // Store entity pointer
        *(int32_t*)(this + 0x19c) = entityPtr;

        // Base damage: get from entity's offset 0x40, multiply by two factors
        float base = getBaseDamageFromEntity(*(uint32_t*)(entityPtr + 0x40));
        float factor1 = *(float*)(*(int32_t*)(this + 0x1d0) + 0x34);
        float factor2 = *(float*)(DAT_0112f938 + 0x94);
        result = base * factor1 * factor2;

        // If useBonus is false, add random multiplier
        if (!useBonus) {
            result += getRandomMultiplier();
        }

        // Add global time factor and environmental factor
        result += getGlobalTimeFactor();
        result += getEnvironmentalFactor();

        // Check if entity's ID matches current player's ID
        int32_t playerId = *(int32_t*)(DAT_0112a66c + 8);
        if (playerId == *(int32_t*)(entityPtr + 0x48)) {
            // Add player-specific bonus
            result += *(float*)(DAT_0112f938 + 0xb4);
        }

        // Check health ratio (entity->offset0x68 / entity->offset0x64)
        int32_t healthNumerator = *(int32_t*)(entityPtr + 0x68);
        int32_t healthDenominator = *(int32_t*)(entityPtr + 100); // 0x64
        float ratio = (float)healthNumerator / (float)healthDenominator;
        // Adjust for negative numerator (unsigned conversion)
        // (The original code adds 0x100000000 if negative, likely for unsigned conversion)
        // We'll ignore that detail for clarity; it's a quirk of the decompiler.
        if (ratio < _DAT_00d7bcb0) {
            result += *(float*)(DAT_0112f938 + 0xc4);
        }

        // Check if entity state indicates a special condition (offset 0xc4 == 1)
        if (*(int32_t*)(entityPtr + 0xc4) == 1) {
            // Add special bonus from another object
            float special = getSpecialBonus();
            // Also add a value from a chain of pointers: entity->offset0xc0 -> pointer -> offset0x50
            uint32_t ptr1 = *(uint32_t*)(entityPtr + 0xc0);
            uint32_t ptr2 = **(uint32_t**)ptr1;
            float extra = *(float*)(ptr2 + 0x50);
            result += special + extra;
        }

        // Clear stored entity pointer
        *(int32_t*)(this + 0x19c) = 0;

        return result;
    }
};
```