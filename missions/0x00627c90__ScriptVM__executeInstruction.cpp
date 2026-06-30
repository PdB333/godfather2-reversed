// FUNC_NAME: ScriptVM::executeInstruction
// Address: 0x00627c90
// Role: Executes a single bytecode instruction for a custom virtual machine.
// The VM uses a stack (stackPointer at this+0x08) and a runtime state (this+0x10).
// Instructions are pairs of (opcode, value) stored on the stack as two 32-bit words.
// Opcodes 3 and 4 are special; opcode 0 triggers a function call/return sequence.

#include <cstdint>

// Forward declarations of helper functions (likely internal to the VM module)
// These would be defined elsewhere in the binary.
void preExecuteInstruction(uint32_t* vmState, uint32_t operand);                                          // FUN_00625ca0
uint32_t* getGlobalValueForOpcode3();                                                                     // FUN_00637f10
uint32_t* getGlobalValueForOpcode4();                                                                     // FUN_00637f90
uint32_t* getDefaultGlobalValue();                                                                        // FUN_00637ea0
void maybeGrowStack(uint32_t* runtimeState);                                                              // FUN_00627360
uint32_t createNewValue(uint32_t a, uint32_t b);                                                          // FUN_00637c50
uint32_t* getStackSlot(uint32_t* vmState, uint32_t frameBaseOffset);                                      // FUN_00638020

// The VM state structure (inferred from offsets used in this function)
struct RuntimeState {
    uint32_t unknown[8];          // +0x00 to +0x1C
    uint32_t stackDepthLimit;     // +0x20
    uint32_t currentDepth;        // +0x24
    uint32_t unknown2[2];         // +0x28 to +0x2C
    int32_t* frameBase;           // +0x30 (points to the base of the current call frame on the stack)
};

struct ScriptVM {
    void* vtable;                 // +0x00
    uint32_t unknown;             // +0x04
    uint32_t* stackPointer;       // +0x08 (points to the current top of the instruction stack)
    uint32_t unknown2;            // +0x0C
    RuntimeState* runtimeState;   // +0x10
};

