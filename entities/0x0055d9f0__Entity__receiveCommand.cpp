// FUNC_NAME: Entity::receiveCommand
// Function address: 0x0055d9f0
// This function is likely part of the Entity class, handling incoming commands (e.g., from scripts or network).
// It copies a 16-byte command structure from the pointer passed in EAX, checks a flag at offset 0xD8 of a related object,
// and then processes the command.
// 
// Offsets:
//   this+0x18: pointer to another object (e.g., a component, maybe EntityData or SentientData)
//   (*this+0x18)+0xD8: byte flag (e.g., debug flag or state byte)
//
// The global DAT_00e2b1a4 is used as the 4th dword of the command data (possibly a timestamp or ID).

struct CommandData {
    uint32_t data0; // +0x00
    uint32_t data1; // +0x04
    uint32_t data2; // +0x08
    uint32_t data3; // +0x0C
};

extern uint32_t DAT_00e2b1a4; // Global variable

// Forward declarations for called functions
void __cdecl FUN_009f4240(int, int, int); // Possibly debug logging or assertion
void __cdecl FUN_009f4c40(CommandData *cmd); // Processes the command

class Entity {
public:
    // __thiscall
    void __thiscall receiveCommand(CommandData *command);
};

void __thiscall Entity::receiveCommand(CommandData *command) {
    CommandData localCmd;
    // Copy command data into local stack (16 bytes)
    localCmd.data0 = command->data0;
    localCmd.data1 = command->data1;
    localCmd.data2 = command->data2;
    localCmd.data3 = DAT_00e2b1a4; // Override the 4th field with a global constant

    // Check a flag in a nested object (this+0x18 -> +0xD8)
    // The byte is compared to 0x07 (ASCII bell), possibly a debug/state flag.
    if (*(char*)(*(int*)((int)this + 0x18) + 0xD8) == '\a') {
        // Call debug/logging function with parameters (1, 1, 0)
        FUN_009f4240(1, 1, 0);
    }

    // Process the command data (e.g., apply to the entity)
    FUN_009f4c40(&localCmd);
}