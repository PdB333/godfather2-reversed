// FUNC_NAME: ScriptCompiler::parseLocalVariables

void ScriptCompiler::parseLocalVariables(void)
{
    int *table;
    int iVar1;
    int iVar2;
    undefined4 tokenPayload;
    undefined4 uVar3;
    int iVar4;
    int localCount;
    int newCapacity;
    
    localCount = 0;
    while (*(int *)(this + 0xc) == 0x116)
    {
        // Save previous token payload
        tokenPayload = *(undefined4 *)(this + 0x10);
        *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
        // If next token is identifier (0x11f), consume it
        if (*(int *)(this + 0x14) == 0x11f)
        {
            uVar3 = getNextToken(this + 0x10);
        }
        else
        {
            uVar3 = *(undefined4 *)(this + 0x14);
            *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
            *(undefined4 *)(this + 0x14) = 0x11f;
        }
        table = *(int **)(this + 0x1c);
        *(undefined4 *)(this + 0xc) = uVar3;   // update current token

        // Check if adding another local would exceed limit (200)
        if (200 < table[0xd] + 1 + localCount)
            goto tooManyLocals;

        // Access symbol entry (first element of table)
        iVar1 = *table;
        // Ensure capacity in the variable array
        if (*(int *)(iVar1 + 0x38) < table[0xc] + 1)
        {
            int oldCapacity = *(int *)(iVar1 + 0x38);
            newCapacity = oldCapacity * 2;
            if (newCapacity < 4)
                newCapacity = 4;
            else if (0x3ffffffd < oldCapacity)
            {
                // Overflow handling; fall through to error
                if (0x7ffffff8 < oldCapacity)
                    goto overflowError;
                newCapacity = 0x7ffffffd;
            }
            // Reallocate array of 12-byte elements
            uVar3 = reallocArray(oldCapacity * 0xc, newCapacity * 0xc);
            *(int *)(iVar1 + 0x38) = newCapacity;
            *(int *)(iVar1 + 0x18) = uVar3;
        }

        // Store token payload in variable array at current index
        *(undefined4 *)(*(int *)(iVar1 + 0x18) + table[0xc] * 0xc) = tokenPayload;
        iVar1 = table[0xc];
        table[0xc] = iVar1 + 1; // increment index

        // Update mapping: map variable name (???)
        int newLocalCount = localCount + 1;
        table[table[0xd] + localCount + 0xae] = iVar1;

        // If current token is comma (0x2c), process next variable in list
        if (*(int *)(this + 0xc) != 0x2c)
            goto afterComma;

        // Handle comma: duplicate first part
        *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
        localCount = newLocalCount;
        // Consume next token (may be identifier)
        if (*(int *)(this + 0x14) == 0x11f)
        {
            uVar3 = getNextToken(this + 0x10);
            *(undefined4 *)(this + 0xc) = uVar3;
        }
        else
        {
            *(undefined4 *)(this + 0xc) = *(undefined4 *)(this + 0x14);
            *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
            *(undefined4 *)(this + 0x14) = 0x11f;
        }
    } // end while

    // If we exited loop, expected "local" keyword not found
    error("<name> expected");

tooManyLocals:
    uVar3 = formatString("too many %s (limit=%d)", "local variables", 200);
    error(uVar3);
    iVar4 = this;
    // Fall through to assert/abort

overflowError:
    assert(iVar4, &DAT_00e2f044); // likely a string constant

afterComma:
    // If current token is '=', handle assignment
    if (*(int *)(this + 0xc) == 0x3d)
    {
        *(undefined4 *)(this + 8) = *(undefined4 *)(this + 4);
        if (*(int *)(this + 0x14) == 0x11f)
        {
            uVar3 = getNextToken(this + 0x10);
            *(undefined4 *)(this + 0xc) = uVar3;
            uVar3 = emitExpression();
        }
        else
        {
            uVar3 = *(undefined4 *)(this + 0x14);
            *(undefined4 *)(this + 0x14) = 0x11f;
            *(undefined4 *)(this + 0xc) = uVar3;
            *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
            uVar3 = emitExpression();
        }
    }
    else
    {
        uVar3 = 0;
    }
    emitAssignment(iVar4, uVar3);
    finalizeVariables();
    return;
}