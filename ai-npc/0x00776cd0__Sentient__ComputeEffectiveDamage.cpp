// FUNC_NAME: Sentient::ComputeEffectiveDamage
// Address: 0x00776cd0
// Computes the final damage after applying resistance from an associated component.

#include <cstdint>

// Global tuning constants (hypothetical names)
extern float g_BaseDamage;          // _DAT_00d5780c
extern float g_ResistanceMin;       // _DAT_00d68260
extern float g_ResistanceMax;       // _DAT_00d6825c
extern float g_ResistanceScale;     // _DAT_00d68258

// Forward declaration of the resistance provider class
class ResistableEntity;

float __thiscall Sentient::ComputeEffectiveDamage()
{
    float damage = g_BaseDamage;

    // m_pComponent is at offset +0x70 in this object
    uintptr_t componentPtr = *(uintptr_t*)((char*)this + 0x70);

    // Check if the component pointer is valid (not null and not a sentinel value 0x48)
    if (componentPtr != 0 && componentPtr != 0x48)
    {
        // The component pointer points into a member of ResistableEntity.
        // Subtract offset 0x48 to recover the base pointer of the containing object.
        ResistableEntity* entity = (ResistableEntity*)(componentPtr - 0x48);

        // Virtual function call at vtable offset 0x1b0 (108th virtual method)
        float resistance = entity->GetResistance();

        // Clamp resistance value to [g_ResistanceMin, g_ResistanceMax]
        float clamped = resistance;
        if (clamped > g_ResistanceMin)
        {
            clamped = resistance;  // redundant in decompiler, but shows original logic
            if (clamped >= g_ResistanceMax)
            {
                clamped = g_ResistanceMax;
            }
        }
        else
        {
            clamped = g_ResistanceMin;
        }

        // Apply scaled resistance reduction
        damage -= (clamped - g_ResistanceMin) * g_ResistanceScale;
    }

    return damage;
}