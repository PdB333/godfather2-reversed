// FUNC_NAME: Sentient::getCurrentActionState
// Function address: 0x007347e0
// This function determines the current action state of a sentient entity based on various flags and global game state.
// Results are stored at +0x2184 as a state code (magic constants).

enum ActionState : uint32_t {
    kActionState_Default = 0x2ca3cff6,
    kActionState_Occupied = 0xec284f6a,
    kActionState_StateA = 0x1193fb8b,
    kActionState_StateB = 0xf1cd124a,
    kActionState_StateC = 0x5485e39,
    kActionState_StateD = 0x90e62591
};

class Sentient {
public:
    // +0x1e70: some pointer (e.g., vehicle or interactive object)
    uint32_t* m_occupiedObject;  // +0x1e70
    // +0x2184: current action state
    uint32_t m_actionState;      // +0x2184
    // +0x8e0: flags, bit1 used
    struct Flags {
        uint32_t bit0 : 1;
        uint32_t bit1 : 1; // 0x2 -> isSomething
        // ...
    } m_flags; // +0x8e0

    // Callees
    friend bool isObjectValid(uint32_t* ptr); // FUN_0045eec0
    friend int getGameManager();              // FUN_0043b870 (with DAT_01131040)
    friend int getGlobalGameState();          // FUN_00800b60
    friend int getGameMode();                 // FUN_0077dd80
    friend bool isSpecialModeActive();        // FUN_006eb940
    friend uint32_t getSecondaryState();      // FUN_0072fad0
};

uint32_t __fastcall Sentient::getCurrentActionState(Sentient* this) {
    // If the stored state pointer is null or invalid, reset to default
    if (this->m_occupiedObject == 0 || !isObjectValid(this->m_occupiedObject)) {
        this->m_actionState = kActionState_Default;

        int managerResult = getGameManager();
        int globalState = getGlobalGameState();

        // If vehicle/inventory is present, indicate occupied state
        if (this->m_occupiedObject != 0) {
            this->m_actionState = kActionState_Occupied;
            return this->m_actionState;
        }

        // Check flag bit 1
        if (!(this->m_flags.bit1)) {
            int mode = getGameMode();
            if (mode != 3) {
                if (managerResult != 0 && isSpecialModeActive()) {
                    uint32_t secondary = getSecondaryState();
                    this->m_actionState = secondary;
                    return secondary;
                }

                switch (globalState) {
                case 0:
                case 1:
                    goto case10;
                case 2:
                case 3:
                case 4:
                    goto case24;
                default:
                    goto defaultCase;
                }
            }
            // mode == 3
            switch (globalState) {
            case10:
            case 0:
                this->m_actionState = kActionState_Default;
                return this->m_actionState;
            case 1:
                this->m_actionState = kActionState_StateA;
                return this->m_actionState;
            case 2:
            case 3:
            case 4:
            case24:
                this->m_actionState = kActionState_StateB;
                break;
            }
        } else {
            // flag bit1 is set
            switch (globalState) {
            case 0:
            case 1:
                this->m_actionState = kActionState_StateC;
                return this->m_actionState;
            case 2:
            case 3:
            case 4:
                this->m_actionState = kActionState_StateD;
                return this->m_actionState;
            }
        }
    }

defaultCase:
    return this->m_actionState;
}