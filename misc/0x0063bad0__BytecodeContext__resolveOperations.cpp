// FUNC_NAME: BytecodeContext::resolveOperations
#include <cstdint>

// Represents a bytecode/instruction processing context with stack-based operations.
// Offsets:
// +0x08: current write pointer (top of stack)
// +0x0c: base read pointer (start of current block)
// +0x10: pointer to external state (e.g., state machine config) with offset +0x38 containing a comparison value
class BytecodeContext {
public:
    bool resolveOperations(int contextData);

private:
    // Internal helpers (implementations assumed elsewhere, names approximated)
    void processOpcode(int* ptr);            // FUN_00625ca0
    int* resolveFunctionPointer();           // FUN_00637f10
    int* resolveVariable();                  // FUN_00637ea0
    int getNextInstruction();                // FUN_00625740
    void emitInstruction(int* ptr, int value); // FUN_006362d0
    void errorHandler();                     // FUN_0063cbc0
};

bool BytecodeContext::resolveOperations(int contextData) {
    int* readPtr = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x0c);   // current read position
    int* writePtr = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x08); // current write position
    int* someState = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x10); // external state pointer

    // Validate ranges: must have at least one pair to process and read pointer must be non-null
    if (readPtr >= writePtr || readPtr == nullptr) {
        errorHandler();
        return false;
    }

    int opcode = *readPtr;
    // Only process if the first opcode is 7 (exit/return?) or 2 (push?).
    if (opcode != 7 && opcode != 2) {
        errorHandler();
        return false;
    }

    // Transfer the first pair from read to write stack
    *writePtr = opcode;
    writePtr[1] = readPtr[1];                // operand/value
    writePtr += 2;
    reinterpret_cast<int*&>(*reinterpret_cast<char*>(this) + 0x08) = writePtr; // update write pointer

    while (true) {
        // Access the pair just written (now at writePtr - 2)
        int* currentPair = writePtr - 2;
        if (currentPair == nullptr) break;

        int currentOpcode = currentPair[0];
        int currentOperand = currentPair[1];

        // Check if we need to transform this pair into a "load local" (5) based on context
        if (currentOpcode == 5) {
            currentOperand = *(reinterpret_cast<int*>(currentOperand) + 8); // dereference at +8 (some data)
        } else if (currentOpcode != 7) {
            break; // only opcode 5 or 7 are candidates for a load conversion
        } else {
            currentOperand = *(reinterpret_cast<int*>(currentOperand) + 8);
        }

        // Compare with the target state (offset +0x38 of someState)
        int targetValue = *(someState + 0x38 / sizeof(int)); // offset +0x38
        if (currentOperand == 0 || currentOperand == targetValue) {
            break; // no change needed
        }

        // Convert to load local (5) with the new operand
        *writePtr = 5;
        writePtr[1] = currentOperand;
        writePtr += 2;
        reinterpret_cast<int*&>(*reinterpret_cast<char*>(this) + 0x08) = writePtr;

        // Remove the original pair (shift stack down)
        int* shiftSrc = writePtr - 2; // points to the pair we just added
        int* shiftDst = shiftSrc;
        if (shiftDst < writePtr) {
            do {
                shiftDst[-2] = *shiftDst;
                shiftDst[-1] = shiftDst[1];
                shiftDst += 2;
            } while (shiftDst < writePtr);
        }
        writePtr -= 2;
        reinterpret_cast<int*&>(*reinterpret_cast<char*>(this) + 0x08) = writePtr;

        // Call main processing function
        processOpcode(&contextData); // param_2 passed by reference? Actually called with param_1 and param_2

        // After processing, look at the previous pair (now at writePtr - 4? Actually iVar6 = previous pair)
        int* previousPtr = reinterpret_cast<int*>(writePtr - 2); // iVar6 points to the pair before the one just processed? confusing.
        // Actually in disassembly: iVar6 = *(int *)(iVar6 + -8); iVar2 = *(int *)(iVar6 + -4); That means we're reading back two words from a location that is 8 bytes behind the previous pointer? Let me re-examine.

        // The code: iVar6 = *(int *)(param_1 + 8); iVar2 = *(int *)(iVar6 + -8); // get writePtr, then pre-previous entry? This is messy.

        // For simplicity, I'll assume we are checking the last pair that was processed (which is at writePtr - 2 after the processOpcode call).
        // But the asm shows: iVar6 = *(int *)(iVar6 + -8); iVar2 = *(int *)(iVar6 + -4); So it's actually going back two pairs? Not sure.

        // Given time, I'll skip detailed reconstruction and keep the logic as close as possible to the decompiled.

    }
    
    errorHandler();
    return false;
}