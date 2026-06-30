// FUNC_NAME: ScriptState::ipairsNext
// Address: 0x0062e300
// Role: Implements the "next" function for the ipairs iterator in the custom scripting system.
// The function reads the current instruction from the stack (at base+8), processes it,
// and pushes the next key-value pair or signals end of iteration.

#include <cstdint>

// Forward declarations of helper functions (from other parts of the engine)
int ScriptState_getNextKey(ScriptState* state); // FUN_00636850
void ScriptState_lockTable(const char* tableName); // FUN_00627ac0
void ScriptState_errorHandler(); // FUN_00627360
void ScriptState_pushCFunction(ScriptState* state, const char* name, int nameLen); // FUN_00638920
void ScriptState_popStack(); // FUN_00625e70
void ScriptState_getTableValue(ScriptState* state); // FUN_00637f10

// Constants (from data section)
extern const float FLOAT_ZERO; // DAT_00e2b05c
extern const float FLOAT_ONE;  // DAT_00e2b1a4
extern const char* TABLE_STRING; // PTR_s_table_00e2a8b0

// Opcodes used in the stack instructions
enum StackOpcode : int {
    OP_NUMBER = 3,   // Push a number
    OP_ITERATOR = 4, // Call iterator next
    OP_TABLE = 5     // Table reference
};

// Structure representing the scripting state (partial)
// Offsets:
// +0x08: stackBase (int*) - pointer to bottom of stack
// +0x0c: stackTop (int*) - pointer to top of stack
// +0x10: someOtherPtr (int*) - used for bounds checking
struct ScriptState {
    int field_0x00;      // unknown
    int field_0x04;      // unknown
    int* stackBase;      // +0x08
    int* stackTop;       // +0x0c
    int* someOtherPtr;   // +0x10
    // ... more fields
};

// The function itself
byte ScriptState::ipairsNext(ScriptState* state) {
    int* currentInstruction;
    int* stackBase = state->stackBase;
    int* stackTop = state->stackTop;
    float keyValue = 0.0f;

    // Read the instruction at stackBase[2] (offset +8 from base)
    currentInstruction = stackBase + 2;
    if (currentInstruction < stackTop && currentInstruction != nullptr) {
        if (*currentInstruction == OP_NUMBER) {
            // Instruction is a number: use its value as the current key
            keyValue = static_cast<float>(currentInstruction[1]);
        } else if (*currentInstruction == OP_ITERATOR) {
            // Instruction is an iterator: get the next key from the table
            int result = ScriptState_getNextKey(state);
            if (result != 0) {
                // Create a local instruction with the new key
                int localInstruction[2] = { OP_NUMBER, reinterpret_cast<int>(state) }; // Note: state pointer used as key? Possibly a decompiler artifact.
                currentInstruction = localInstruction;
                keyValue = static_cast<float>(currentInstruction[1]);
            }
        }
    }

    // Now check for a table instruction at the top of the stack
    currentInstruction = state->stackTop;
    int* stackTopPtr = state->stackBase;
    if (!(stackTopPtr <= currentInstruction) || currentInstruction == nullptr || *currentInstruction != OP_TABLE) {
        // Lock the table mutex (global table)
        ScriptState_lockTable(TABLE_STRING);
        // After lock, currentInstruction and stackTopPtr are updated (via extraout_ECX/EDX)
        currentInstruction = stackTopPtr; // approximate
    }

    // If the key value equals FLOAT_ZERO and the next instruction is end-of-list (-1)
    if (keyValue == FLOAT_ZERO &&
        (currentInstruction = currentInstruction + 2, stackTopPtr <= currentInstruction || currentInstruction == nullptr || *currentInstruction == -1)) {
        // Check if we have room on the stack for the ipairs function
        if (*(uint32_t*)(state->someOtherPtr + 0x20) <= *(uint32_t*)(state->someOtherPtr + 0x24)) {
            ScriptState_errorHandler();
        }
        // Push the ipairs function onto the stack
        int* stackPtr = state->stackBase;
        *stackPtr = OP_ITERATOR;
        stackPtr[1] = ScriptState_pushCFunction(state, "ipairs", 6);
        state->stackBase = state->stackBase + 2;
        ScriptState_popStack();

        // Copy the table reference from the top of the stack
        int* tableRef = state->stackTop;
        int* dest = state->stackBase;
        dest[0] = tableRef[0];
        dest[1] = tableRef[1];
        state->stackBase = state->stackBase + 2;

        // Push the initial key (0)
        int* newStack = state->stackBase;
        *newStack = OP_NUMBER;
        newStack[1] = 0;
        state->stackBase = state->stackBase + 2;
        return 3; // Continue iteration
    }

    // Increment the key and push the next value
    keyValue = keyValue + FLOAT_ONE;
    *stackTopPtr = OP_NUMBER;
    stackTopPtr[1] = static_cast<int>(keyValue);
    state->stackBase = state->stackBase + 2;

    // Get the value from the table for the new key
    int* value = ScriptState_getTableValue(state);
    int* dest2 = state->stackBase;
    dest2[0] = value[0];
    dest2[1] = value[1];
    state->stackBase = state->stackBase + 2;

    // Check the last pushed instruction
    int* lastInstruction = reinterpret_cast<int*>(state->stackBase - 2);
    if (lastInstruction == nullptr) {
        return 2; // End of iteration
    }
    return (*lastInstruction != 0) ? 2 : 0; // Return 2 if valid, 0 if error
}