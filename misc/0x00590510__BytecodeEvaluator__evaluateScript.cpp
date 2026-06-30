// FUNC_NAME: BytecodeEvaluator::evaluateScript

#include <cstdint>

// Opcode function table (0x23 entries)
extern float (__thiscall* opcodeTable[0x23])(void* context, uint8_t* command, int* stack);

// Grow the result stack to at least a given size
extern void growResultStack(int* stack, int newSize);

// Recursive evaluation or fixup (called when index out of bounds?)
extern void fixupEvaluation(void* fixupParam);

// Structure: bytecode block (commands + result index pointer)
struct BytecodeBlock {
    char unknown0;                // +0x0 unknown
    int8_t commandCount;          // +0x1 number of commands
    short* resultIndexPtr;         // +0x4 pointer to short holding final result index
    uint8_t* commands[1];          // +0xC array of command pointers (variable length)
};

// Stack for storing intermediate results (array of float converted to int)
struct EvalStack {
    int* data;    // +0x0 pointer to array of ints (actually floats stored as int bits)
    int size;     // +0x4 number of elements allocated
};

// Evaluate bytecode block, return final float value
float __thiscall BytecodeEvaluator::evaluateScript(void* context, BytecodeBlock* block, EvalStack* stack) {
    short* resultIdxPtr = *(short**)((uint8_t*)block + 4); // pointer to final result index
    int count = (int)((int8_t*)(block))[1]; // command count at +0x1

    int* stackData = stack->data;
    int stackSize = stack->size;

    // Process each command in order
    for (int i = 0; i < count; i++) {
        uint8_t* cmd = block->commands[i];
        uint8_t opcode = cmd[0] & 0x3F; // opcode
        int result = 0;

        if (opcode < 0x23) {
            float val = opcodeTable[opcode](context, cmd, stack);
            result = (int)val; // store as integer (bit pattern of float)
        }
        // Get the index where result should be stored (from cmd's short at offset 2)
        uint16_t storeIdx = *(uint16_t*)(cmd + 2);
        // Ensure stack is large enough
        if (stackSize <= storeIdx) {
            int newSize = storeIdx + 1 - stackSize;
            growResultStack(stack, newSize);
            int curSize = stack->size;
            for (int j = curSize; j < curSize + newSize; j++) {
                int* slot = &stack->data[j];
                if (slot) *slot = 0;
            }
            curSize = stack->size;
            // Actually the grow function adjusts size accordingly; simplified
        }
        // Store result (as int) in stack at storeIdx
        stack->data[storeIdx] = result;
    }

    // Final result index from block's pointer
    uint16_t finalIdx = *resultIdxPtr;
    // Ensure stack size is at least finalIdx+1
    if (stackSize <= finalIdx) {
        int newSize = finalIdx + 1 - stackSize;
        growResultStack(stack, newSize);
        int curSize = stack->size;
        for (int j = curSize; j < curSize + newSize; j++) {
            int* slot = &stack->data[j];
            if (slot) *slot = 0;
        }
    }

    // Read final result as float, but then compare as int
    int resultInt = (int)*(float*)&stack->data[finalIdx];
    if (resultInt < 0) resultInt = 0;

    if (count <= resultInt) {
        return 1.0f;
    }

    // Get the command at index 'resultInt' and use its store index for a secondary result
    uint8_t* cmd = block->commands[resultInt];
    uint16_t secIdx = *(uint16_t*)(cmd + 2);
    if (stack->size <= secIdx) {
        int dummy = 0;
        fixupEvaluation(&dummy);
    }
    return *(float*)&stack->data[secIdx];
}