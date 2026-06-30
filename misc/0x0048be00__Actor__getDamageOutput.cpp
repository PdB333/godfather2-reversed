// FUNC_NAME: Actor::getDamageOutput
// Function at 0x0048be00: Computes final damage by multiplying base damage (from stats) with a multiplier.
// Fields:
//   Actor+0x1c: m_pStats (Stats*)
//   Actor+0x2c: m_fDamageMultiplier (float)
//   Stats+0x18: m_nBaseDamage (int)

struct Stats {
    int m_nBaseDamage; // +0x18
    // ... possibly other fields
};

class Actor {
public:
    // ... other methods

    float __thiscall getDamageOutput() const {
        float result = 0.0f;
        if (m_pStats != nullptr) {
            result = static_cast<float>(m_pStats->m_nBaseDamage) * m_fDamageMultiplier;
        }
        return result;
    }

private:
    // Assuming offsets based on decompilation:
    // +0x00: vtable?  
    // ...
    Stats* m_pStats;          // +0x1c
    float m_fDamageMultiplier; // +0x2c
    // ... other members
};