// FUNC_NAME: MultiplayerRoundCompletedEvent::MultiplayerRoundCompletedEvent
// Address: 0x008b2b20
// Constructor for a message handler that processes round completion events in the multiplayer scenario

#include <cstdint>

// Forward declarations for external functions
extern void __thiscall FUN_008b2650(void* param_2);
extern void __fastcall FUN_00408240(void* msgSystem, const char* messageName);
extern void __fastcall FUN_00408680(void* msgSystem);

class MultiplayerRoundCompletedEvent {
public:
    // Vtable pointer at offset 0x00
    void* vtable; // +0x00

    // Remaining member fields (offsets inferred from decompilation)
    void* field_0x3C; // +0x3C, initially set to &PTR_LAB_00d7ad54
    void* field_0x48; // +0x48, initially set to &PTR_LAB_00d7ad50

    // Magic sentinel values (probably for debug buffer checks)
    uint32_t magic1; // +0x64, 0xBADBADBA
    uint32_t magic2; // +0x68, 0xBEEFBEEF
    uint32_t magic3; // +0x6C, 0xEAC15A55
    uint32_t magic4; // +0x70, 0x91100911

    // Zero-initialized fields
    uint32_t zero1; // +0x74
    uint32_t zero2; // +0x78
    uint32_t zero3; // +0x7C
    uint32_t zero4; // +0x80
    uint32_t zero5; // +0x84
    uint32_t zero6; // +0x88
    uint32_t zero7; // +0x8C

    // Constructor: initializes the event listener for multiplayer round completed messages
    __thiscall MultiplayerRoundCompletedEvent(void* param_2) {
        // Call base or sub-object constructor with the given parameter
        FUN_008b2650(param_2);

        // Set up vtable pointer
        this->vtable = &PTR_FUN_00d7ad64;

        // Assign additional function/data pointers
        this->field_0x3C = &PTR_LAB_00d7ad54;
        this->field_0x48 = &PTR_LAB_00d7ad50;

        // Initialize magic constants (possibly for integrity checking)
        this->magic1 = 0xBADBADBA;
        this->magic2 = 0xBEEFBEEF;
        this->magic3 = 0xEAC15A55;
        this->magic4 = 0x91100911;

        // Clear remaining fields
        this->zero1 = 0;
        this->zero2 = 0;
        this->zero3 = 0;
        this->zero4 = 0;
        this->zero5 = 0;
        this->zero6 = 0;
        this->zero7 = 0;

        // Register this object as handler for the "iMsgMultiplayerRoundCompleted" message
        FUN_00408240(&DAT_0112f4b4, "iMsgMultiplayerRoundCompleted");
        FUN_00408680(&DAT_0112f4b4);
    }
};