int32_t ScriptVM::executeInstruction(uint32_t operand) {
    preExecuteInstruction(reinterpret_cast<uint32_t*>(this), operand);   // call to FUN_00625ca0

    // Current instruction is at stackPointer[-8] (opcode) and stackPointer[-4] (value)
    uint32_t* stackPtr = this->stackPointer;
    uint32_t opcode = *(stackPtr - 2);  // iVar1[-8] == stackPtr[-2] in 32-bit units? No: iVar1 is int*, offset in bytes.
                                         // Actually iVar1 is an int*, so iVar1 - 8 is decrement by 8*4 = 32 bytes? 
                                         // Wait, iVar1 is int*, so iVar1 - 8 decrements the pointer by 8 ints, i.e., 32 bytes.
                                         // But the code does *(int *)(iVar1 + -8) and *(int *)(iVar1 + -4). 
                                         // Since iVar1 is int*, iVar1 + -8 is actually decrement by 8 ints (32 bytes) -> this is suspicious.
                                         // But based on the pattern of the stack (decrementing by 8 in bytes later: *(int*)(param_1+8) = piVar3; piVar3 = iVar1 - 8; then later stackPointer += 8 (in bytes) ), 
                                         // the stack is managed in bytes, but iVar1 is cast to int*. So iVar1 - 8 means subtract 8*sizeof(int) = 32 bytes. That doesn't match 8-byte increments.
                                         // More likely: iVar1 is actually a byte pointer, but the decompiler treats it as int*. 
                                         // Looking at the code: iVar1 = *(int *)(param_1 + 8) => iVar1 is the value at offset 8, which is a pointer (stackPointer). 
                                         // Then *(int *)(iVar1 + -8) -> treats iVar1 as a pointer to int, so subtracted bytes are -8*4 = -32, but that seems too large.
                                         // Given later stackPointer is incremented by 8 (in bytes? Actually *(int *)(param_1+8) = *(int *)(param_1+8) + 8; so the pointer is incremented by 8 bytes (since it's stored as int* but arithmetic is on int*? In C, pointer arithmetic adds multiples of pointed-to type. So if stackPointer is int*, then +8 adds 32 bytes. That would be inconsistent.
                                         // To resolve: The decompiler likely misinterpreted pointer arithmetic. In the original x86 assembly, the instructions use immediate offsets in bytes, not pointer arithmetic. So the correct interpretation is that stackPointer is a byte pointer (char*), but Ghidra's decompiler treats it as int*. We need to use byte offsets.
                                         // Better to treat stackPointer as uint8_t* (byte pointer). Then iVar1 is a byte pointer, and offsets -8 and -4 are byte offsets.
                                         // So we'll reinterpret: uint8_t* stackPtrBytes = reinterpret_cast<uint8_t*>(stackPtr); but that makes code ugly.
                                         // Alternatively, we can keep stackPointer as uint32_t* and use manual byte offset casting. For clarity, I'll treat stackPointer as a pointer to uint8_t[].
                                         // Let's assume the decompiler's arithmetic is off; we'll use byte offsets consistently.
    // Instead, I'll define a local char* to match byte offsets.
    uint8_t* sp = reinterpret_cast<uint8_t*>(this->stackPointer);
    uint32_t opcode = *reinterpret_cast<uint32_t*>(sp - 8);
    uint32_t value = *reinterpret_cast<uint32_t*>(sp - 4);

    uint32_t* newPair;
    if (opcode == 3) {
        // Check if the float reinterpret of value equals its integer truncation (likely a NaN or infinity check)
        float fval = *reinterpret_cast<float*>(&value);
        if (static_cast<float>(static_cast<int32_t>(fval)) == fval) {
            newPair = getGlobalValueForOpcode3();
            goto writePair;
        }
    } else if (opcode == 4) {
        newPair = getGlobalValueForOpcode4();
        goto writePair;
    }
    newPair = getDefaultGlobalValue();

writePair:
    // Overwrite the current instruction with the fetched pair
    *reinterpret_cast<uint32_t*>(sp - 8) = newPair[0];
    *reinterpret_cast<uint32_t*>(sp - 4) = newPair[1];

    // Check the preceding stack entry (the one that will become top when we pop the current instruction)
    uint8_t* prevStack = sp - 8;  // piVar3 = iVar1 - 8 in bytes
    if (prevStack != nullptr && *reinterpret_cast<uint32_t*>(prevStack) == 0) {
        // The previous opcode is 0 => this is a function call/return context.
        // Replace the current instruction with opcode 5 and a new value, then run a complex sequence.
        this->stackPointer = reinterpret_cast<uint32_t*>(prevStack);  // stack pointer now points to the previous instruction
        // Check call depth against limit (runtimeState->+0x20 and +0x24)
        if (this->runtimeState->stackDepthLimit <= this->runtimeState->currentDepth) {
            maybeGrowStack(reinterpret_cast<uint32_t*>(this->runtimeState));
        }
        sp = reinterpret_cast<uint8_t*>(this->stackPointer);
        // Push opcode 5 and a new value onto the stack
        *reinterpret_cast<uint32_t*>(sp) = 5;
        *reinterpret_cast<uint32_t*>(sp + 4) = createNewValue(0, 0);
        this->stackPointer = reinterpret_cast<uint32_t*>(sp + 8); // advance stack by 8 bytes

        // Execute some pre-instruction logic (likely fetch next instruction)
        preExecuteInstruction(reinterpret_cast<uint32_t*>(this), operand);

        // Swap the two elements below the current stack pointer? 
        // The code does: *puVar2 = puVar2[-4]; puVar2[1] = puVar2[-3]; then increments stack.
        // This appears to be a "rotate" or "swap" of stack entries.
        sp = reinterpret_cast<uint8_t*>(this->stackPointer);
        *reinterpret_cast<uint32_t*>(sp) = *reinterpret_cast<uint32_t*>(sp - 16);   // copy from 4 entries below
        *reinterpret_cast<uint32_t*>(sp + 4) = *reinterpret_cast<uint32_t*>(sp - 12);
        this->stackPointer = reinterpret_cast<uint32_t*>(sp + 8);

        // Get a stack slot at offset runtimeState->frameBase (at runtimeState+0x30) and write the current top pair into it, then pop.
        sp = reinterpret_cast<uint8_t*>(this->stackPointer);
        uint32_t* slot = getStackSlot(reinterpret_cast<uint32_t*>(this), this->runtimeState->frameBase);
        *slot = *reinterpret_cast<uint32_t*>(sp - 8);
        *(slot + 1) = *reinterpret_cast<uint32_t*>(sp - 4);
        this->stackPointer = reinterpret_cast<uint32_t*>(sp - 16); // pop two pairs (16 bytes)

        // Again swap/rotate
        sp = reinterpret_cast<uint8_t*>(this->stackPointer);
        *reinterpret_cast<uint32_t*>(sp) = *reinterpret_cast<uint32_t*>(sp - 8);
        *reinterpret_cast<uint32_t*>(sp + 4) = *reinterpret_cast<uint32_t*>(sp - 4);
        this->stackPointer = reinterpret_cast<uint32_t*>(sp + 8);

        // Execute pre-instruction logic again
        preExecuteInstruction(reinterpret_cast<uint32_t*>(this), operand);

        // Get another stack slot and write the current top pair, then pop.
        sp = reinterpret_cast<uint8_t*>(this->stackPointer);
        slot = getStackSlot(reinterpret_cast<uint32_t*>(this), this->runtimeState->frameBase);
        *slot = *reinterpret_cast<uint32_t*>(sp - 8);
        *(slot + 1) = *reinterpret_cast<uint32_t*>(sp - 4);
        this->stackPointer = reinterpret_cast<uint32_t*>(sp - 16);

        return 1; // instruction executed successfully
    }

    return 0; // instruction not executed (or no special action)
}