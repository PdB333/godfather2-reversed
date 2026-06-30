// FUNC_NAME: GameConfigManager::GameConfigManager

#include <cstdint>

// Forward declarations

class GameConfigManagerBase {
public:
    // Constructor called with an argument
    GameConfigManagerBase(uint32_t arg);
};

// Global data references (addresses from Ghidra)
extern uint32_t g_vtable_00d5f610;          // Main vtable pointer
extern uint32_t g_vtable_00d5f600;          // Secondary vtable at +0x3C (0xF * 4)
extern uint32_t g_vtable_00d5f5fc;          // Tertiary vtable at +0x48 (0x12 * 4)
extern uint32_t g_vtable_00d5f5f8;          // Quaternary vtable at +0x50 (0x14 * 4)
extern uint32_t g_configFieldA;             // DAT_00d5e288
extern uint32_t g_configFieldB;             // DAT_00d5efd0
extern uint32_t g_configFieldC;             // _DAT_00d5780c
extern uint32_t g_configFieldD;             // DAT_00e446dc
extern uint32_t g_vtable_00d5f5f0;          // At +0x54 (0x15 * 4)
extern uint32_t g_vtable_00d5f5f4;          // At +0x58 (0x16 * 4)

class GameConfigManager : public GameConfigManagerBase {
public:
    // Offset: +0x00 - Main vtable pointer (points to PTR_FUN_00d5f610)
    // Offset: +0x3C - Secondary vtable pointer (PTR_LAB_00d5f600)
    // Offset: +0x48 - Tertiary vtable pointer (PTR_LAB_00d5f5fc)
    // Offset: +0x50 - Quaternary vtable pointer (PTR_LAB_00d5f5f8)
    // Offset: +0x54 - Some global pointer (DAT_00d5f5f0)
    // Offset: +0x58 - Another global pointer (DAT_00d5f5f4)
    // Offset: +0x94 - First configuration field (0x25 * 4 = 0x94)
    // Offset: +0x98 - Second configuration field (0x26 * 4 = 0x98)
    // Offset: +0x9C - Third configuration field (0x27 * 4 = 0x9C)
    // Offset: +0xA0 - Fourth configuration field (0x28 * 4 = 0xA0)
    // Offset: +0xA4 - Fifth configuration field (0x29 * 4 = 0xA4)
    // Offset: +0xA8 - Sixth configuration field (0x2A * 4 = 0xA8)
    // Offset: +0xAC - Seventh configuration field (0x2B * 4 = 0xAC)
    // Offset: +0xB0 - Eighth configuration field (0x2C * 4 = 0xB0)
    // Offset: +0xB4 - Ninth configuration field (0x2D * 4 = 0xB4)

    GameConfigManager(uint32_t arg) : GameConfigManagerBase(arg) {
        // Set the vtable pointers to the class's own vtables
        this->vtableMain = &g_vtable_00d5f610;
        this->vtableSecondary = &g_vtable_00d5f600;
        this->vtableTertiary = &g_vtable_00d5f5fc;
        this->vtableQuaternary = &g_vtable_00d5f5f8;

        // Copy configuration data from globals
        this->configField1 = g_configFieldA;   // +0x94
        this->configField2 = g_configFieldB;   // +0x98
        this->configField3 = g_configFieldA;   // +0x9C
        this->configField4 = g_configFieldB;   // +0xA0

        // More configuration fields
        this->configField5 = g_configFieldC;   // +0xA4
        this->configField6 = g_configFieldA;   // +0xA8 (note: sources swap)
        this->configField7 = g_configFieldD;   // +0xAC
        this->configField8 = g_configFieldC;   // +0xB0
        this->configField9 = g_configFieldC;   // +0xB4

        // Additional vtable-like pointers
        this->vtableExtra1 = &g_vtable_00d5f5f0; // +0x54
        this->vtableExtra2 = &g_vtable_00d5f5f4; // +0x58
    }

private:
    // Member variables (offsets relative to 'this')
    uint32_t* vtableMain;            // +0x00
    uint32_t* vtableSecondary;       // +0x3C
    uint32_t* vtableTertiary;        // +0x48
    uint32_t* vtableQuaternary;      // +0x50
    uint32_t* vtableExtra1;          // +0x54
    uint32_t* vtableExtra2;          // +0x58
    uint32_t configField1;           // +0x94
    uint32_t configField2;           // +0x98
    uint32_t configField3;           // +0x9C
    uint32_t configField4;           // +0xA0
    uint32_t configField5;           // +0xA4
    uint32_t configField6;           // +0xA8
    uint32_t configField7;           // +0xAC
    uint32_t configField8;           // +0xB0
    uint32_t configField9;           // +0xB4
};

// Function implementation (address 0x006da660)
// This __thiscall constructor initializes a GameConfigManager object.
// The base class constructor (FUN_00473d90) is called first with the given argument.
uint32_t* __thiscall GameConfigManager_constructor(uint32_t* thisPtr, uint32_t arg) {
    // Call base class constructor (likely GameConfigManagerBase at address 0x00473d90)
    FUN_00473d90(arg);

    // Set vtable pointers
    thisPtr[0] = (uint32_t)&g_vtable_00d5f610;         // +0x00
    thisPtr[0xF] = (uint32_t)&g_vtable_00d5f600;      // +0x3C
    thisPtr[0x12] = (uint32_t)&g_vtable_00d5f5fc;     // +0x48
    thisPtr[0x14] = (uint32_t)&g_vtable_00d5f5f8;     // +0x50

    // Set configuration fields from globals
    thisPtr[0x25] = g_configFieldA;   // +0x94
    thisPtr[0x26] = g_configFieldB;   // +0x98
    thisPtr[0x27] = g_configFieldA;   // +0x9C
    thisPtr[0x28] = g_configFieldB;   // +0xA0

    thisPtr[0x29] = g_configFieldC;   // +0xA4
    thisPtr[0x2A] = g_configFieldA;   // +0xA8
    thisPtr[0x2B] = g_configFieldD;   // +0xAC
    thisPtr[0x2C] = g_configFieldC;   // +0xB0
    thisPtr[0x2D] = g_configFieldC;   // +0xB4

    // Set additional vtable pointers
    thisPtr[0x15] = (uint32_t)&g_vtable_00d5f5f0;     // +0x54
    thisPtr[0x16] = (uint32_t)&g_vtable_00d5f5f4;     // +0x58

    return thisPtr;
}