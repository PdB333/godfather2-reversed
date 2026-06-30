// FUNC_NAME: ScriptParser::parseLocalVariables

// This function parses a list of local variable declarations (e.g., "var a, b = expr, c;")
// It expects a sequence of identifiers separated by commas, ending with a semicolon.
// The parser maintains a token stream at offsets from the 'this' pointer.
void ScriptParser::parseLocalVariables()
{
    int *localVarTable;       // pointer to local variable management structure (+0x1c)
    int savedIndex;           // temporary for index storage
    int identifierValue;      // token value for the identifier being processed
    int variableCount = 0;    // number of variables added in this statement
    bool bStatementEnd = false;

    // +0x0c: current token type
    if (*(int *)(this + 0x0c) != 0x29)  // 0x29 = TOKEN_VAR (the 'var' keyword)
    {
        // Loop while the current token is an identifier (0x116)
        while (*(int *)(this + 0x0c) == 0x116)  // TOKEN_IDENTIFIER
        {
            // Save the identifier's value (e.g., name string) from +0x10
            identifierValue = *(int *)(this + 0x10);
            // Save the current "base" value from +0x04 into +0x08 (maybe for some expression stack)
            *(int *)(this + 0x08) = *(int *)(this + 0x04);

            // Check the next token type (+0x14)
            if (*(int *)(this + 0x14) == 0x11f)  // TOKEN_ASSIGNMENT '='
            {
                // Consume the assignment expression and update current token
                // FUN_00639c70 likely parses an expression after the '=', returns new token type
                *(int *)(this + 0x0c) = parseAssignmentExpression((int *)(this + 0x10));
            }
            else
            {
                // No assignment: just shift the token stream and mark as assignment?
                // This might be handling the case where a comma or semicolon follows directly.
                *(int *)(this + 0x0c) = *(int *)(this + 0x14);
                *(int *)(this + 0x10) = *(int *)(this + 0x18);
                *(int *)(this + 0x14) = 0x11f;  // Mark as assignment for next variable?
            }

            // Get the local variable table structure (this + 0x1c)
            localVarTable = *(int **)(this + 0x1c);

            // Check for max local variable limit (200)
            if (200 < localVarTable[0x0d] + 1 + variableCount)
            {
                goto errorTooManyLocalVars;
            }

            // Ensure there is enough space in the local variable name buffer
            // localVarTable[0x0c] is the current count of variable names stored
            // localVarTable[0x38] is the buffer capacity
            if (*(int *)(*localVarTable + 0x38) < localVarTable[0x0c] + 1)
            {
                // FUN_00627930 reallocates the name buffer
                *(int *)(localVarTable + 0x18) = allocateLocalVarSlot(
                    *(int *)(this + 0x20),          // some allocator context
                    *(int *)(*localVarTable + 0x18), // old buffer pointer
                    (int *)(*localVarTable + 0x38), // capacity pointer
                    0x0c,                           // element size (12 bytes per entry)
                    &DAT_00e2f044                    // maybe a memory pool
                );
            }

            // Store the identifier token value into the name buffer at the current index
            *(int *)(*(int *)(localVarTable + 0x18) + localVarTable[0x0c] * 0x0c) = identifierValue;

            savedIndex = localVarTable[0x0c];     // remember this index
            localVarTable[0x0c] = savedIndex + 1; // increment the count

            // Map the variable order to the saved index: store into a table at offset 0xae from localVarTable
            localVarTable[localVarTable[0x0d] + variableCount + 0xae] = savedIndex;

            variableCount++;

            // After handling one variable, check if the next token is a comma (0x2c)
            if (*(int *)(this + 0x0c) != 0x2c)   // TOKEN_COMMA
            {
                break;
            }

            // Comma found: save current base value and handle assignment if present
            *(int *)(this + 0x08) = *(int *)(this + 0x04);
            if (*(int *)(this + 0x14) == 0x11f)  // TOKEN_ASSIGNMENT
            {
                *(int *)(this + 0x0c) = parseAssignmentExpression((int *)(this + 0x10));
            }
            else
            {
                // Shift tokens and mark next as assignment
                *(int *)(this + 0x0c) = *(int *)(this + 0x14);
                *(int *)(this + 0x10) = *(int *)(this + 0x18);
                *(int *)(this + 0x14) = 0x11f;
            }
        }

        // After processing all variables, expect a semicolon (0x118) or similar end-of-statement
        if (*(int *)(this + 0x0c) != 0x118)  // TOKEN_SEMICOLON
        {
            errorOut("<name> or `...' expected");
            // jump to error handling that prints "too many local variables" (might be wrong path)
            // but code flows to the same error label
        }

        // Set flag indicating we saw the semicolon
        bStatementEnd = true;
    }

    // Finalize the local variable list
    finalizeLocalVarList(bStatementEnd);
    return;

errorTooManyLocalVars:
    // Output error: "too many local variables (limit=200)"
    // FUN_00636c00 constructs the error message string
    errorOut(formatString("too many %s (limit=%d)", "local variables", 200));
    // Break into debugger (software interrupt)
    asm("swi 3");
    // The code after swi is unreachable; we return anyway
    return;
}