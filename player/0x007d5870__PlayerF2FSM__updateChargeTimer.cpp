// FUNC_NAME: PlayerF2FSM::updateChargeTimer

#include <math.h>

// Global constants (addresses from the binary)
extern float s_depleteRate;      // DAT_00e531f4
extern float s_chargeRate;       // DAT_00e531f0
extern float s_maxCharge;        // DAT_00e531ec
extern float s_randomFactor;     // DAT_00e531f8 (multiplier for random offset)
extern float s_randomBase1;      // DAT_00d60d04
extern float s_randomBase2;      // DAT_00d5c458

// External event triggers (sound / visual)
extern void triggerEvent(int eventId);   // FUN_007f63e0 (deplete sound?)
extern void triggerEventReady(int eventId); // FUN_007f6420 (ready sound?)

class PlayerF2FSM {
public:
    struct DataBlock {
        int32_t m_chargeDirection;  // +0x8e4: negative = depleting, non-negative = recharging
        uint8_t m_flags;            // +0x8e8: bit0 = ready flag for event
    };

    DataBlock* m_pData;             // +0x58
    float m_chargeLevel;            // +0x78
    uint32_t m_nextActionTime;      // +0x7c

    void updateChargeTimer(uint32_t currentTime, float deltaTime);
};

void PlayerF2FSM::updateChargeTimer(uint32_t currentTime, float deltaTime)
{
    DataBlock* data = m_pData;

    if (data->m_chargeDirection < 0) {
        // Decharging: drain the charge
        m_chargeLevel -= s_depleteRate * deltaTime;
        if (m_chargeLevel < 0.0f) {
            m_chargeLevel = 0.0f;
        }

        if (m_chargeLevel == 0.0f) {
            triggerEvent(0x40); // Play "depleted" event
            // Compute next action time with a random offset
            float offset = s_randomFactor * s_randomBase1 + s_randomBase2;
            m_nextActionTime = currentTime + (uint32_t)round(offset);
        }
    } else {
        // Recharging: increase charge
        if ((data->m_flags & 1) != 0 && m_nextActionTime <= currentTime) {
            triggerEventReady(0x40); // Play "ready" event
        }
        m_chargeLevel += s_chargeRate * deltaTime;
        if (m_chargeLevel > s_maxCharge) {
            m_chargeLevel = s_maxCharge;
        }
    }
}