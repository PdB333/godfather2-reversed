// FUNC_NAME: StatModifierManager::updateModifiers

/* Function address: 0x005dd660
 * Role: Computes final stat modifiers (damage/effect multipliers) for a game object.
 * Accesses a global modifier table, applies up to 5 sequential modifier entries,
 * and clamps results to valid ranges. Returns success code 0x17701 (96001)
 */

class StatModifierManager {
public:
    // Offset map:
    // +0x38: modifierEntries[5] array (each 104 bytes = 26 floats)
    // +0x214: weaponSlot / equipmentType (int, -1 if none)
    // +0x240: baseDamageMultiplier (float)
    // +0x244: damageRange (float)
    // +0x254: baseEffectValue (float)
    // +0x27c: effectMultiplier (float)
    // +0x284: finalMinDamage (float)
    // +0x288: finalMaxDamage (float)
    // +0x28c: finalMinEffect (float)
    // +0x290: finalMaxEffect (float)
    // +0x294: maxEffectValue (uint, clamped to 96000)
    // +0x298: isSpecialEffect (char)

    int updateModifiers();

private:
    // NOTE: The class definition is incomplete; only fields used in this function are noted.
};

// Internal helper: likely reads a random index from a global hash table
extern int __cdecl getHashIndex(uint* outIndex, int seed);
// Internal: checks if a modifier entry is active/enabled
extern bool __thiscall isModifierActive(StatModifierManager* this);

// Global table: each entry is a pointer to a modifier record (with a float at +0x68)
extern void** gModifierDataTable; // 0x01223504

int StatModifierManager::updateModifiers() {
    // ----- First step: potentially pick a random extra modifier from global table -----
    uint localHash = 0;
    char cResult = getHashIndex(&localHash, 0);
    if (cResult && ((localHash ^ 0xad103100) < *(byte*)((int)gModifierDataTable + 0x1c))) {
        // Index = (localHash ^ 0xad103100) & 0xff
        int index = (localHash ^ 0xad103100) & 0xff;
        // Read a pointer from table at offset 4 + index*4, then get float at +0x68
        float* tableEntry = (float*)(*(int*)((int)gModifierDataTable + 4 + index * 4) + 0x68);
        *(int*)(this + 700) = *(int*)tableEntry; // copy 4 bytes (float) to +700 (0x2bc)
    }

    float zero = 0.0f;

    // ----- Determine base min/max damage/effect from equipment type -----
    if (*(int*)(this + 0x214) == -1) {
        // No weapon equipped: use default values from hardcoded globals
        *(float*)(this + 0x284) = *(float*)0x00e2e780; // DAT_00e2e780
        *(float*)(this + 0x288) = *(float*)0x00e2b1a4; // DAT_00e2b1a4
    } else {
        // Weapon equipped: call helper to check something
        bool active = isModifierActive(this);
        if (*(char*)(this + 0x298) == '\0') {
            // Normal case: compute final range from base and multipliers
            *(float*)(this + 0x288) = *(float*)(this + 0x244); // damageRange
            *(float*)(this + 0x284) = *(float*)(this + 0x29c) * *(float*)(this + 0x27c) * *(float*)(this + 0x240);
        } else {
            // Special effect active: reset minDamage, set maxDamage to damageRange
            *(float*)(this + 0x284) = zero;
            *(float*)(this + 0x288) = *(float*)(this + 0x244);
        }
    }

    // Copy initial final values from computed base
    *(float*)(this + 0x28c) = *(float*)(this + 0x284); // finalMinEffect = finalMinDamage?
    *(float*)(this + 0x294) = *(float*)(this + 0x254); // maxEffectValue = baseEffectValue
    float* entryBase = (float*)(this + 0x38); // pointer to first modifier entry
    *(float*)(this + 0x290) = *(float*)(this + 0x288); // finalMaxEffect = finalMaxDamage

    // ----- Apply up to 5 sequential modifier entries -----
    int entryCount = 5;
    do {
        if (entryBase[-0xb] != -NAN) { // Check if entry is active (non-NaN flag)
            bool active = isModifierActive(this);
            if (active) {
                char specialFlag = *(char*)(entryBase - 6); // offset -24? (char)
                if (specialFlag == '\0') {
                    // Scale both damage and effect by the two multipliers (entry[0], entry[1])
                    *(float*)(this + 0x284) = *entryBase * *(float*)(this + 0x284);
                    *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * *entryBase;
                    *(float*)(this + 0x288) = *(float*)(this + 0x288) * entryBase[1];
                    *(float*)(this + 0x290) = *(float*)(this + 0x290) * entryBase[1];
                } else {
                    // Special: only scale effect, and set a new effect base from entry[5]
                    *(float*)(this + 0x28c) = *(float*)(this + 0x28c) * *entryBase;
                    *(float*)(this + 0x290) = entryBase[1] * *(float*)(this + 0x290);
                    *(float*)(this + 0x294) = entryBase[5]; // new maxEffectValue
                }

                // Additional flag checks (nested)
                char flagA = *(char*)((int)entryBase - 0x15); // offset -21 bytes
                if (flagA != '\0') {
                    char flagB = *(char*)((int)entryBase - 0x16); // offset -22 bytes
                    if (flagB == '\0') {
                        char flagC = *(char*)((int)entryBase - 0x17); // offset -23 bytes
                        if (flagC != '\0') {
                            *(float*)(this + 0x288) = zero; // maxDamage = 0
                        }
                    } else {
                        entryBase[-0xb] = -NAN; // Mark entry as inactive (set to NaN)
                    }
                }
            }
        }
        entryBase += 0x1a; // Advance to next entry (26 floats = 104 bytes)
        --entryCount;
    } while (entryCount != 0);

    // ----- Clamp final values to zero if negative -----
    if (*(float*)(this + 0x284) <= zero && zero != *(float*)(this + 0x284)) {
        *(float*)(this + 0x284) = zero;
    }
    if (*(float*)(this + 0x288) <= zero && zero != *(float*)(this + 0x288)) {
        *(float*)(this + 0x288) = zero;
    }
    if (*(float*)(this + 0x28c) <= zero && zero != *(float*)(this + 0x28c)) {
        *(float*)(this + 0x28c) = zero;
    }
    if (*(float*)(this + 0x290) <= zero && zero != *(float*)(this + 0x290)) {
        *(float*)(this + 0x290) = zero;
    }

    // Cap maxEffectValue at 96000
    if (*(uint*)(this + 0x294) > 96000) {
        *(uint*)(this + 0x294) = 96000;
    }

    return 0x17701; // 96001
}