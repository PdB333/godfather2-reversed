// FUNC_NAME: ExpressionCompiler::pushExpressionNode
// Address: 0x00642ec0
// Role: Pushes a new expression node onto the compiler's internal stack, managing depth limits.
// Called from multiple expression parsing functions to track nesting complexity.

void __fastcall ExpressionCompiler::pushExpressionNode(int *this)
{
    int oldDepth;
    int maxDepth;
    int *scriptContext;

    // Perform pre-push checks (likely updates internal state or validates context)
    prePushCheck();

    // Global compiler state (e.g., type of script being compiled)
    volatile int *globalState = (volatile int*)0x0; // Actual address unknown; treat as volatile
    if ((*globalState == 0xb) &&
        (this[0xd] <= globalState[1]) &&
        (globalState[1] < 0xfa)) {
        // Decrement depth if condition matches (maybe to share stack space)
        this[9]--;
    }

    // Retrieve the script context object (pointer at offset 0 of this)
    scriptContext = (int*)*this;  // +0x0: ptr to ScriptContext
    // Get current depth and max allowed depth from script context at offset 0x47
    maxDepth = (int)*(char*)((int)scriptContext + 0x47);  // byte at +0x47
    oldDepth = this[9] + 1;  // depth after increment
    if (maxDepth < oldDepth) {
        if (0xf9 < oldDepth) {
            // Complexity limit exceeded; report error via parent compiler/reporter
            this = (int*)this[3];  // +0xC: pointer to error handler
            oldDepth = reportError("function or expression too complex");
        }
        // Update max depth byte in script context
        *(char*)((int)scriptContext + 0x47) = (char)oldDepth;
    }
    // Increment depth
    this[9]++;
    // Notify depth change (pass old depth)
    onDepthChanged(this[9] - 1);
    return;
}