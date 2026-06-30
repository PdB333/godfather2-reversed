// FUNC_NAME: Player::Player
// Function address: 0x0074d3b0
// Constructor for the Player class (Godfather 2 EARS engine).
// Initializes multiple vtable pointers, reads an owner-related value, and sets up input manager.

class Player : public BaseClass { // BaseClass constructor called as FUN_0080e6a0
public:
    // __thiscall, this in ecx
    Player(BaseClass* parentObject, uint32_t flags) : BaseClass(parentObject, flags) {
        // Set vtable pointers for this derived class (overwrites base vtable at offset 0)
        // +0x00: main vtable
        *reinterpret_cast<void**>(this) = &PTR_LAB_00d6473c;
        // +0x58: secondary vtable (interface?)
        reinterpret_cast<void**>(this)[0x16] = &PTR_FUN_00d64738;
        // +0x5C: tertiary vtable
        reinterpret_cast<void**>(this)[0x17] = &PTR_LAB_00d64734;

        // Zero-initialize fields from +0x60 to +0x80 (8 dwords)
        for (int i = 0x18; i <= 0x20; ++i) {
            reinterpret_cast<uint32_t*>(this)[i] = 0;
        }

        // +0x48: m_pOwner (pointer to owning object)
        // Compute relative offset from owner if valid (used for multiple inheritance adjustment)
        // +0x88: m_ownerOffset
        if (m_pOwner != nullptr) {
            m_ownerOffset = reinterpret_cast<uint8_t*>(m_pOwner) - 0x48;
        } else {
            m_ownerOffset = 0;
        }

        // Zero-initialize fields from +0x8C to +0xB0 (10 dwords)
        for (int i = 0x23; i <= 0x2C; ++i) {
            reinterpret_cast<uint32_t*>(this)[i] = 0;
        }

        // +0x88: m_ownerOffset points to a structure, read at +0x5C4 (e.g., a manager pointer)
        // +0xD4: m_someValue (stored for later use)
        m_someValue = *reinterpret_cast<uint32_t*>(m_ownerOffset + 0x5C4);

        // +0xB4: another vtable pointer
        reinterpret_cast<void**>(this)[0x2D] = &PTR_FUN_00d64720;
        // +0xB8, +0xBC: zero
        reinterpret_cast<uint32_t*>(this)[0x2E] = 0;
        reinterpret_cast<uint32_t*>(this)[0x2F] = 0;
        // +0xC0: byte (set to 0)
        *reinterpret_cast<uint8_t*>(this + 0x30) = 0;
        // +0xC4, +0xC8, +0xCC: zero
        reinterpret_cast<uint32_t*>(this)[0x31] = 0;
        reinterpret_cast<uint32_t*>(this)[0x32] = 0;
        reinterpret_cast<uint32_t*>(this)[0x33] = 0;
        // +0xD0: short (0xC000 = flag combination)
        *reinterpret_cast<uint16_t*>(this + 0x34) = 0xC000;
        // +0xD4: already set
        // +0xD8, +0xDC, +0xE0: zero
        reinterpret_cast<uint32_t*>(this)[0x36] = 0;
        reinterpret_cast<uint32_t*>(this)[0x37] = 0;
        reinterpret_cast<uint32_t*>(this)[0x38] = 0;
        // +0xE4: flags (initially 1)
        reinterpret_cast<uint32_t*>(this)[0x39] = 1;
        // +0x84: previously zero (initialized earlier)
        reinterpret_cast<uint32_t*>(this)[0x21] = 0;

        // +0xF4: m_pInputManager – obtained from global game manager (DAT_01131018) if owner is valid
        if (m_ownerOffset != 0) {
            m_pInputManager = FUN_0043b870(*reinterpret_cast<void**>(0x01131018));
        } else {
            m_pInputManager = 0;
        }

        // Debug/initialization call (mark memory of size 0x34)
        FUN_007f63e0(0x34);

        // Add flag 0x100 to +0xE4
        reinterpret_cast<uint32_t*>(this)[0x39] |= 0x100;
    }

private:
    // Structure fields (offsets in dwords):
    // +0x48 (0x12): m_pOwner
    void* m_pOwner;
    // +0x88 (0x22): m_ownerOffset
    uint8_t* m_ownerOffset;
    // +0xD4 (0x35): m_someValue (read from owner at +0x5C4)
    uint32_t m_someValue;
    // +0xF4 (0x3D): m_pInputManager
    void* m_pInputManager;
    // ... other fields omitted for brevity
};

// External references (from Ghidra symbols):
// PTR_LAB_00d6473c, PTR_FUN_00d64738, PTR_LAB_00d64734, PTR_FUN_00d64720 – vtable addresses
// DAT_01131018 – global game manager pointer
// FUN_0043b870 – function to retrieve input manager from game manager
// FUN_007f63e0 – debug marking function (size parameter)