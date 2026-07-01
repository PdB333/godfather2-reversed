// FUNC_NAME: PlayerGroundSM::constructor
// Address: 0x0076b0f0
// Reconstructed constructor for PlayerGroundSM (state ID = 9)

#include <cstdint>

// Forward declarations
struct Actor;
extern void* g_vtable_PlayerGroundSM; // PTR_LAB_00d65f00
extern void BaseClass_constructor(void* arg1, void* arg2); // FUN_0073e160
extern void memoryManagerPush(uint32_t id);  // FUN_007f6420
extern void memoryManagerPushSub(uint32_t subId); // FUN_007f63e0
extern void memoryManagerPop(uint32_t id);   // FUN_007f63e0? Actually both push/pop

class PlayerGroundSM {
public:
    // Vtable pointer at +0x00
    // Base class at +0x00 (inherited)

    // Offsets from this:
    // +0x1c (0x70): uint32_t m_field70
    // +0x1d (0x74): uint32_t m_field74
    // +0x1e (0x78): uint32_t m_stateId
    // +0x1f (0x7c): uint32_t m_field7c
    // +0x20 (0x80): uint32_t m_flags
    // +0x5c (0x5c): Actor* m_actorPtr

    PlayerGroundSM* constructor(void* baseParam1, void* baseParam2) {
        // Base class initialization
        BaseClass_constructor(baseParam1, baseParam2);

        // Set vtable for this class
        this->vtable = &g_vtable_PlayerGroundSM;

        // Initialize state machine fields
        this->m_field70 = 0;
        this->m_field74 = 0;
        this->m_stateId = 9;   // Ground state ID
        this->m_field7c = 0;
        this->m_flags = 0;

        // Get actor pointer from this
        Actor* actor = (Actor*)this->m_actorPtr; // offset 0x5c

        // Memory profiling for actor field initialization
        memoryManagerPush(0x0e);
        memoryManagerPushSub(3);
        actor->field_833 = 0;  // offset 0x20cc from actor base
        memoryManagerPop(0x0c);

        // Check bit 6 of actor's flags at offset 0x4a4
        if ((actor->m_flags >> 6) & 1) {
            this->m_flags |= 1;
            // Call virtual function at offset 0x290 on actor
            // (**(code **)(*(int*)actor + 0x290))(0, 1);
            actor->vtable->someMethod(0, 1); // named for clarity
        }

        return this;
    }
};