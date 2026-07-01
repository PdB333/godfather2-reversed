// FUNC_NAME: ScriptVM::execute
// Function address: 0x00634830
// Role: Main bytecode interpreter loop for EARS script VM

int* ScriptVM::execute(ScriptVM* thisPtr)
{
    int* result;
    uint opcodeWord;
    uint opcode;
    int* op1;
    int* op2;
    int* op3;
    int* varPtr;
    uint idx1;
    uint idx2;
    int idx3;
    int* ptr;
    int* dest;
    uint uVar13;
    uint uVar7;
    int iVar9;
    int iVar12;
    int iVar14;
    bool bVar15;
    float fVar16;
    uint* codePtr;       // local_40: current instruction pointer
    int* localVarBase;   // local_3c: base of local variable table
    int local_38;        // pointer to global variable storage
    int* exprDest;       // local_34: destination cell for result
    int* opAddr;         // local_2c: address of operand
    int* opAddr2;        // local_28: another operand address
    int intValue;        // local_24: temporary integer
    int intVal2;         // local_20: temporary integer
    int intArr[3];       // local_1c: temp array
    int tValue;          // local_10: temporary variable
    float tFloat;        // local_c: temporary float

    // Interpreter state struct offsets (relative to thisPtr)
    // +0x08: current stack top pointer (base pointer for expression evaluation)
    // +0x0c: pointer to local variable storage (offset by +/-?)
    // +0x10: pointer to global context/table
    // +0x14: pointer to execution stack frame (push/pop)
    // +0x30: flags (bit0: yield requested?, bit1: ?, bit2: ?, bit3: ?)
    // +0x38: yield counter (decremented each instruction)
    // +0x44: function table pointer? +0x10 points to something
    // +0x48: flag for something

    // Entry point - check if yield needed
LAB_00634840:
    if ((*(byte*)(thisPtr + 0x30) & 1) != 0)
    {
        // If yield flag set, store current code pointer in some structure
        *(uint***)(*(int*)(thisPtr + 0x14) + 0x10) = &codePtr;
        // Call yield function (likely returns when resume)
        FUN_00635d00(0xffffffff); // Yield with -1 token
    }

    // Normal execution start
LAB_0063485e:
    *(uint***)(*(int*)(thisPtr + 0x14) + 0x10) = &codePtr;
    *(undefined4*)(*(int*)(thisPtr + 0x14) + 8) = 2;  // set state to "running"
    codePtr = *(uint**)(*(int*)(thisPtr + 0x14) + 0xc); // load instruction pointer from frame
    // Load global variable base from context
    local_38 = *(int*)(*(int*)(*(int*)(thisPtr + 0xc) + -4) + 0xc) + 8; // pointer to global var storage
    exprDest = (int*)(*(int*)(thisPtr + 0xc) + 0); // initial destination?

    // Main instruction loop
LAB_00634890:
    do {
        opcodeWord = *codePtr;
        codePtr++; // advance instruction pointer

        // Check for yield condition
        if ((*(byte*)(thisPtr + 0x30) & 0xc) != 0)
        {
            iVar12 = *(int*)(thisPtr + 0x38) - 1;
            *(int*)(thisPtr + 0x38) = iVar12;
            if ((iVar12 == 0) || ((*(byte*)(thisPtr + 0x30) & 4) != 0))
            {
                // Yield if counter expired or forced yield flag set
                FUN_00633a00(); // Perform yield
                if ((*(byte*)(*(int*)(thisPtr + 0x14) + 8) & 0x10) != 0)
                {
                    // If interrupted, save instruction pointer and return
                    *(uint**)(*(int*)(thisPtr + 0x14) + 0xc) = codePtr - 1;
                    *(undefined4*)(*(int*)(thisPtr + 0x14) + 8) = 0x18; // set state "paused"
                    return (int*)0x0;
                }
            }
        }

        // Decode operand fields
        localVarBase = *(int**)(thisPtr + 0xc);
        op1 = (int*)((int)opcodeWord >> 0x18); // high 8 bits: register/offset?
        opAddr = (int*)((int)op1 * 8); // scale for address
        ptr = (int*)((int)opAddr + (int)localVarBase); // compute destination cell
        uint opcode = opcodeWord & 0x3f; // low 6 bits: operation code
        dest = ptr; // destination pointer
        opAddr2 = op1;
    } while (0x22 < opcode); // skip if opcode > 0x22 (invalid? loop until valid opcode?)

    // Extract fields from opcode word
    uVar13 = (int)opcodeWord >> 0xf; // bits 15-? for sub-operand
    uVar7 = (int)opcodeWord >> 6; // bits 6-14 for register/offset

    switch (opcode)
    {
    case 0: // OP_COPY_LOCAL_TO_LOCAL
        *ptr = localVarBase[(uVar13 & 0x1ff) * 2];
        ptr[1] = localVarBase[(uVar13 & 0x1ff) * 2 + 1];
        goto LAB_00634890;

    case 1: // OP_COPY_GLOBAL_TO_LOCAL
        *ptr = *(int*)(local_38 + (uVar7 & 0x3ffff) * 8);
        ptr[1] = *(int*)(local_38 + (uVar7 & 0x3ffff) * 8 + 4);
        goto LAB_00634890;

    case 2: // OP_LOAD_INTEGER
        *ptr = 1;
        ptr[1] = uVar13 & 0x1ff;
        if ((opcodeWord & 0x7fc0) != 0)
        {
            codePtr++; // extra operand (immediate value)
        }
        goto LAB_00634890;

    case 3: // OP_ZERO_RANGE
        // Zero out a range of local variables from (uVar13&0x1ff) down to ptr's destination
        op1 = localVarBase + (uVar13 & 0x1ff) * 2;
        do {
            *op1 = 0;
            op1 = op1 - 2;
        } while (ptr <= op1);
        goto LAB_00634890;

    case 4: // OP_LOAD_FROM_OBJECT_FIELD
        {
            int* fieldPtr = *(int**)(*(int*)(*(int*)(thisPtr + 0x18 + (uVar13 & 0x1ff) * 4)) + 8);
            *ptr = *fieldPtr;
            ptr[1] = fieldPtr[1];
            goto LAB_00634890;
        }

    case 5: // OP_GET_MEMBER
        {
            int* memberTable = (int*)(local_38 + (uVar7 & 0x3ffff) * 8);
            int* memberSearch = (int*)(*(int*)(*(int*)(local_38 + 0x14) + 0x10) +
                ((1 << (*(byte*)(*(int*)(local_38 + 0x14) + 7) & 0x1f)) - 1U &
                *(uint*)(memberTable[1] + 8)) * 0x14);
            do {
                if ((*memberSearch == 4) && (memberSearch[1] == memberTable[1]))
                {
                    if (memberSearch[2] != 0)
                    {
                        *ptr = memberSearch[2];
                        ptr[1] = memberSearch[3];
                        goto LAB_00634890;
                    }
                    break;
                }
                memberSearch = (int*)memberSearch[4];
            } while (memberSearch != (int*)0x0);

            iVar12 = *(int*)(*(int*)(local_38 + 0x14) + 8);
            if ((*(byte*)(iVar12 + 6) & 1) == 0)
            {
                iVar14 = *(int*)(*(int*)(thisPtr + 0x10) + 0x54);
                int* search2 = (int*)(*(int*)(iVar12 + 0x10) +
                    ((1 << (*(byte*)(iVar12 + 7) & 0x1f)) - 1U & *(uint*)(iVar14 + 8)) * 0x14);
                do {
                    if ((*search2 == 4) && (search2[1] == iVar14))
                    {
                        search2 = search2 + 2;
                        if (*search2 != 0) goto LAB_00634a58;
                        break;
                    }
                    search2 = (int*)search2[4];
                } while (search2 != (int*)0x0);
                *(byte*)(iVar12 + 6) = *(byte*)(iVar12 + 6) | 1;
            }
            int* result2 = (int*)0x0;
LAB_00634a58:
            if (result2 == (int*)0x0)
            {
                int* defaultResult = &DAT_00e2a93c; // static nil/error value
            }
            else if (*result2 == 6)
            {
                FUN_00633ac0(thisPtr, result2, local_38 + 0x10, memberTable);
                int* resultAddr = *(int**)(thisPtr + 8);
            }
            else
            {
                int* resultAddr = (int*)FUN_00633cb0(thisPtr, result2, memberTable, 0);
            }
            // write result to dest
            goto LAB_00634a8b;
        }

    case 6: // OP_BINARY_OP (arithmetic/comparison?)
        uVar7 = uVar7 & 0x1ff;
        int* srcVal1 = localVarBase + (uVar13 & 0x1ff) * 2;
        if (uVar7 < 0xfa)
        {
            int* srcVal2 = localVarBase + uVar7 * 2;
        }
        else
        {
            int* srcVal2 = (int*)(local_38 + -2000 + uVar7 * 8); // global window
        }
        if (*srcVal1 == 5)
        {
            if (*srcVal2 == 3)
            {
                if ((float)(int)(float)srcVal2[1] != (float)srcVal2[1]) goto LAB_00634b51;
                op1 = (int*)FUN_00637f10(); // get builtin function?
            }
            else if (*srcVal2 == 4)
            {
                int* resolved = (int*)(*(int*)(srcVal1[1] + 0x10) +
                    ((1 << (*(byte*)(srcVal1[1] + 7) & 0x1f)) - 1U & *(uint*)(srcVal2[1] + 8)) * 0x14);
                do {
                    if ((*resolved == 4) && (resolved[1] == srcVal2[1]))
                    {
                        resolved = resolved + 2;
                        goto LAB_00634b5c;
                    }
                    resolved = (int*)resolved[4];
                } while (resolved != (int*)0x0);
                resolved = &DAT_00e2a93c;
            }
            else
            {
LAB_00634b51:
                op1 = (int*)FUN_00637ea0(); // error? 
            }
LAB_00634b5c:
            if (*op1 == 0)
            {
                int* result = (int*)FUN_00633bc0(thisPtr, srcVal1, srcVal2, 0);
                goto LAB_00634a8b;
            }
            *dest = *op1;
            dest[1] = op1[1];
            goto LAB_00634890;
        }
        // else case: call generic binary op
        int* result = (int*)FUN_00633c30(srcVal1, srcVal2, 0);
        goto LAB_00634a8b;

    case 7: // OP_STORE_GLOBAL_TO_LOCAL? (inverse of assign?)
        FUN_00633d60(local_38 + 0x10, local_38 + (uVar7 & 0x3ffff) * 8, ptr);
        goto LAB_00634890;

    case 8: // OP_COPY_TO_OBJECT
        op1 = *(int**)(*(int*)(local_38 + 0x18 + (uVar13 & 0x1ff) * 4) + 8);
        *op1 = *ptr;
        op1[1] = ptr[1];
        goto LAB_00634890;

    case 9: // OP_ASSIGN_LOCAL_TO_LOCAL? (indirect copy)
        uVar7 = uVar7 & 0x1ff;
        if (uVar7 < 0xfa)
        {
            int* src = localVarBase + uVar7 * 2;
        }
        else
        {
            int* src = (int*)(local_38 + -2000 + uVar7 * 8);
        }
        uVar13 = uVar13 & 0x1ff;
        if (uVar13 < 0xfa)
        {
            FUN_00633d60(ptr, localVarBase + uVar13 * 2, src);
        }
        else
        {
            FUN_00633d60(ptr, local_38 + -2000 + uVar13 * 8, src);
        }
        goto LAB_00634890;

    case 10: // OP_MAKE_STRING?
        *ptr = 5;
        iVar12 = FUN_00637c50((uVar13 & 7) << ((byte)((int)(uVar13 & 0x1ff) >> 3) & 0x1f), uVar7 & 0x1ff);
        ptr[1] = iVar12;
        goto LAB_00634c7c;

    case 0xb: // OP_GET_MEMBER2? (similar to case 5?)
        uVar7 = uVar7 & 0x1ff;
        int* src1 = localVarBase + (uVar13 & 0x1ff) * 2;
        int* src2;
        if (uVar7 < 0xfa)
        {
            src2 = localVarBase + uVar7 * 2;
        }
        else
        {
            src2 = (int*)(local_38 + -2000 + uVar7 * 8);
        }
        if (*src2 != 4)
        {
            return (int*)0x0;
        }
        ptr[2] = *src1;
        ptr[3] = src1[1];
        if (*src1 == 5)
        {
            int* resolved2 = (int*)(*(int*)(src1[1] + 0x10) +
                ((1 << (*(byte*)(src1[1] + 7) & 0x1f)) - 1U & *(uint*)(src2[1] + 8)) * 0x14);
            do {
                if ((*resolved2 == 4) && (resolved2[1] == src2[1]))
                {
                    if (resolved2[2] != 0)
                    {
                        *ptr = resolved2[2];
                        ptr[1] = resolved2[3];
                        goto LAB_00634890;
                    }
                    break;
                }
                resolved2 = (int*)resolved2[4];
            } while (resolved2 != (int*)0x0);
            int* result3 = (int*)FUN_00633bc0(thisPtr, src1, src2, 0);
        }
        else
        {
            int* result3 = (int*)FUN_00633c30(src1, src2, 0);
        }
        // write result to current cell
LAB_00634a8b:
        int* writeAddr = (int*)(*(int*)(thisPtr + 0xc) + (int)opAddr);
        *writeAddr = *result3;
        writeAddr[1] = result3[1];
        goto LAB_00634890;

    case 0xc: // OP_ADD
        uVar13 = uVar13 & 0x1ff;
        int* a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        uVar7 = uVar7 & 0x1ff;
        int* a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        if ((*a1 == 3) && (*a2 == 3))
        {
            *ptr = 3;
            ptr[1] = (int)((float)a2[1] + (float)a1[1]);
        }
        else
        {
            FUN_00634660(thisPtr, a1, a2, 5); // generic add
        }
        goto LAB_00634890;

    case 0xd: // OP_SUB
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        if ((*a1 == 3) && (*a2 == 3))
        {
            *ptr = 3;
            ptr[1] = (int)((float)a1[1] - (float)a2[1]);
        }
        else
        {
            FUN_00634660(thisPtr, a1, a2, 6); // generic sub
        }
        goto LAB_00634890;

    case 0xe: // OP_MUL
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        if ((*a1 == 3) && (*a2 == 3))
        {
            *ptr = 3;
            ptr[1] = (int)((float)a2[1] * (float)a1[1]);
        }
        else
        {
            FUN_00634660(thisPtr, a1, a2, 7); // generic mul
        }
        goto LAB_00634890;

    case 0xf: // OP_DIV
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        if ((*a1 == 3) && (*a2 == 3))
        {
            *ptr = 3;
            ptr[1] = (int)((float)a1[1] / (float)a2[1]);
        }
        else
        {
            FUN_00634660(thisPtr, a1, a2, 8); // generic div
        }
        goto LAB_00634890;

    case 0x10: // OP_MOD? Or comparison?
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        FUN_00634660(thisPtr, a1, a2, 9); // generic?
        goto LAB_00634890;

    case 0x11: // OP_NEGATE
        a1 = localVarBase + (uVar13 & 0x1ff) * 2;
        if (*a1 != 3)
        {
            if ((*a1 != 4) || (iVar12 = FUN_00636850(&intValue), iVar12 == 0))
            {
                intArr[1] = 0;
                iVar12 = FUN_00633f00(thisPtr, a1, intArr + 1, dest, 10);
                if (iVar12 == 0)
                {
                    opAddr2 = intArr + 1;
                    if ((*a1 != 3) && ((*a1 != 4 || (iVar12 = FUN_00636850(&opAddr), iVar12 == 0))))
                    {
                        opAddr2 = a1;
                    }
                    FUN_006336f0("perform arithmetic on");
                }
                goto LAB_00634890;
            }
            intArr[1] = 3;
            intArr[2] = intValue;
            a1 = intArr + 1;
        }
        fVar16 = DAT_00e44564; // constant 0.0?
        *dest = 3;
        dest[1] = (int)(fVar16 - (float)a1[1]); // negate: 0 - value
        goto LAB_00634890;

    case 0x12: // OP_NOT (logical NOT)
        iVar12 = localVarBase[(uVar13 & 0x1ff) * 2];
        if ((iVar12 == 0) || ((iVar12 == 1 && ((localVarBase + (uVar13 & 0x1ff) * 2)[1] == 0))))
        {
            *ptr = 1;
            ptr[1] = 1; // true
        }
        else
        {
            *ptr = 1;
            ptr[1] = 0; // false
        }
        goto LAB_00634890;

    case 0x13: // OP_JUMP? Actually shift range?
        uVar13 = uVar13 & 0x1ff;
        FUN_006343b0(thisPtr, ((uVar7 & 0x1ff) - uVar13) + 1, uVar7 & 0x1ff);
        iVar12 = *(int*)(thisPtr + 0xc);
        *(undefined4*)((int)opAddr + iVar12) = *(undefined4*)(iVar12 + uVar13 * 8);
        *(undefined4*)((int)opAddr + iVar12 + 4) = *(undefined4*)(iVar12 + 4 + uVar13 * 8);
        // Fall through to label

    case 10: // (note: case 10 jumps to same label as 0x13 after assignment)
LAB_00634c7c:
        // Check for stack overflow
        if (*(uint*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint*)(*(int*)(thisPtr + 0x10) + 0x24))
        {
            uint prevState = FUN_00627290();
            FUN_00626f80(thisPtr, 0);
            FUN_00626fd0(0);
            FUN_00626f80(thisPtr, 0);
            FUN_00627010(prevState);
            FUN_006270e0();
        }
        goto LAB_00634890;

    case 0x14: // OP_JUMP_BACK? (relative jump back by (uVar7 & 0x3ffff) - 0x1ffff)
        codePtr = codePtr + ((uVar7 & 0x3ffff) - 0x1ffff);
        goto LAB_00634890;

    case 0x15: // OP_EQUAL
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        if (*a1 == *a2)
        {
            // compare values; if equal, check type
            if (uVar7 < 0xfa)
            {
                a2 = localVarBase + uVar7 * 2;
            }
            else
            {
                a2 = (int*)(local_38 + -2000 + uVar7 * 8);
            }
            iVar12 = FUN_006342e0(thisPtr, a2);
            if (iVar12 == 0) goto LAB_006351f0;
            result = (int*)0x1;
        }
        else
        {
LAB_006351f0:
            result = (int*)0x0;
        }
        if (result != opAddr2)
        {
            codePtr++; // skip next instruction if not equal? (condition branch)
        }
        goto LAB_00634890;

    case 0x16: // OP_NOT_EQUAL?
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        result = (int*)FUN_00634150(a2);
        if (result != opAddr2)
        {
            codePtr++; // skip? branch
        }
        goto LAB_00634890;

    case 0x17: // OP_LESS? (comparison)
        uVar7 = uVar7 & 0x1ff;
        a2 = (uVar7 < 0xfa) ? (localVarBase + uVar7 * 2) : ((int*)(local_38 + -2000 + uVar7 * 8));
        uVar13 = uVar13 & 0x1ff;
        a1 = (uVar13 < 0xfa) ? (localVarBase + uVar13 * 2) : ((int*)(local_38 + -2000 + uVar13 * 8));
        result = (int*)FUN_00634200(a1, a2);
        if (result != opAddr2)
        {
            codePtr++; // skip? branch
        }
        goto LAB_00634890;

    case 0x18: // OP_IF (conditional branch)
        a1 = localVarBase + (uVar13 & 0x1ff) * 2;
        iVar12 = *a1;
        if ((iVar12 == 0) || ((iVar12 == 1 && (a1[1] == 0))))
        {
            uint cond = 1; // false
        }
        else
        {
            uint cond = 0; // true
        }
        if (cond == (uVar7 & 0x1ff))
        {
            codePtr++; // skip branch? (no jump)
            goto LAB_00634890;
        }
        // else: take branch? Actually fall through to set destination
        *ptr = iVar12;
        ptr[1] = a1[1];
        break; // then jump to the default case offset adjustment? (fall through to main offset)

    // default case handles many other opcodes (0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22)
    // We'll include cleanup at the end.

    default:
        // For opcodes other than those handled explicitly (0-0x18 with explicit cases)
        // This handles opcodes 0x19-0x22 plus default
        // Many of these involve function calls, stack frame management, etc.
        // We'll keep a simplified version.

        if ((uVar13 & 0x1ff) != 0)
        {
            *(int**)(thisPtr + 8) = ptr + (uVar13 & 0x1ff) * 2;
        }
        opAddr2 = (int*)((uVar7 & 0x1ff) - 1);
        uint flags = FUN_00636050(ptr);
        if (flags == 0)
        {
            // Handle opcode 0x19 specifically? (conditional or function return?)
            if (((byte)opcodeWord & 0x3f) == 0x19)
            {
                // Return from function?
                *(uint**)(*(int*)(thisPtr + 0x14) + -0xc) = codePtr;
                *(undefined4*)(*(int*)(thisPtr + 0x14) + -0x10) = 0xc;
            }
            else
            {
                // Pop stack frame
                iVar12 = *(int*)(*(int*)(thisPtr + 0x14) + -0x18);
                int* frameBase = (int*)(iVar12 + (int)op1 * 8);
                if (*(int*)(thisPtr + 0x48) != 0)
                {
                    FUN_006382a0();
                }
                iVar14 = 0;
                if (frameBase < *(int**)(thisPtr + 8))
                {
                    iVar9 = 0;
                    result = frameBase;
                    do {
                        *(int*)(iVar9 - 8 + iVar12) = *result;
                        *(int*)(iVar9 - 4 + iVar12) = result[1];
                        iVar14++;
                        iVar9 = iVar14 * 8;
                        result = frameBase + iVar14 * 2;
                    } while (result < *(int**)(thisPtr + 8));
                }
                iVar12 = iVar12 + iVar14 * 8;
                *(int*)(thisPtr + 8) = iVar12;
                *(int*)(*(int*)(thisPtr + 0x14) + -0x14) = iVar12;
                *(undefined4*)(*(int*)(thisPtr + 0x14) + -0xc) = *(undefined4*)(*(int*)(thisPtr + 0x14) + 0xc);
                int* stackDepth = (int*)(*(int*)(thisPtr + 0x14) + -4);
                *stackDepth = *stackDepth + 1;
                *(undefined4*)(*(int*)(thisPtr + 0x14) + -0x10) = 8;
                *(int*)(thisPtr + 0x14) = *(int*)(thisPtr + 0x14) - 0x18;
                *(undefined4*)(thisPtr + 0xc) = **(undefined4**)(thisPtr + 0x14);
            }
            goto LAB_00634840; // restart execution loop with new frame
        }
        // If flags != 0, check if stack space available
        if (*(uint*)(thisPtr + 8) < flags)
        {
            *(uint**)(*(int*)(thisPtr + 0x14) + -0xc) = codePtr;
            *(undefined4*)(*(int*)(thisPtr + 0x14) + -0x10) = 8;
            return (int*)0x0; // need more space, return
        }
        FUN_00636260(thisPtr);
        if (-1 < (int)opAddr2)
        {
            *(undefined4*)(thisPtr + 8) = *(undefined4*)(*(int*)(thisPtr + 0x14) + 4);
        }
        goto LAB_00634890;
    }

    // After conditional opcodes that fall through (e.g., case 0x18)
    // Adjust instruction pointer by relative offset from next word
    codePtr = codePtr + (((int)*codePtr >> 6 & 0x3ffffU) - 0x1fffe);
    goto LAB_00634890;

    // Cases for opcode 0x1b (switch case)
switchD_006348ed_caseD_1b:
    {
        ptr = (int*)(*(int*)(thisPtr + 0x14) + -0x18);
        if ((uVar13 & 0x1ff) != 0)
        {
            *(int**)(thisPtr + 8) = ptr + (uVar13 & 0x1ff) * 2 - 2;
        }
        if (*(int*)(thisPtr + 0x48) != 0)
        {
            FUN_006382a0();
        }
        *(undefined4*)(*(int*)(thisPtr + 0x14) + 8) = 8;
        *(uint**)(*(int*)(thisPtr + 0x14) + 0xc) = codePtr;
        if ((*(byte*)(ptr + 2) & 4) == 0)
        {
            return ptr; // return some value?
        }
        iVar12 = *(int*)(ptr[3] + -4);
        FUN_00636260(thisPtr);
        if (-1 < (int)((iVar12 >> 6 & 0x1ffU) - 1))
        {
            *(undefined4*)(thisPtr + 8) = *(undefined4*)(*(int*)(thisPtr + 0x14) + 4);
        }
        goto LAB_0063485e;
    }

    // Cases for opcode 0x22 (function call with arguments)
switchD_006348ed_caseD_22:
    {
        int* tableEntry = *(int**)(*(int*)(*(int*)(local_38 + 0xc) + 0x10) + (uVar7 & 0x3ffff) * 4);
        int argCount = (uint)*(byte*)(tableEntry + 0x11);
        int* funcObj = (int*)FUN_00638190((int*)argCount, local_38 + 0x10);
        funcObj[3] = (int)tableEntry;
        if (0 < argCount)
        {
            int* argDest = funcObj + 6;
            do {
                uint argOpcode = *codePtr;
                if (((byte)argOpcode & 0x3f) == 4)
                {
                    *argDest = *(int*)(local_38 + 0x18 + (argOpcode >> 0xf & 0x1ff) * 4);
                }
                else
                {
                    iVar12 = FUN_00638220(localVarBase + (argOpcode >> 0xf & 0x1ff) * 2);
                    *argDest = iVar12;
                }
                argDest++;
                codePtr++;
                argCount--;
            } while (argCount != 0);
        }
        *ptr = 6; // type: function?
        ptr[1] = (int)funcObj;
        // Check stack size
        if (*(uint*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint*)(*(int*)(thisPtr + 0x10) + 0x24))
        {
            int* prevState = (int*)FUN_00627290();
            FUN_00626f80(thisPtr, 0);
            iVar12 = 0;
            if (0 < *(int*)(*(int*)(thisPtr + 0x10) + 8))
            {
                do {
                    iVar14 = *(int*)(thisPtr + 0x10);
                    iVar9 = FUN_00626f80(thisPtr, 0);
                    int* stackUsed = (int*)(iVar14 + 4);
                    *stackUsed = *stackUsed - iVar9;
                    iVar12++;
                } while (iVar12 < *(int*)(*(int*)(thisPtr + 0x10) + 8));
            }
            FUN_00626f80(thisPtr, 0);
            FUN_00627010(prevState);
            FUN_006270e0();
        }
        goto LAB_00634890;
    }

    // The switch includes direct jumps to labels that are not shown in this simplified reconstruction.
    // The actual code handles opcodes 0x19-0x22 via fallthrough to default and then separate sections.
    // We'll omit the duplicated default case that was already presented.

    return (int*)0x0;
}