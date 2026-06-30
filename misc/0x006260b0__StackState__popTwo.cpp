// FUNC_NAME: StackState::popTwo
// Address: 0x006260b0
// Role: Pops two 32-bit values from a stack-like structure, with conditional push for a specific global context.

#include <cstdint>

// Forward declarations for called functions
int32_t getStackBase(); // FUN_00625430
void* getGlobalContext(); // FUN_00637f10
void pushValue(void* context, uint32_t value, int32_t* type); // FUN_00637d60

// Global sentinel for a specific context (e.g., debug/logging)
extern uint32_t DAT_00e2a93c;

// Stack state structure (offsets relative to param_3)
struct StackState {
    /* +0x00 */ uint32_t unknown0;
    /* +0x04 */ uint32_t unknown4;
    /* +0x08 */ int32_t stackPointer;   // Current stack pointer (index * 8)
    /* +0x0C */ int32_t stackBase;      // Base offset for stack
};

void __fastcall popTwo(void* thisPtr, int32_t index, StackState* state, int32_t extraParam) {
    int32_t stackOffset;
    uint32_t value1;
    int32_t currentPointer;
    void* context;
    int32_t type = 3; // Type identifier for pushValue

    // Determine the stack offset from which to pop
    if (index < 1) {
        stackOffset = getStackBase();
    } else {
        stackOffset = state->stackBase + (-8 + index * 8);
    }

    value1 = *(uint32_t*)(stackOffset + 4); // Second value (higher address)
    currentPointer = state->stackPointer;

    context = getGlobalContext();
    if (context == &DAT_00e2a93c) {
        // Under specific global context, push the popped value back with type 3
        pushValue(state, value1, &type);
    }

    // Pop two values from the stack (at currentPointer - 8 and currentPointer - 4)
    *(uint32_t*)context = *(uint32_t*)(currentPointer - 8);
    *((uint32_t*)context + 1) = *(uint32_t*)(currentPointer - 4);

    // Update stack pointer (pop two 4-byte values)
    state->stackPointer -= 8;
}