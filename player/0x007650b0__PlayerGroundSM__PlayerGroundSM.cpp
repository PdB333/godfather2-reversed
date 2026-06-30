// FUNC_NAME: PlayerGroundSM::PlayerGroundSM
// Function address: 0x007650b0
// Constructor for PlayerGroundSM (player ground state machine subclass)
// Initializes base state machine (FUN_004ac120), sets up vtable and function pointers,
// and adjusts internal pointers derived from an embedded object at offset 0x48.

class PlayerGroundSM : public StateMachine {  // base likely StateMachine or PlayerSM
public:
    void* __thiscall PlayerGroundSM(void* param_2, void* param_3) {
        // Call base constructor (FUN_004ac120) – likely StateMachine::StateMachine
        reinterpret_cast<void(__thiscall*)(void*,void*,void*)>(0x004ac120)(this, param_2, param_3);

        // Set vtable pointer
        *(void***)this = &PTR_LAB_00d65684;

        // Offset 0x48 (index 0x12): pointer to embedded sibling object
        // If non-null, subtract 0x48 to get container base (container_of pattern)
        int* arr = reinterpret_cast<int*>(this);
        int containerBase;
        if (arr[0x12] == 0) {
            containerBase = 0;
        } else {
            containerBase = arr[0x12] - 0x48;   // +0x48 offset -> container base
        }

        // +0x50 (index 0x14): stored container base
        arr[0x14] = containerBase;

        // +0x54 (index 0x15): global flag/value
        arr[0x15] = DAT_00d65680;

        // Zero out various state members
        arr[0x19] = 0;   // +0x64
        arr[0x1A] = 0;   // +0x68
        arr[0x1B] = 0;   // +0x6C
        arr[0x1C] = 0;   // +0x70
        arr[0x21] = 0;   // +0x84
        arr[0x24] = 0;   // +0x90

        // +0x9C (index 0x27): function pointer (probably update/execute callback)
        arr[0x27] = reinterpret_cast<int>(&LAB_007648e0);

        // +0x88 (index 0x22): copy of container base (mirrors +0x50)
        arr[0x22] = arr[0x14];

        // +0x8C (index 0x23): function pointer (probably another callback)
        arr[0x23] = reinterpret_cast<int>(FUN_0072f960);

        // +0xA0 (index 0x28): null
        arr[0x28] = 0;

        // +0xB4 (index 0x2D): null
        arr[0x2D] = 0;

        // +0xB8 (index 0x2E): invalid sentinel (-1)
        arr[0x2E] = 0xFFFFFFFF;

        // Clear additional state fields at +0x60, +0x5C, +0x58
        arr[0x18] = 0;
        arr[0x17] = 0;
        arr[0x16] = 0;

        return this;
    }
};