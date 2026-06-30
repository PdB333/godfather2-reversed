// FUNC_NAME: ScriptEngine::executeScript
undefined4 ScriptEngine::executeScript(int* context)
{
    int* stackPtr;
    int* stackEnd;
    int* piVar4;
    int* extraout_ECX;
    int* extraout_ECX_00;
    int* piVar2;
    int iVar3;
    undefined4* puVar1;

    stackEnd = *(int**)(context + 0xc);           // +0xC: m_pStackEnd or m_pCodeEnd
    stackPtr = *(int**)(context + 8);             // +0x8: m_pStack

    // Validate initial opcodes: expect opcode 5 (table?) then opcode 6 (function?)
    if (((stackPtr <= stackEnd) || (stackEnd == (int*)0x0)) || (*stackEnd != 5))
    {
        stackEnd = (int*)FUN_00627ac0(PTR_s_table_00e2a8b0);  // error: expected table
        stackPtr = extraout_ECX;   // preserve modified stackPtr
    }
    piVar4 = stackEnd + 2;
    if (((stackPtr <= piVar4) || (piVar4 == (int*)0x0)) || (*piVar4 != 6))
    {
        FUN_00627ac0(PTR_s_function_00e2a8b4);    // error: expected function
        stackPtr = extraout_ECX_00;
    }

    *stackPtr = 0;          // clear stack top?
    *(int*)(context + 8) = *(int*)(context + 8) + 8;  // advance stack pointer

    while (true)
    {
        iVar3 = FUN_00637650();   // read next bytecode/instruction
        if (iVar3 == 0)
        {
            *(int*)(context + 8) = *(int*)(context + 8) - 8;  // revert stack
            return 0;
        }

        *(int*)(context + 8) = *(int*)(context + 8) + 8;  // advance stack

        // Copy two dwords from the code area (m_pCode + 8 and +0xc) to stack
        iVar3 = *(int*)(context + 0xc);          // m_pCode
        puVar1 = *(undefined4**)(context + 8);
        *puVar1 = *(undefined4*)(iVar3 + 8);
        puVar1[1] = *(undefined4*)(iVar3 + 0xc);
        *(int*)(context + 8) = *(int*)(context + 8) + 8;  // advance stack

        // Duplicate previous two stack entries (copy from offset -6 and -5 relative to current)
        puVar1 = *(undefined4**)(context + 8);
        *puVar1 = puVar1[-6];
        puVar1[1] = puVar1[-5];
        *(int*)(context + 8) = *(int*)(context + 8) + 8;  // advance stack

        // Duplicate again (copy from offset -6 again — note: this duplicates the just duplicated values)
        puVar1 = *(undefined4**)(context + 8);
        *puVar1 = puVar1[-6];
        puVar1[1] = puVar1[-5];
        *(int*)(context + 8) = *(int*)(context + 8) + 8;

        // Execute the opcode at position (stack - 0x18) with argument 1
        FUN_006362d0(context, *(int*)(context + 8) - 0x18, 1);

        iVar3 = FUN_00625740();   // check for break condition (interrupt?)
        if (iVar3 != 0) break;

        // If not break, revert stack by 0x10 (pop two dwords)
        *(int*)(context + 8) = *(int*)(context + 8) - 0x10;
    }

    return 1;
}