// FUN_00495dd0: EARS::TextDisplay::TextDisplay

// Reconstructed constructor for a UI text display element (EA EARS engine)
// Sets up vtable, base object, and default color/text states.

#include <cstdint>

// Forward declarations for global data (symbols from binary)
extern void* PTR_LAB_00e34f9c;            // VTable for TextDisplay class
extern uint32_t DAT_00e44790;             // Default text color (normal)
extern uint32_t DAT_00e2b1a4;             // Default text color (hover)

// Forward declarations for helper functions
void __thiscall FUN_00495b20(void* baseObj);   // Base object constructor
void __thiscall FUN_00495ee0(void* baseObj);   // Base object finalizer

class EARS::TextDisplay {
public:
    void* vtable;                               // +0x00

    // Base sub-object at offset 0x04 (0x114 bytes)
    struct {
        uint32_t field_00;                      // +0x00 (relative to base)
        uint16_t field_04;                      // +0x04
        // ... further base fields up to offset 0x114
        // Actual layout determined by base class
    } baseObject;                                // +0x04 (size 0x114)

    // Fields directly in TextDisplay
    uint32_t textColorNormal;                   // +0x118 (from DAT_00e44790)
    uint32_t textColorPressed;                  // +0x11C (set to 0xffff00)
    uint32_t textColorHover;                    // +0x120 (from DAT_00e2b1a4)
    uint32_t someFlag;                          // +0x124 (cleared)
    uint8_t  byteAt0x128;                       // +0x128 (cleared)
    uint8_t  byteAt0x129;                       // +0x129 (cleared)
    uint32_t someOther;                         // +0x12C (cleared)
    // Object size >= 0x130 bytes
};

void __thiscall EARS::TextDisplay::TextDisplay(EARS::TextDisplay* this) {
    // Store vtable pointer
    this->vtable = &PTR_LAB_00e34f9c;

    // Initialize base sub-object header
    this->baseObject.field_00 = 0;
    this->baseObject.field_04 = 3;

    // Call base object constructor
    FUN_00495b20(&this->baseObject);

    // Set default colors
    this->textColorNormal  = DAT_00e44790;      // e.g., 0xFFFFFF
    this->textColorPressed = 0xFFFF00;          // Yellow
    this->textColorHover   = DAT_00e2b1a4;      // e.g., 0xAAAAAA

    // Clear flags and padding
    this->someFlag     = 0;
    this->byteAt0x128  = 0;
    this->byteAt0x129  = 0;
    this->someOther    = 0;

    // Finalize base object
    FUN_00495ee0(&this->baseObject);

    return;
}