// FUNC_NAME: PlayerCrewLeaderComponent::PlayerCrewLeaderComponent

// Constructor for PlayerCrewLeaderComponent (size ~0x310 bytes)
// Sets up vtable, base class, and initializes all member fields to default values.
// Called from FUN_006c59a0 (likely Player::Player or similar).

// Base class initialization
void FUN_006c9760(uint param_2, uint globalData);  // Some base class init (e.g., Component::Component)
void FUN_006c1360(void);                            // Another initialization (e.g., vtable fixup)

class PlayerCrewLeaderComponent {
public:
    // VTable pointers
    void **vfTable;          // +0x00: Primary vtable (PTR_FUN_00d5ef34)
    // +0x04: unknown / padding?
    void *someSecondaryPtr;  // +0x08: Secondary vtable or type info (PTR_LAB_00d5ef2c)

    // Crew leader state arrays (possibly triplets for each crew member slot)
    // Each group of 3*4 bytes = 12 bytes per member
    // +0x208 (0x82*4): ...
    uint32_t crewMember0[3];  // +0x208: [0x82,0x83,0x84]
    uint32_t crewMember1[3];  // +0x214: [0x85,0x86,0x87]
    uint32_t crewMember2[3];  // +0x220: [0x88,0x89,0x8a]
    uint32_t crewMember3[3];  // +0x22c: [0x8b,0x8c,0x8d]
    uint32_t crewMember4[3];  // +0x238: [0x8e,0x8f,0x90]
    uint32_t crewMember5[3];  // +0x244: [0x91,0x92,0x93]  // +0x91 set to 0 separately? Actually +0x91=0, then +0x92=0, +0x93=0 later but they are in pattern.
    uint32_t someFlag1;       // +0x254: [0x95] - 0
    uint32_t someFlag2;       // +0x250: [0x94] - 0
    // +0x258: [0x96]=0, [0x97]=0
    uint32_t crewMember6[2];  // +0x258: [0x96,0x97]?
    // +0x260: [0x98]=0, [0x99]=0
    uint32_t crewMember7[2];  // +0x260: [0x98,0x99]?
    // ... many more fields
    uint32_t field_0x9a;      // +0x268: [0x9a]=0
    uint32_t field_0x9b;      // +0x26c: [0x9b]=0
    uint8_t  byte_0x9c;       // +0x270: [0x9c] - byte 0
    uint32_t field_0x9d;      // +0x274: [0x9d]=0
    uint8_t  byte_0x9e;       // +0x278: [0x9e] - byte 0
    uint32_t field_0x9f;      // +0x27c: [0x9f]=0
    uint32_t field_0xa0;      // +0x280: [0xa0]=0
    uint32_t field_0xa1;      // +0x284: [0xa1]=0
    uint32_t field_0xa2;      // +0x288: [0xa2]=0
    uint32_t field_0xa3;      // +0x28c: [0xa3]=0
    uint32_t field_0xa4;      // +0x290: [0xa4]=0
    uint32_t field_0xa5;      // +0x294: [0xa5]=0
    uint32_t field_0xa6;      // +0x298: [0xa6]=0
    uint32_t field_0xa7;      // +0x29c: [0xa7]=0
    uint32_t field_0xa8;      // +0x2a0: [0xa8]=0
    uint32_t field_0xa9;      // +0x2a4: [0xa9]=0
    uint32_t field_0xaa;      // +0x2a8: [0xaa]=0
    uint32_t field_0xab;      // +0x2ac: [0xab]=0
    uint32_t field_0xac;      // +0x2b0: [0xac]=0
    uint32_t field_0xad;      // +0x2b4: [0xad]=0
    uint32_t field_0xae;      // +0x2b8: [0xae]=0
    uint8_t  byte_0xaf;       // +0x2bc: [0xaf] - byte 0
    uint32_t field_0xb0;      // +0x2c0: [0xb0]=0
    uint32_t field_0xb1;      // +0x2c4: [0xb1]=0
    uint32_t field_0xb2;      // +0x2c8: [0xb2]=0
    uint32_t field_0xb3;      // +0x2cc: [0xb3]=0
    uint32_t field_0xb4;      // +0x2d0: [0xb4]=0
    uint32_t field_0xb5;      // +0x2d4: [0xb5]=0
    uint32_t isActive;        // +0x2d8: [0xb6]=1 (initially active)
    uint32_t someTick;        // +0x2dc: [0xb7] = _DAT_00d5780c (global tick/seed)
    uint32_t field_0xb8;      // +0x2e0: [0xb8]=0
    uint32_t field_0xb9;      // +0x2e4: [0xb9]=0
    uint32_t field_0xba;      // +0x2e8: [0xba]=0
    uint32_t field_0xbb;      // +0x2ec: [0xbb]=0
    uint32_t field_0xbc;      // +0x2f0: [0xbc]=0
    uint32_t field_0xbd;      // +0x2f4: [0xbd]=0
    // Skip 0xbe? not set
    uint32_t field_0xbf;      // +0x2fc: [0xbf]=0
    uint32_t field_0xc0;      // +0x300: [0xc0]=0
    uint32_t field_0xc1;      // +0x304: [0xc1]=0
    uint8_t  byte_0xc2;       // +0x308: [0xc2] - byte 0
    uint32_t field_0xc3;      // +0x30c: [0xc3]=0

