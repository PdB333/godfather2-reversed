// FUNC_NAME: ScriptEngine::enterScope
// Address: 0x00642d40
// Role: Pushes a new scope/expression level, adjusting max depth and checking for overflow.
// Called when entering a new expression or function call context.

void __fastcall ScriptEngine::enterScope(void* thisPtr, void* nodePtr /* in EAX */)
{
    // thisPtr is an opaque context pointer (param_1)
    // nodePtr is a pointer to the current AST node (in_EAX), used to check its type.

    int* context = (int*)thisPtr; // treat as int array for field access
    char* globalState; // pointer to some global state, obtained from context[0]
    int newDepth;
    int temp;

    // Check if the current node type is not 0xB (certain node type that bypasses depth tracking?)
    if (*(int*)nodePtr != 0xB) {
        globalState = (char*)*context; // context[0] -> pointer to global state structure
        newDepth = context[9] + 1;    // context[9] (offset 0x24) is current scope depth, increment for new scope

        // Check if the new depth exceeds the maximum allowed depth stored at globalState+0x47
        if ( (unsigned int)(unsigned char)globalState[0x47] < newDepth ) {
            if (newDepth > 0xF9) { // maximum nesting depth = 249
                temp = context[3]; // context[3] (offset 0xC) - possibly error handler or string table
                // Report error: function or expression too complex
                FUN_00638b80("function or expression too complex");
                // Note: extraout_ECX and extraout_EDX are leftover from the error call,
                // but the code continues with updated registers. Here we ignore them for clean reconstruction.
                // The original likely had a branch to cleanup or abort.
            }
            // Update the maximum depth in the global state
            globalState[0x47] = (char)newDepth;
        }

        // Increment current scope depth in context
        context[9] = newDepth;

        // Call a function to set up the new scope (e.g., allocate a stack frame) with the previous depth
        FUN_00642c40(context[9] - 1);
    }
    return;
}