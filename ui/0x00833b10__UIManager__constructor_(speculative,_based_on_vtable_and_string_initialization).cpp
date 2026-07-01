// FUNC_NAME: UIManager::constructor (speculative, based on vtable and string initialization)
// Function address: 0x00833b10
// Role: Constructor for a manager class (likely UI-related) that initializes vtable, copies matrix data, and sets up string fields based on a global flag.

#include <cstdint>

// Forward declarations for called functions (assumed to be part of the engine)
void __cdecl baseConstructor(uint32_t param); // FUN_0046c590
void __cdecl staticInit(); // FUN_008338f0
uint32_t* __cdecl getMatrixData(); // FUN_0043ab10 - returns pointer to 4 dwords (e.g., identity matrix)
void __cdecl secondaryInit(uint32_t param); // FUN_00833760
void __cdecl specialInit(void* thisPtr); // FUN_008356d0
void __cdecl stringCopy(char* dest, const char* src); // FUN_004089b0 - copies string, uses default if src is null

// Global flag (likely indicates whether the manager should be initialized in a special mode)
extern uint32_t g_useSpecialInit; // DAT_0112db84

// Default string used when source pointer is null
extern const char g_defaultString; // DAT_0120546e (single byte? but used as string)

// Class definition (partial, based on offsets observed in decompilation)
struct UIManager {
    // vtable pointer at +0x00
    void** vtable;
    // ... other fields ...
    // Offset 0x3C (index 0xF): some function pointer table
    void** field_0x3C;
    // Offset 0x48 (index 0x12): another function pointer table
    void** field_0x48;
    // Offset 0x88 (index 0x22): matrix data (4 dwords)
    uint32_t matrix[4];
    // Offset 0x9C (index 0x27): state flag (0 or 1)
    uint32_t stateFlag;
    // Offset 0xA0 (index 0x28): source string pointer 1
    const char* sourceString1;
    // Offset 0xB0 (index 0x2C): source string pointer 2
    const char* sourceString2;
    // Offset 0xC8 (index 0x32): special init flag
    uint32_t specialInitFlag;
    // Offset 0xCC (index 0x33): destination string buffer 1 (size 8 bytes? based on two shorts)
    char destString1[8];
    // Offset 0xD4 (index 0x35): destination string buffer 2 (size 8 bytes)
    char destString2[8];
};

// Constructor implementation
UIManager* __thiscall UIManager_constructor(UIManager* this, uint32_t param2) {
    // Call base class constructor (likely sets up initial vtable or other base data)
    baseConstructor(param2);

    // Set vtable pointer
    this->vtable = (void**)0x00d73abc;

    // Set additional function pointer tables (possibly for derived behavior)
    this->field_0x3C = (void**)0x00d73aac;
    this->field_0x48 = (void**)0x00d73aa8;

    // Call static initialization (e.g., register class, load resources)
    staticInit();

    // Initialize state flag to 0
    this->stateFlag = 0;

    // Clear destination string buffers (two shorts each, total 4 bytes per buffer? Actually two shorts = 4 bytes, but offset suggests 8 bytes total for each? The decompiled shows two shorts at +0xD0 and +0xD2, and another two at +0xD8 and +0xDA, so each buffer is 4 bytes? But index 0x33 is offset 0xCC, and then two shorts at +0xD0 and +0xD2, so buffer1 is 8 bytes? Let's just zero the 8-byte region)
    *(uint16_t*)(this->destString1) = 0;
    *(uint16_t*)(this->destString1 + 2) = 0;
    *(uint16_t*)(this->destString1 + 4) = 0;
    *(uint16_t*)(this->destString1 + 6) = 0;

    // Clear second buffer (offset 0xD4 = index 0x35)
    *(uint16_t*)(this->destString2) = 0;
    *(uint16_t*)(this->destString2 + 2) = 0;
    *(uint16_t*)(this->destString2 + 4) = 0;
    *(uint16_t*)(this->destString2 + 6) = 0;

    // Copy matrix data from global source (e.g., identity matrix)
    uint32_t* matrixData = getMatrixData();
    this->matrix[0] = matrixData[0];
    this->matrix[1] = matrixData[1];
    this->matrix[2] = matrixData[2];
    this->matrix[3] = matrixData[3];

    // Call secondary initialization (e.g., set up additional resources)
    secondaryInit(param2);

    // Check global flag and state to decide initialization path
    if (g_useSpecialInit != 0 && this->stateFlag == 0) {
        // Special initialization path (e.g., load from save data)
        specialInit(this);
        this->specialInitFlag = 1;
        return this;
    }

    // If stateFlag is 1, copy strings from source pointers (or use default)
    if (this->stateFlag == 1) {
        const char* src1 = this->sourceString1;
        if (src1 == nullptr) {
            src1 = &g_defaultString; // Default string (likely empty or placeholder)
        }
        stringCopy(this->destString1, src1);

        const char* src2 = this->sourceString2;
        if (src2 == nullptr) {
            src2 = &g_defaultString;
        }
        stringCopy(this->destString2, src2);
    }

    return this;
}