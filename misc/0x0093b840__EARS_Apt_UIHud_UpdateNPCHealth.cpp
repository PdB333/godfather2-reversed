// Xbox PDB: EARS_Apt_UIHud_UpdateNPCHealth
// FUNC_NAME: NPC::updateHealth
// Reconstructed C++ for function 0x0093b840
// This function updates the NPC's health bar / health display value

// Forward declarations and external references
extern float DAT_00d5e288; // Maximum health display scale (e.g., 100.0f)
extern void FUN_005a04a0(const char* message, int arg1, float* data, int arg2); // Debug/log function

// Abstract interface for health data provider (likely a component with vtable)
class IHealthProvider {
public:
    virtual ~IHealthProvider() = 0;
    virtual float getCurrentHealth() = 0;   // vtable offset +0xC0
    virtual float getMaxHealth() = 0;       // vtable offset +0xC4
    // Additional virtual functions not used here
};

class NPC {
public:
    // Member offsets (relative to 'this')
    // +0x110 : current displayed health (scaled)
    float m_displayHealth;
    // +0x114 : pointer to health data provider (may be an inner component)
    IHealthProvider* m_healthProvider;

    // Primary method: update the health display value
    void updateHealth();
};

void NPC::updateHealth() {
    float newDisplayHealth;

    IHealthProvider* healthProvider = m_healthProvider;

    if (healthProvider != nullptr) {
        // The stored pointer points 0x48 bytes *after* the actual health component object
        // Subtract 0x48 to get the proper vtable base
        IHealthProvider* healthBase = reinterpret_cast<IHealthProvider*>(reinterpret_cast<char*>(healthProvider) - 0x48);

        float currentHP = healthBase->getCurrentHealth();
        float maxHP = healthBase->getMaxHealth();

        float scaledHealth = (currentHP / maxHP) * DAT_00d5e288;

        if (scaledHealth > 0.0f) {
            // Clamp scaledHealth to not exceed the maximum display value
            newDisplayHealth = (scaledHealth < DAT_00d5e288) ? scaledHealth : DAT_00d5e288;
        } else {
            newDisplayHealth = 0.0f;
        }
    } else {
        newDisplayHealth = 0.0f;
    }

    // Update if value changed
    if (newDisplayHealth != m_displayHealth) {
        m_displayHealth = newDisplayHealth;
        FUN_005a04a0("UpdateNPCHealth", 0, &newDisplayHealth, 0);
    }
}