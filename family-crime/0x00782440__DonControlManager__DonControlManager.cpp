// FUNC_NAME: DonControlManager::DonControlManager
// Address: 0x00782440
// Role: Constructor for DonControlManager (EA EARS component used in Godfather 2)
//       Initializes member variables with default values from global data.
//       Assumes a base class constructor is called first.

// ----------------------------------------------------------------------
// Global data (from the game's data segment)
extern uint32_t g_defaultDonControlValue;   // _DAT_00d5c458 - base don control param
extern uint32_t g_defaultFloat1;            // DAT_00d5f53c
extern uint32_t g_defaultFloat2;            // DAT_00d5efa4
extern uint32_t g_defaultZeroOrOne;         // DAT_00d5e288 - used as default for many fields

// Vtable pointers (function tables)
extern void* g_vtable_DonControlManager;    // PTR_FUN_00d69654
extern void* g_secondVtable;                // PTR_LAB_00d69644
extern void* g_thirdVtable;                 // PTR_LAB_00d69640

// Forward declaration of base class constructor (likely Entity or EARSObject)
// void __thiscall BaseClass::constructor(uint32_t someParam); // FUN_0046c590

// ----------------------------------------------------------------------
class DonControlManager {
public:
    // Known vtable pointer at +0x00
    void** vtable;

    // Offsets deduced from initialization:
    // +0x3C (0x0F) - second vtable pointer
    // +0x48 (0x12) - third vtable pointer
    // +0x50 (0x14) - field_14 (int, set to 0)
    // +0x54 (0x15) - field_15 (from g_defaultFloat1)
    // +0x58 (0x16) - field_16 (from g_defaultFloat2)
    // +0x5C (0x17) - field_17 (from g_defaultZeroOrOne)
    // +0x60 (0x18) - field_18 (set to 0)
    // +0x64 (0x19) - field_19 (set to 0)
    // +0x68 (0x1A) - field_1A (set to 0)
    // +0x6C (0x1B) - field_1B (set to 0)
    // +0x70 (0x1C) - field_1C (from g_defaultDonControlValue)
    // +0x74 (0x1D) - field_1D (set to 0)
    // +0x78 (0x1E) - field_1E (from g_defaultZeroOrOne)
    // +0x7C (0x1F) - field_1F (set to 0)
    // +0x80 (0x20) - field_20 (from g_defaultZeroOrOne)
    // +0x84 (0x21) - field_21 (set to 0)
    // +0x88 (0x22) - field_22 (from g_defaultZeroOrOne)
    // +0x8C (0x23) - field_23 (set to 0)
    // +0x90 (0x24) - field_24 (from g_defaultZeroOrOne)

    // Constructor
    __thiscall DonControlManager(uint32_t someParam);
};

// ----------------------------------------------------------------------
DonControlManager* __thiscall DonControlManager::DonControlManager(uint32_t someParam)
{
    // Base class initialisation (FUN_0046c590)
    BaseClass::constructor(someParam);

    uint32_t temp = g_defaultDonControlValue;

    // Set up vtable and secondary function pointers
    this->vtable = &g_vtable_DonControlManager;          // +0x00
    this->secondVtable = &g_secondVtable;                 // +0x3C (0x0F)
    this->thirdVtable = &g_thirdVtable;                   // +0x48 (0x12)

    // Clear a block of four fields
    this->field_0x18 = 0;    // +0x60
    this->field_0x19 = 0;    // +0x64
    this->field_0x1A = 0;    // +0x68
    this->field_0x1B = 0;    // +0x6C

    // Main don control value from global
    this->field_0x1C = temp; // +0x70

    // Other configurable parameters
    this->field_0x15 = g_defaultFloat1;    // +0x54
    this->field_0x16 = g_defaultFloat2;    // +0x58

    // field at 0x14 is zeroed
    this->field_0x14 = 0;                  // +0x50

    // field at 0x17 gets the default "zero or one" value
    this->field_0x17 = g_defaultZeroOrOne; // +0x5C

    // Several fields that appear to be part of a repeating pattern (likely float or int arrays)
    // 0x1D, 0x1F, 0x21, 0x23 are zeroed
    this->field_0x1D = 0;                  // +0x74
    this->field_0x1F = 0;                  // +0x7C
    this->field_0x21 = 0;                  // +0x84
    this->field_0x23 = 0;                  // +0x8C

    // 0x1E, 0x20, 0x22, 0x24 are set to the default "zero or one"
    this->field_0x1E = g_defaultZeroOrOne; // +0x78
    this->field_0x20 = g_defaultZeroOrOne; // +0x80
    this->field_0x22 = g_defaultZeroOrOne; // +0x88
    this->field_0x24 = g_defaultZeroOrOne; // +0x90

    return this;
}