// FUNC_NAME: ScriptInterpreter::processOpcode4

// 0x00628940: Handles an opcode 4 instruction with three integer operands.
// Context pointer passed in EDI (likely a frame/thread context).
// Returns 1 on success, 0 if no operands remain.

typedef int (*BufferFlushFunc)(void);
typedef int (*OperandProcessorFunc)(void* context, const int* operands, int size);

// Structure pointed to by EDI
struct ScriptFrame {
    const int* pOperandStream;  // +0x00: pointer to current operand data
    int statementCount;         // +0x04: number of statements executed
    void* pVMContext;           // +0x08: pointer to VM state (contains output buffer)
};

// VM state structure - partial definition
struct VMState {
    char pad_0x00[8];
    int* pOutputBuffer;         // +0x08: current write position in output buffer
    char pad_0x10[16];         // +0x10: buffer capacity (offset 0x20 and 0x24 within sub-structure)
};

int ScriptInterpreter::processOpcode4(void)
{
    ScriptFrame* pFrame = (ScriptFrame*)EDI;
    int operandSize;
    VMState* pVM;
    int* pOutput;
    int result;

    // Calculate remaining operand size based on self-referential offset.
    // The operand stream is placed such that its start address is stored at pFrame[0],
    // and the size is derived by subtracting the frame address and a fixed 12-byte offset.
    operandSize = (*pFrame->pOperandStream - (int)pFrame) - 12;
    if (operandSize == 0) {
        return 0; // No operands to process
    }

    pVM = (VMState*)pFrame->pVMContext;

    // Check if the output buffer has enough space (capacity at +0x20 vs used at +0x24 inside sub-structure at +0x10)
    if (*(uint*)(*(int*)((char*)pVM + 0x10) + 0x20) <= *(uint*)(*(int*)((char*)pVM + 0x10) + 0x24)) {
        // Buffer full - flush or expand
        BufferFlushFunc flush = (BufferFlushFunc)0x00627360;
        flush();
    }

    pOutput = pVM->pOutputBuffer;
    *pOutput = 4; // Emit opcode 4

    // Process the three integer operands and get a result value
    OperandProcessorFunc processOperands = (OperandProcessorFunc)0x00638920;
    result = processOperands(pVM, pFrame + 3, operandSize);
    pOutput[1] = result;

    // Advance output buffer by 8 bytes (opcode + result)
    pVM->pOutputBuffer += 8;

    // Advance operand stream by 3 ints (12 bytes)
    pFrame->pOperandStream = (const int*)((int)pFrame + 12);

    pFrame->statementCount++;
    return 1;
}