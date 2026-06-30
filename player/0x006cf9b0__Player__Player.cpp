// FUNC_NAME: Player::Player
// Reconstructed constructor for Player class at 0x006cf9b0
// The class uses multiple inheritance with vtable pointers at +0x00, +0x3C, +0x48, +0x50.
// The constant 0xFE16702F at offsets +0xCC and +0xD4 appears to be a type identifier.

class Player {
public:
    // Vtable for primary class (Player)
    void* vtable;                               // +0x00

    // Possibly base class data until +0x3C (15*4)
    // Unknown fields between +0x04 and +0x3B

    // Secondary vtable pointers (for multiple inheritance)
    void* base2_vtable;                         // +0x3C (param_1[0xf])
    void* base3_vtable;                         // +0x48 (param_1[0x12])
    void* interface_vtable;                     // +0x50 (param_1[0x14])

    // Fields from +0x54 to +0xB3 (not initialized here)
    // Possibly alignment or other base class data

    // Fields zeroed by this constructor
    uint32_t field_0xB4;                        // +0xB4 (param_1[0x2d])
    uint16_t field_0xB8;                        // +0xB8 (halfword)
    uint16_t field_0xBA;                        // +0xBA (halfword)
    uint32_t field_0xBC;                        // +0xBC (param_1[0x2f])
    uint16_t field_0xC0;                        // +0xC0 (halfword)
    uint16_t field_0xC2;                        // +0xC2 (halfword)
    uint32_t field_0xC8;                        // +0xC8 (param_1[0x32])
    uint32_t typeID_0xCC;                      // +0xCC (param_1[0x33]) set to 0xFE16702F
    uint32_t field_0xD0;                        // +0xD0 (param_1[0x34]) zeroed
    uint32_t typeID_0xD4;                       // +0xD4 (param_1[0x35]) set to 0xFE16702F

    // Constructor
    Player() {
        // Base class constructor (likely for Sentient or Entity)
        BaseClassConstructor();                 // FUN_004737b0

        // Set primary vtable
        this->vtable = &Player_vtable;          // PTR_FUN_00d5f228

        // Set secondary vtable pointers (multiple inheritance)
        this->base2_vtable = &Base2_vtable;     // PTR_LAB_00d5f214
        this->base3_vtable = &Base3_vtable;     // PTR_LAB_00d5f210
        this->interface_vtable = &Interface_vtable; // PTR_LAB_00d5f20c

        // Common initialization (clears flags, registers, etc.)
        CommonInit();                           // FUN_00473750

        // Zero out specific fields
        this->field_0xB4 = 0;
        this->field_0xB8 = 0;
        this->field_0xBA = 0;
        this->field_0xBC = 0;
        this->field_0xC0 = 0;
        this->field_0xC2 = 0;
        this->field_0xC8 = 0;

        // Set type identification magic values
        this->typeID_0xCC = 0xFE16702F;
        this->field_0xD0 = 0;
        this->typeID_0xD4 = 0xFE16702F;

        // Player-specific initialization
        PlayerSpecificInit();                   // FUN_006cf1a0

        // Additional common initialization (possibly redundant)
        CommonInit();                           // FUN_00473750
    }
};