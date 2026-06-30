// FUNC_NAME: ScriptVM::executeCall

// Function address: 0x00642ec0
// Implements the "call" opcode for the EA script VM.
// Handles call depth tracking, recursion limit (max 0xf9),
// and tail-call optimization for operand type 0xb (function).

void __fastcall ScriptVM::executeCall(ScriptVM* vmState, int* operand)
{
    // Prologue: save current execution state
    callPrologue();

    // Check for tail-call opportunity:
    // Operand type == 0xB (function), and argument count (slot 13) fits within
    // the function's expected parameter range [operand[1], 0xFA)
    if ((*operand == 0xB) &&
        (vmState->slots[13] <= operand[1]) &&
        (operand[1] < 0xFA))
    {
        // Adjust depth for tail call (reduce stack usage)
        vmState->depth--;
    }

    // Fetch the global state pointer (used for max depth)
    int* globalState = vmState->globalStatePtr;
    int newDepth = vmState->depth + 1;

    // Enforce recursion depth limit (max depth stored at globalState+0x47)
    if ((unsigned char)(*(globalState + 0x47 / sizeof(int))) < newDepth)
    {
        if (newDepth > 0xF9)
        {
            // Depth exceeded -> report error
            vmState = (ScriptVM*)vmState->errorContext; // switch to error context
            setScriptError("function or expression too complex"); // FUN_00638b80
        }
        // Update max depth recorded
        *((char*)(globalState) + 0x47) = (char)newDepth;
    }

    // Advance depth and push new call frame (old depth as parameter)
    vmState->depth = newDepth;
    pushCallFrame(vmState->depth - 1);
}