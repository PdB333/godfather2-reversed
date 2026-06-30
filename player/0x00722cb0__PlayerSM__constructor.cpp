// FUNC_NAME: PlayerSM::constructor

// Forward declarations of callee functions (renamed from Ghidra names)
void baseEntityConstructor(PlayerSM* thisPtr);          // previously FUN_00722630
void allocateInternalData(PlayerSM* thisPtr, int size); // previously FUN_0043b960

class PlayerSM {
public:
    PlayerSM(uint8_t flags) {
        // Call base class constructor (likely from EARS engine hierarchy)
        baseEntityConstructor(this);
        // If flag bit 0 is set, allocate/initialize a 0x194-byte internal data block (e.g., state machine data)
        if (flags & 1) {
            allocateInternalData(this, 0x194); // +0x194 size member
        }
    }
};