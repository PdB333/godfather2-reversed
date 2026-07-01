// FUNC_NAME: DebugConsoleCommand::DebugConsoleCommand

// Constructor for a debug console command. Registers the command in a global linked list.
// Offsets:
// +0x00: vtable pointer (set to PTR_LAB_00d77e28)
// +0x04: param_3 (likely function pointer to execute)
// +0x08: param_5 (additional data)
// +0x0C: param_4 (additional data)
// +0x10: next0 (always 0)
// +0x14: next1 (always 0)
// +0x18: next2 (always 0)
// +0x1C: next3 (always 0)
// +0x20: name buffer (0x40 bytes, 64 characters including null)
// +0x70: pNext (pointer to next command in global list)

#include <string.h>

extern void* PTR_LAB_00d77e28; // vtable for DebugConsoleCommand
extern DebugConsoleCommand* DAT_012059ec; // global head of command list

void FUN_0064cc90(void); // base class constructor (likely cCommandBase)

class DebugConsoleCommand {
public:
    void* vtable;                    // +0x00
    int param3;                      // +0x04 (function pointer?)
    int param5;                      // +0x08
    int param4;                      // +0x0C
    int zero1;                       // +0x10
    int zero2;                       // +0x14
    int zero3;                       // +0x18
    int zero4;                       // +0x1C
    char name[64];                   // +0x20
    DebugConsoleCommand* pNext;      // +0x70

    DebugConsoleCommand(const char* cmdName, int func, int data1, int data2);
};

DebugConsoleCommand::DebugConsoleCommand(const char* cmdName, int func, int data1, int data2)
{
    FUN_0064cc90(); // base class initialization

    this->vtable = &PTR_LAB_00d77e28;
    strncpy(this->name, cmdName, 63);
    this->name[63] = '\0'; // ensure null terminator

    this->param3 = func;
    this->param4 = data1;
    this->param5 = data2;

    // These fields are always zeroed (maybe reserved)
    this->zero1 = 0;
    this->zero2 = 0;
    this->zero3 = 0;
    this->zero4 = 0;

    // Insert this command at the head of the global list
    this->pNext = DAT_012059ec;
    DAT_012059ec = this;
}