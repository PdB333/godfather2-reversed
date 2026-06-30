// FUNC_NAME: CommandQueue::pushCommand
// Address: 0x0050a750
// Role: Pushes a command onto the global command stack and immediately processes it.

// Global command stack structure (at DAT_01206880)
struct CommandStack {
    int* stackPointer; // +0x14: current position in the command stack
};

extern CommandStack g_CommandStack;            // Global command stack context
extern void* s_CommandHandlerTable;           // PTR_LAB_011250b8 – handler vtable/type table

// Function called to process the command after queuing
void __fastcall commandProcessFunction(int commandObject); // FUN_009c8eb0

void __fastcall CommandQueue::pushCommand(int commandObject)
{
    if (commandObject == 0)
        return;

    // Read command data from the object
    int cmdType = *(int*)(commandObject + 0x4C);   // +0x4C: command type ID
    int cmdData = *(int*)(commandObject + 0x50);   // +0x50: associated data

    // Push a command entry onto the global stack
    int* sp = g_CommandStack.stackPointer;
    *sp = (int)&s_CommandHandlerTable;   // Store handler table pointer
    sp++;
    *sp = commandObject;                 // Store the command object
    sp++;
    *sp = cmdType;                       // Store command type
    sp++;
    *sp = cmdData;                       // Store command data
    sp++;

    // Update the stack pointer
    g_CommandStack.stackPointer = sp;

    // Process the command immediately
    commandProcessFunction(commandObject);
}