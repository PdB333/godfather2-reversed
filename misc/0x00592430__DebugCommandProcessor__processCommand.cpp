// FUNC_NAME: DebugCommandProcessor::processCommand
// Address: 0x00592430
// This function reads a command string from the EAX register (first byte must be newline),
// extracts a 16-bit command index, validates it against a global limit, and dispatches
// via a global function table (12-byte entries, handler at offset +4).

#include <cstdint>

// Global data (from DAT_01205570 and DAT_01205574)
extern CommandEntry* g_commandTable;   // base address of the command table
extern int32_t g_maxCommandIndex;       // maximum valid index

// Structure for a command table entry (12 bytes)
#pragma pack(push, 1)
struct CommandEntry {
    uint8_t unknown[4];                  // +0x00: possibly some flags/type
    void (*handler)(void*, int32_t, char*); // +0x04: function pointer
    uint8_t reserved[4];                 // +0x08: possibly more data
};
#pragma pack(pop)

// Function: processes a command string (pointer expected in EAX on x86)
// param_1 is a context pointer (e.g., a "this" for the dispatcher)
void __fastcall DebugCommandProcessor::processCommand(void* param_1, const char* command)
{
    // command is actually passed in EAX register, but we define it as fastcall first param.
    // Ghidra shows it as in_EAX; we simulate with fastcall convention.

    if (*command != '\n')
        return;

    int32_t index = *reinterpret_cast<const int16_t*>(command + 2);
    if (index < 0 || index >= g_maxCommandIndex)
        return;

    // Get the handler from the table entry at offset index*12
    CommandEntry* entry = &g_commandTable[index];
    void (*handler)(void*, int32_t, char*) = entry->handler;
    if (handler == nullptr)
        return;

    // local buffer passed to handler (likely for result or argument parsing)
    char localBuffer[12] = {0};
    handler(*reinterpret_cast<void**>(param_1), index, localBuffer);
}