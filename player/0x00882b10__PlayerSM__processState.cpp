// FUNC_NAME: PlayerSM::processState
// Address: 0x00882b10
// Role: State machine update handler for player states (state IDs 10-17)
// Handles various player actions: entering/exiting vehicles, aiming, moving, etc.

#include <cstdint>

class PlayerSM {
public:
    // Virtual table offsets (assumed)
    virtual bool isActive();                    // +0x30
    virtual void onEnterVehicle();              // +0x288
    virtual void onExitVehicle();               // +0x298

    // Member offsets (in int units, *4 for byte offset)
    // +0x68: m_pOwner (pointer to entity/player object)
    // +0x6C: m_targetX (float)
    // +0x70: m_targetY (float)
    // +0x74: m_targetZ (float)
    // +0x78: m_flags (bitfield)
    // +0x7C: m_someFloat (float)
    // +0x80: m_sqDistThreshold (float)
    // +0x30: m_someOtherFloat (float) [offset 0x0c*4]

    uint8_t processState(uint32_t unk1, uint32_t unk2, uint32_t unk3, int32_t stateId, uint32_t unk4);
};

// External function declarations (renamed based on observed behavior)
extern void setAnimation(uint32_t animId);                          // 0x0086a770
extern void resetState();                                           // 0x0085f850
extern void setGlobalFlag(uint32_t flag);                           // 0x00766470
extern int32_t isPlayerInVehicle();                                 // 0x00542d70
extern float getPlayerPositionX();                                  // 0x00549a20
extern float getPlayerPositionY();                                  // 0x00549a10
extern float getPlayerPositionZ();                                  // 0x00549a00
extern void setSomeFloat1(float val);                               // 0x0086b830
extern void setSomeFloat2(float val);                               // 0x0086b7d0
extern void setSomeFloat3(float val);                               // 0x0086b7b0
extern uint32_t getSomeValue();                                     // 0x0086d6b0
extern uint32_t getAnotherValue();                                  // 0x0085e970
extern void setSomeInt(uint32_t val);                               // 0x0086b7f0
extern void setSomeOther(uint32_t val);                             // 0x0086b810
extern void someInit(uint32_t a, uint32_t b);                       // 0x0086d060
extern bool checkCondition(float* out, int32_t* data);              // 0x008824c0
extern void clearSomeData(int32_t* data);                           // 0x005fde60
extern int32_t getPlayer();                                         // 0x00471610
extern void setAnimationState(int32_t state);                       // 0x00544ae0
extern void handleExit();                                           // 0x00882740
extern float calculateSomething(int32_t entity);                    // 0x008821f0
extern uint8_t baseClassHandler(uint32_t, uint32_t, uint32_t, int32_t, uint32_t); // 0x004ac700

// Global variables (from data section)
extern float g_someGlobalFloat;     // 0x00d5780c
extern float g_thresholdDot;        // 0x00d76e7c
extern float g_someOtherThreshold;  // 0x00d76e78

uint8_t PlayerSM::processState(uint32_t unk1, uint32_t unk2, uint32_t unk3, int32_t stateId, uint32_t unk4) {
    uint8_t result = 1;
    float localX, localY, localZ; // stack variables for position

    switch (stateId - 10) {
    case 0: // State 10: Entering vehicle?
        if (m_pOwner != 0) {
            setAnimation(unk2); // unk2 is likely animation ID
            if (*(int32_t*)(m_pOwner + 0xf2c) == 1) {
                resetState();
            }
            if ((*(uint32_t*)(m_pOwner + 0xf28) >> 0x15) & 1) {
                setGlobalFlag(0x1000000);
            }
            if (*(int32_t*)(m_pOwner + 0xaa0) != 0 && isPlayerInVehicle() != 0) {
                float posX = getPlayerPositionX();
                float posY = getPlayerPositionY();
                float posZ = getPlayerPositionZ();
                setSomeFloat1(posX);
                setSomeFloat2(posY);
                setSomeFloat3(posZ);
                uint32_t val1 = getSomeValue();
                setSomeInt(val1);
                uint32_t val2 = getAnotherValue();
                setSomeOther(val2);
                return 1;
            }
        }
        break;

    case 1: // State 11: Some initialization
        isPlayerInVehicle();
        someInit(0, 1);
        return 1;

    case 2: // State 12: Check condition and clear
        if (isActive()) {
            if (checkCondition(&localX, &m_targetX)) {
                m_flags |= 2;
                int32_t owner = m_pOwner;
                clearSomeData(&m_targetX);
                *(int32_t*)(owner + 0x1108) = 0;
                return 1;
            }
        }
        break;

    case 3: // State 13: Distance check to player
        {
            int32_t player = getPlayer();
            float dx = (float)m_targetX - *(float*)(player + 0x30);
            float dy = (float)m_targetY - *(float*)(player + 0x34);
            float dz = (float)m_targetZ - *(float*)(player + 0x38);
            if (dx*dx + dy*dy + dz*dz < (float)m_sqDistThreshold) {
                // Call virtual function on owner
                (*(void (**)(int32_t))(*(int32_t*)m_pOwner + 0x288))();
                return 1;
            }
        }
        break;

    case 4: // State 14: No action
        break;

    case 5: // State 15: Exit vehicle
        m_flags &= 0xfffffffb; // Clear bit 2
        setAnimationState(2);
        (*(void (**)(int32_t))(*(int32_t*)m_pOwner + 0x298))(); // onExitVehicle
        if ((*(uint32_t*)(m_pOwner + 0xc88) & 0x100) == 0) {
            m_flags |= 0x20;
            setGlobalFlag(0x1000000);
            return 1;
        }
        handleExit();
        return 1;

    case 6: // State 16: Aiming/movement check
        m_flags |= 4;
        setAnimationState(1);
        if (!isActive()) {
            localX = (float)m_targetX;
            localY = (float)m_targetY;
            localZ = (float)m_targetZ;
        }
        {
            int32_t player1 = getPlayer();
            int32_t player2 = getPlayer(); // Possibly different object?
            float playerY = *(float*)(player1 + 0x34);
            float dirY = *(float*)(player2 + 0x24);
            float playerX = *(float*)(player1 + 0x30);
            float playerZ = *(float*)(player1 + 0x38);
            float dirX = *(float*)(player2 + 0x20);
            float dirZ = *(float*)(player2 + 0x28);
            m_someFloat = g_someGlobalFloat;
            float dot = dirX * (localX - playerX) + dirY * (localY - playerY) + dirZ * (localZ - playerZ);
            if (dot < g_thresholdDot) {
                float result = calculateSomething(m_pOwner);
                m_someFloat = result;
                return 1;
            }
        }
        break;

    case 7: // State 17: Update some parameters
        if (isPlayerInVehicle() != 0) {
            setSomeFloat1(m_someFloat);
            setSomeInt(1);
            setSomeFloat3(0.0f);
            if (g_someOtherThreshold < (float)m_someOtherFloat) {
                setSomeFloat2(1.0f);
                return 1;
            }
        }
        break;

    default:
        result = baseClassHandler(unk1, unk2, unk3, stateId, unk4);
    }
    return result;
}