    explicit PlayerCrewLeaderComponent(uint param_2) {
        // Call base class constructor
        FUN_006c9760(param_2, _DAT_00d5cf70);  // Some base initialization
        // Set vtable pointers (probably from base class or derived)
        *reinterpret_cast<void ***>(this) = &PTR_FUN_00d5ef34;  // Primary vtable
        *reinterpret_cast<void **>(reinterpret_cast<char*>(this) + 8) = &PTR_LAB_00d5ef2c; // Secondary vtable/type

        // Call additional initialization (likely member function or vtable setup)
        FUN_006c1360();

        // Initialize crew member arrays (all zero)
        crewMember0[0] = 0; crewMember0[1] = 0; crewMember0[2] = 0;
        crewMember1[0] = 0; crewMember1[1] = 0; crewMember1[2] = 0;
        crewMember2[0] = 0; crewMember2[1] = 0; crewMember2[2] = 0;
        crewMember3[0] = 0; crewMember3[1] = 0; crewMember3[2] = 0;
        crewMember4[0] = 0; crewMember4[1] = 0; crewMember4[2] = 0;
        crewMember5[0] = 0; crewMember5[1] = 0; crewMember5[2] = 0;  // see offset ordering
        // Overlap: 0x91,0x92,0x93 also zeroed, but 0x91 set later? Actually all zeroed together.

        // Set single fields
        field_0x9a = 0;
        field_0x9b = 0;
        byte_0x9c = 0;
        field_0x9d = 0;
        byte_0x9e = 0;
        field_0x9f = 0;
        field_0xa0 = 0;
        // ... all other fields as per decompile

        // Active flag set to 1
        isActive = 1;
        // Store a global timestamp/seed
        someTick = _DAT_00d5780c;

        // Remaining zeroed fields
        field_0x92 = 0;  // actually crewMember5[1] already zeroed, but it's explicitly set again
        field_0x98 = 0;
        field_0x99 = 0;
        field_0xad = 0;
        field_0xae = 0;
        field_0xb0 = 0;
        field_0xb1 = 0;
        field_0xb3 = 0;
        field_0xb4 = 0;
        field_0xb5 = 0;
        field_0xb8 = 0;
        field_0xb9 = 0;
        field_0xba = 0;
        field_0xbb = 0;
        field_0xbc = 0;
        field_0xbd = 0;
        field_0x95 = 0;
        field_0x94 = 0;
        field_0x93 = 0;
        field_0xc1 = 0;
        field_0xc0 = 0;
        field_0xbf = 0;
        byte_0xc2 = 0;
        field_0xc3 = 0;
    }
};