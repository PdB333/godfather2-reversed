// FUNC_NAME: ScriptCompiler::allocateLocalVariable
// Function address: 0x0063de90
// This function allocates a slot in the local variable table with a given name ID and optional offset.
// It checks for the 200-variable limit and calls an error function if exceeded.

void ScriptCompiler::allocateLocalVariable(int nameId, int offset)
{
    // +0x1c: pointer to LocalVariableTable structure
    LocalVariableTable* varTable = *(LocalVariableTable**)(this + 0x1c);
    
    // Check if adding this variable would exceed the limit (200).
    // varTable->count + 1 + offset > 200
    if (200 < varTable->varCount + 1 + offset) {
        // Format error message: "too many %s (limit=%d)", "local variables", 200
        char* errorMsg = formatString("too many %s (limit=%d)", "local variables", 200);
        // Output the error (e.g., to debug console or log)
        errorOutput(errorMsg);
    }
    
    // Resolve the name ID to a value (e.g., a string pointer or symbol index)
    int value = resolveName(nameId);
    
    // Store the value at the appropriate slot.
    // The slot index is varTable->varCount + offset.
    // Array of 4-byte values at offset 0x2b8 in the table structure.
    varTable->localVariables[varTable->varCount + offset] = value;
}