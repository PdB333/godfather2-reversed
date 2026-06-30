// FUNC_NAME: EARSObject::EARSObject

// Reconstructed constructor for EARSObject (EA EARS engine base object)
// Address: 0x0047d5f0
// Initializes magic signatures and various flags, calls base constructor

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

// External vtable pointers (defined in .rdata)
extern void* const VTABLE_BASE;      // 0x00e33260
extern void* const VTABLE_DERIVED;    // 0x00e3321c
extern void* const VTABLE_SOMETHING;  // 0x00e33230
extern void* const PTR_LAB_00e3324c;
extern void* const PTR_LAB_00e3325c;

// External functions (from other translation units)
extern void __thiscall FUN_0046c590(uint someArg);  // base constructor
extern void __thiscall FUN_00407e60(void* ptr, void* globalData); // registration

// Global pointer to this object
extern EARSObject* g_globalObject; // _DAT_0122340c
extern void* DAT_012069f4; // global manager pointer

// class EARSObject
class EARSObject {
public:
    // Offsets relative to this pointer (in bytes)
    void* vtable;                         // +0x00
    void* someOtherVtable;                // +0x04   (param_1[1])
    void* ptrAt0x40;                      // +0x40   (param_1[0x10])
    void* ptrAt0x4C;                      // +0x4C   (param_1[0x13])
    uint field_0x54;                      // +0x54   (param_1[0x15])
    ushort field_0x58;                    // +0x58   (*(uint16*)(this+0x58))
    ushort field_0x5A;                    // +0x5A   (*(uint16*)(this+0x5A))
    uint field_0x5C;                      // +0x5C   (param_1[0x17])
    ushort field_0x60;                    // +0x60   (*(uint16*)(this+0x60))
    ushort field_0x62;                    // +0x62   (*(uint16*)(this+0x62))
    uint field_0x64;                      // +0x64   (param_1[0x19])
    ushort field_0x68;                    // +0x68   (*(uint16*)(this+0x68))
    ushort field_0x6A;                    // +0x6A   (*(uint16*)(this+0x6A))
    uint debugSig1;                       // +0x6C   (0xbadbadba) (param_1[0x1b])
    uint debugSig2;                       // +0x70   (0xbeefbeef) (param_1[0x1c])
    uint debugSig3;                       // +0x74   (0xeac15a55) (param_1[0x1d])
    uint debugSig4;                       // +0x78   (0x91100911) (param_1[0x1e])
    uint field_0x7C;                      // +0x7C   (param_1[0x1f])
    uint field_0x80;                      // +0x80   (param_1[0x20])
    uint field_0x84;                      // +0x84   (param_1[0x21])
    byte flag1;                           // +0x88   (*(uint8*)(this+0x88))  set to 1
    uint field_0x8C;                      // +0x8C   (param_1[0x23])
    byte flag2;                           // +0x90   (*(uint8*)(this+0x90))  set to 1
    uint field_0x94;                      // +0x94   (param_1[0x25])
    uint field_0x98;                      // +0x98   (param_1[0x26])
    uint field_0x9C;                      // +0x9C   (param_1[0x27])
    uint field_0xA0;                      // +0xA0   (param_1[0x28])

    // Constructor
    EARSObject(uint someArg)
    {
        // Set base class vtable (temporarily)
        this->vtable = &VTABLE_BASE;

        // Store a global reference to this object
        g_globalObject = this;

        // Call base constructor (may use temporary vtable)
        FUN_0046c590(someArg);

        // Override with derived class vtable
        this->vtable = &VTABLE_DERIVED;

        // Additional vtable pointers
        this->someOtherVtable = &VTABLE_SOMETHING;
        this->ptrAt0x40 = &PTR_LAB_00e3324c;
        this->ptrAt0x4C = &PTR_LAB_00e3325c;

        // Zero-initialize a block of fields (0x54 – 0x6A)
        this->field_0x54 = 0;
        this->field_0x58 = 0;
        this->field_0x5A = 0;
        this->field_0x5C = 0;
        this->field_0x60 = 0;
        this->field_0x62 = 0;
        this->field_0x64 = 0;
        this->field_0x68 = 0;
        this->field_0x6A = 0;

        // Set debug signatures for object identification
        this->debugSig1 = 0xbadbadba;
        this->debugSig2 = 0xbeefbeef;
        this->debugSig3 = 0xeac15a55;
        this->debugSig4 = 0x91100911;

        // Zero-initialize following fields
        this->field_0x7C = 0;
        this->field_0x80 = 0;
        this->field_0x84 = 0;

        // Set flags
        this->flag1 = 1;   // +0x88
        this->field_0x8C = 0;
        this->flag2 = 1;   // +0x90
        this->field_0x94 = 0;
        this->field_0x98 = 0;
        this->field_0x9C = 0;
        this->field_0xA0 = 0;

        // If a global manager exists, register this object's internal pointer
        if (DAT_012069f4 != 0) {
            FUN_00407e60(&this->ptrAt0x40, &DAT_012069f4);
        }
    }
};