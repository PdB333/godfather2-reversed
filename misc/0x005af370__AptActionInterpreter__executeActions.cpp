// FUNC_NAME: AptActionInterpreter::executeActions
int* __thiscall AptActionInterpreter::executeActions(AptActionInterpreter* this, int* bytecode, AptContext* context, int maxRegisters)
{
    char* string;
    code* funcPtr;
    bool bVar3;
    bool bVar4;
    char cVar5;
    int* piVar6;
    uint uVar7;
    int* piVar8;
    undefined4 uVar9;
    uint* puVar10;
    int iVar11;
    char* pcVar12;
    uint* puVar13;
    undefined4* puVar14;
    undefined4 uVar15;
    char* pcVar16;
    int iVar17;
    int fsOffset;
    float10 fVar18;
    float in_XMM0;
    float fVar19;
    uint* puStack_314;
    uint* puStack_310;
    int* local_308;
    float fStack_300;
    int local_2fc;
    undefined4 uStack_2f8;
    float fStack_2f4;
    char* local_2f0;
    char* local_2ec;
    undefined4 local_2e8;
    int local_2e4;
    undefined1* local_2e0;
    float fStack_2dc;
    float fStack_2d8;
    float fStack_2d4;
    float fStack_2d0;
    float fStack_2cc;
    float fStack_2c8;
    float fStack_2c4;
    float fStack_2bc;
    float fStack_2b8;
    undefined1* puStack_2b4;
    char* pcStack_2b0;
    undefined4 uStack_2ac;
    undefined4 uStack_2a8;
    undefined* puStack_2a4;
    undefined1* puStack_2a0;
    char* pcStack_29c;
    undefined4 uStack_298;
    undefined4 uStack_294;
    undefined* puStack_290;
    undefined1* puStack_28c;
    char* pcStack_288;
    undefined4 uStack_284;
    undefined4 uStack_280;
    undefined* puStack_27c;
    undefined1 auStack_278[28];
    undefined1 auStack_25c[28];
    undefined1 auStack_240[8];
    undefined4 uStack_238;
    undefined1 auStack_224[8];
    undefined4 uStack_21c;
    undefined1 auStack_208[256];
    undefined1 auStack_108[260];

    local_308 = bytecode;
    local_2fc = 0;
    if (maxRegisters == -1) {
        pushRegisterContext(context);
    }
    pushValueToStack(context, 0, "super", 1, 1);
    piVar6 = local_308;
opcodeLoop:
    local_308 = piVar6;
    iVar11 = *local_308;
    piVar6 = (int*)((int)local_308 + 1);
    if (local_2fc != 0) {
exitLabel:
        if (maxRegisters == -1) {
            popRegisterContext();
        }
        return piVar6;
    }
    if ((char)iVar11 == '\0') {
        if (maxRegisters >= 0) {
popStackAndExit:
            popStack(this);
        }
        goto exitLabel;
    }
    if ((maxRegisters >= 0) && (maxRegisters < (int)piVar6 - (int)bytecode)) goto popStackAndExit;
    if ((context != (uint*)0x0) && (*(short*)((int)context + 2) == 0)) {
        local_2f0 = "pCurrentContext == 0 || pCurrentContext->getRefCount() > 0";
        local_2ec = "..\\source\\Apt\\AptActionInterpreter.cpp";
        local_2e8 = 0x6bd;
        local_2e4 = 2;
        local_2e0 = &DAT_01128ffb;
        if (DAT_01128ffb != '\0') {
            piVar8 = *(int**)(**(int**)(fsOffset + 0x2c) + 0x30);
            uVar7 = 1;
            if (((piVar8 == (int*)0x0) ||
                 (uVar7 = (**(code**)(*piVar8 + 8))(&local_2f0, "pCurrentContext == 0 || pCurrentContext->getRefCount() > 0"),
                  local_2e0 != (undefined1*)0x0)) && ((uVar7 & 2) != 0)) {
                *local_2e0 = 0;
            }
            if (((piVar8 != (int*)0x0) || (local_2e4 != 4)) &&
                (((uVar7 & 1) != 0) || ((local_2e4 == 0) || (local_2e4 == 1)))) {
                funcPtr = (code*)swi(3);
                piVar6 = (int*)(*funcPtr)();
                return piVar6;
            }
        }
    }
    switch ((char)iVar11) {
    case 0x07: // Opcode 7: maybe 'push' or something
        if (((~((byte)(*context >> 0xf) & 1) == 0) && (cVar5 = isDebugModeEnabled(), cVar5 == '\0')) {
            enableTrace();
            iVar11 = getTraceOutput();
            *(uint*)(iVar11 + 0x14) = *(uint*)(iVar11 + 0x14) & 0xfeffffff;
        }
        goto opcodeLoop;
    default:
        puStack_2a0 = &DAT_00e36da0; // Error message string
        pcStack_29c = "..\\source\\Apt\\AptActionInterpreter.cpp";
        uStack_298 = 0xdce;
        uStack_294 = 2;
        puStack_290 = &DAT_01128ffe;
        FatalError();
    case 0x09: // Tab - NOP?
    case 0x8a: // -0x76 = 0x8a? Actually -118 signed -> 0x8A
        goto opcodeLoop;
    case 0x0B: // '\v' - Vertical tab: Add?
        readValue(0);
        readValue(1);
        pushFloatFromStack();
        fStack_2bc = in_XMM0;
        pushFloatFromStack();
        fStack_2dc = in_XMM0;
        popStack();
        popStack();
        puVar13 = (uint*)(*gAlloc)(8, 0);
        if (puVar13 != (uint*)0x0) {
            in_XMM0 = fStack_2dc - fStack_2bc;
            *puVar13 = *puVar13 & 0xffff8006 | 6;
            *(undefined2*)((int)puVar13 + 2) = 0;
            *puVar13 = *puVar13 | 0x8000;
            puVar13[1] = (uint)in_XMM0;
            popStack(this);
            goto opcodeLoop;
        }
        break;
    case 0x0C: // '\f' - Multiply?
        readValue(0);
        readValue(1);
        puVar13 = (uint*)(*gAlloc)(8, 0);
        if (puVar13 != (uint*)0x0) {
            pushFloatFromStack();
            fVar19 = in_XMM0;
            pushFloatFromStack();
            *puVar13 = *puVar13 & 0xffff8006 | 6;
            *(undefined2*)((int)puVar13 + 2) = 0;
            *puVar13 = *puVar13 | 0x8000;
            in_XMM0 = in_XMM0 * fVar19;
            puVar13[1] = (uint)in_XMM0;
        }
        goto LAB_005afa10;
    case 0x0D: // '\r' - Divide?
        readValue(0);
        readValue(1);
        pushFloatFromStack();
        fStack_2d8 = in_XMM0;
        if ((in_XMM0 != 0.0f) &&
            (puVar13 = (uint*)(*gAlloc)(8, 0), puVar13 != (uint*)0x0)) {
            pushFloatFromStack();
            in_XMM0 = in_XMM0 / fStack_2d8;
            *puVar13 = *puVar13 & 0xffff8006 | 6;
            *(undefined2*)((int)puVar13 + 2) = 0;
            *puVar13 = *puVar13 | 0x8000;
            puVar13[1] = (uint)in_XMM0;
        }
        goto LAB_005afa10;
    case 0x0F: // Min?
        readValue(0);
        readValue(1);
        iVar11 = (*gAlloc)(8, 0);
        if (iVar11 != 0) {
            pushFloatFromStack();
            fVar19 = in_XMM0;
            pushFloatFromStack();
            if (fVar19 <= in_XMM0) {
                popFloatResult();
                in_XMM0 = fVar19;
            } else {
                popFloatResult();
                in_XMM0 = fVar19;
            }
        }
        goto LAB_005afa10;
    case 0x12: // Increment?
        readValue(0);
        pushFloatFromStack();
        fStack_2c4 = in_XMM0;
        popStack();
        iVar11 = (*gAlloc)(8, 0);
        if (iVar11 != 0) {
            in_XMM0 = fStack_2c4;
            if (fStack_2c4 == 0.0f) {
                popFloatResult();
                popStack(this);
            } else {
                popFloatResult();
                popStack(this);
            }
            goto opcodeLoop;
        }
        break;
    case 0x17: // To integer?
        goto switchD_005af4a2_caseD_17;
    case 0x18: // Convert to string?
        readValue(0);
        pushStringFromStack();
        popStack();
        iVar11 = (*gAlloc)(8, 0);
        if (iVar11 != 0) {
            popStringResult();
            popStack(this);
            goto opcodeLoop;
        }
        break;
    case 0x1C: // NewObject?
        puVar13 = (uint*)readValue(0);
        if ((~((byte)(*puVar13 >> 0xf) & 1) == 0) {
            uVar15 = getStringFromValue(auStack_208, 0x100);
            pushValueToStack(context, 0, uVar15, 1, 1);
            popStack();
            popStack(this);
        }
        goto opcodeLoop;
    case 0x1D: // NewObject with arguments?
        uVar15 = readValue(0);
        readValue(1);
        uVar9 = getStringFromValue(auStack_208, 0x100);
        setVariable(context, 0, uVar9, uVar15, 1, 1);
        popStack();
        popStack();
        goto opcodeLoop;
    case 0x21: // Not?
        uVar15 = readValue(0);
        uVar9 = readValue(1);
        logicalNot(uVar15, uVar9);
        goto LAB_005afa10;
    case 0x22: // Get member?
        readValue(0);
        readValue(1);
        getMember(context, 0);
defaultSwitch:
        popStack();
        popStack();
        goto LAB_005af94e;
    case 0x23: // Set member?
        readValue(0);
        readValue(1);
        readValue(2);
        getMember(context, 0);
        pushStringFromStack();
        popStack();
        popStack();
        popStack();
        goto opcodeLoop;
    case 0x26: // Trace?
        readValue(0);
        uVar15 = getStringFromValue(auStack_208, 0x100);
        (*gTrace)("AptTrace: %s\n", uVar15);
        popStack();
        goto opcodeLoop;
    case 0x3A: // ':' - GetURL?
        readValue(0);
        uVar15 = readValue(1);
        cVar5 = isDebuggerActive(0);
        if ((cVar5 != '\0') || (cVar5 = isDebuggerSupported(), cVar5 != '\0')) {
            uVar9 = getStringFromValue(auStack_208, 0x100);
            setVariable(uVar15, 0, uVar9, 0, 1, 1);
        }
        popStack();
        popStack();
        iVar11 = isActionInterrupted();
        if (iVar11 != 0) {
            popStringResult();
            popStack(this);
            goto opcodeLoop;
        }
        break;
    case 0x3C: // '<' - GetVariable?
        uVar15 = readValue(0);
        readValue(1);
        iVar11 = getCurrentScope();
        setVariable(context, 0, *(undefined4*)(iVar11 + 0xc), uVar15, 0, 1);
        popStack();
        popStack();
        goto opcodeLoop;
    case 0x3D: // '=' - SetVariable?
        puStack_310 = (uint*)readValue(0);
        readValue(1);
        uVar15 = pushStringFromStack();
        beginActionBlock();
        cVar5 = isTraceEnabled();
        if (((cVar5 != '\0') &&
             (iVar11 = getTraceOutput(), puStack_310 = (uint*)gDefaultValue, 0 < *(int*)(iVar11 + 0x54))) &&
            (**(int**)(iVar11 + 0x4c) != 0)) {
            puStack_310 = (uint*)**(int**)(iVar11 + 0x4c);
        }
        cVar5 = isInFunction();
        if (cVar5 != '\0') {
            iVar11 = getCurrentScope();
            callMethodWithArgs(context, 0, *(undefined4*)(iVar11 + 0xc), auStack_240);
            puStack_310 = (uint*)pushValueToStack(0, 0, uStack_238, 1, 1);
        }
        endActionBlock();
        popStack();
        popStack();
        setProperty(context, uVar15);
        (**(code**)(&gTypeVtables + (*puStack_310 & 0x7fff) * 4))(puStack_310);
        popDynamicVariable();
        goto opcodeLoop;
    case 0x3E: // '>' - Return?
        local_2fc = 1;
        goto opcodeLoop;
    case 0x3F: // '?' - Random?
        readValue(0);
        readValue(1);
        pushFloatFromStack();
        fStack_2cc = in_XMM0;
        if ((in_XMM0 != 0.0f) &&
            (puVar13 = (uint*)(*gAlloc)(8, 0), puVar13 != (uint*)0x0)) {
            pushFloatFromStack();
            *puVar13 = *puVar13 & 0xffff8006 | 6;
            *(undefined2*)((int)puVar13 + 2) = 0;
            *puVar13 = *puVar13 | 0x8000;
            fStack_2b8 = in_XMM0;
            fVar18 = (float10)random();
            puVar13[1] = (uint)(float)fVar18;
        }
        goto LAB_005afa10;
    case 0x40: // '@' - CallMethod?
        readValue(0);
        readValue(1);
        getStringFromValue(auStack_208, 0x100);
        uVar15 = pushStringFromStack();
        popStack();
        popStack();
        puVar13 = (uint*)resolveValue(this, context, uVar15);
        if (puVar13 == (uint*)0x0) {
LAB_005af94e:
            popStack(this);
        } else {
            popStack(this);
            (**(code**)(&gTypeVtables + (*puVar13 & 0x7fff) * 4))(puVar13);
        }
        goto opcodeLoop;
    case 0x41: // 'A' - Add2?
        readValue(0);
        iVar11 = getCurrentScope();
        puVar13 = (uint*)pushValueToStack(context, 0, *(undefined4*)(iVar11 + 0xc), 0, 1);
        if ((~((byte)(*puVar13 >> 0xf) & 1) != 0) {
            iVar11 = getCurrentScope();
            setVariable(context, 0, *(undefined4*)(iVar11 + 0xc), gDefaultValue, 0, 1);
        }
switchD_005af4a2_caseD_17:
        popStack();
        goto opcodeLoop;
    case 0x42: // 'B' - CallFunction?
        readValue(0);
        iVar11 = pushStringFromStack();
        popStack();
        iVar17 = isFunctionAvailable();
        if (iVar17 == 0) {
            puStack_314 = (uint*)0x0;
        } else {
            puStack_314 = (uint*)getFunctionObject();
        }
        endActionBlock();
        iVar17 = 0;
        if (0 < iVar11) {
            do {
                uVar15 = readValue(0);
                addFunctionArg(uVar15);
                popStack();
                iVar17 = iVar17 + 1;
            } while (iVar17 < iVar11);
        }
        goto LAB_005b0e86;
    case 0x43: // 'C' - CallMethodWithArgs?
        readValue(0);
        puVar13 = (uint*)pushStringFromStack();
        popStack();
        puVar10 = (uint*)resolveValue(this, context, 0);
        if (puVar10 == (uint*)0x0) {
            if (0 < (int)puVar13) {
                do {
                    popStack();
                    popStack();
                    puVar13 = (uint*)((int)puVar13 + -1);
                } while (puVar13 != (uint*)0x0);
            }
            popStack(this);
        } else {
            puStack_314 = puVar10;
            if (0 < (int)puVar13) {
                do {
                    puStack_314 = puVar13;
                    uVar15 = readValue(0);
                    readValue(1);
                    uVar9 = getStringFromValue(auStack_208, 0x100);
                    callFunctionArgs(puVar10 + 1, uVar9, uVar15);
                    popStack();
                    popStack();
                    puVar13 = (uint*)((int)puStack_314 + -1);
                    puStack_314 = puVar10;
                } while (puVar13 != (uint*)0x0);
            }
LAB_005b0e86:
            popStack(this);
            (**(code**)(&gTypeVtables + (*puStack_314 & 0x7fff) * 4))(puStack_314);
        }
        goto opcodeLoop;
    case 0x47: // 'G' - Add?
        uVar15 = readValue(0);
        uVar9 = readValue(1);
        cVar5 = isInFunction();
        if ((cVar5 != '\0') || (cVar5 = isInFunction(), cVar5 != '\0')) {
            logicalNot(uVar15, uVar9);
            goto LAB_005afa10;
        }
        cVar5 = isNumberType();
        if ((((cVar5 == '\0') && (cVar5 = isNumberType(), cVar5 == '\0')) ||
             (cVar5 = isStringType(), cVar5 != '\0')) || (cVar5 = isStringType(), cVar5 != '\0')) {
            pushFloatFromStack();
            fStack_2d0 = in_XMM0;
            pushFloatFromStack();
            fStack_2d4 = in_XMM0;
            popStack();
            popStack();
            puVar13 = (uint*)(*gAlloc)(8, 0);
            if (puVar13 != (uint*)0x0) {
                in_XMM0 = fStack_2d4 + fStack_2d0;
                *puVar13 = *puVar13 & 0xffff8006 | 6;
                *(undefined2*)((int)puVar13 + 2) = 0;
                *puVar13 = *puVar13 | 0x8000;
                puVar13[1] = (uint)in_XMM0;
                popStack(this);
                goto opcodeLoop;
            }
        } else {
            pushStringFromStack();
            pushStringFromStack();
            popStack();
            popStack();
            iVar11 = (*gAlloc)(8, 0);
            if (iVar11 != 0) {
                popStringResult();
                popStack(this);
                goto opcodeLoop;
            }
        }
        break;
    case 0x48: // 'H' - LessThan?
        readValue(0);
        readValue(1);
        cVar5 = isInFunction();
        if ((cVar5 == '\0') || (cVar5 = isInFunction(), cVar5 == '\0')) {
            cVar5 = isStringType();
            if ((cVar5 == '\0') && (cVar5 = isStringType(), cVar5 == '\0')) {
                pushStringFromStack();
                pushStringFromStack();
            } else {
                pushFloatFromStack();
                pushFloatFromStack();
            }
        } else {
            iVar11 = getCurrentScope();
            pcVar16 = *(char**)(iVar11 + 0xc);
            iVar11 = getCurrentScope();
            stricmp(*(char**)(iVar11 + 0xc), pcVar16);
        }
        goto LAB_005afdd2;
    case 0x49: // 'I' - Equals?
        puVar13 = (uint*)readValue(0);
        puStack_310 = (uint*)readValue(1);
        if ((*puVar13 & 0x7fff) == 0x13) {
            puVar13 = gDefaultValue;
        }
        if ((*puStack_310 & 0x7fff) == 0x13) {
            puStack_310 = gDefaultValue;
        }
        cVar5 = isNumberType();
        if (((((((cVar5 != '\0') || (cVar5 = isStringType(), cVar5 != '\0')) ||
                (cVar5 = isBoolType(), cVar5 != '\0')) || (cVar5 = isInFunction(), cVar5 != '\0')) &&
              (((cVar5 = isNumberType(), cVar5 != '\0' || (cVar5 = isStringType(), cVar5 != '\0')) ||
                ((cVar5 = isBoolType(), cVar5 != '\0' || (cVar5 = isInFunction(), cVar5 != '\0')))))) ||
             (((*puStack_310 ^ *puVar13) & 0x7fff) == 0)) && ((~((byte)(*puVar13 >> 0xf) & 1) == 0)) {
            cVar5 = isNumberType();
            if ((cVar5 == '\0') || (cVar5 = isNumberType(), cVar5 == '\0')) {
                cVar5 = isStringType();
                if ((cVar5 == '\0') || (cVar5 = isStringType(), cVar5 == '\0')) {
                    cVar5 = isInFunction();
                    if ((cVar5 == '\0') || (cVar5 = isInFunction(), cVar5 == '\0')) {
                        cVar5 = isNumberType();
                        if ((cVar5 == '\0') &&
                            (((cVar5 = isStringType(), cVar5 == '\0' && (cVar5 = isNumberType(), cVar5 == '\0'))
                              && (cVar5 = isStringType(), cVar5 == '\0')))) {
                            cVar5 = isInFunction();
                            if ((cVar5 == '\0') || (cVar5 = isBoolType(), cVar5 != '\0')) {
                                cVar5 = isBoolType();
                                if ((cVar5 != '\0') && (cVar5 = isInFunction(), cVar5 == '\0')) {
                                    pushStringFromStack();
LAB_005b0576:
                                    pushStringFromStack();
                                }
                            } else {
                                pcVar16 = (char*)getStringFromValue(auStack_208, 0x100);
                                pcVar12 = (char*)getStringFromValue(auStack_108, 0x100);
                                do {
                                    if (((*pcVar16 != *pcVar12) || (*pcVar16 == '\0')) ||
                                        (pcVar1 = pcVar16 + 1, *pcVar1 != pcVar12[1])) break;
                                    pcVar16 = pcVar16 + 2;
                                    pcVar12 = pcVar12 + 2;
                                } while (*pcVar1 != '\0');
                            }
                        } else {
                            bVar4 = false;
                            bVar3 = false;
                            cVar5 = isInFunction();
                            if ((cVar5 != '\0') || (cVar5 = isStringType(), cVar5 != '\0')) {
                                cVar5 = isStringType();
                                if (cVar5 == '\0') {
                                    iVar11 = getCurrentScope();
                                    pcVar16 = strchr(*(char**)(iVar11 + 0xc), '.');
                                    if (pcVar16 == (char*)0x0) goto LAB_005b05e4;
                                }
                                bVar4 = true;
                            }
LAB_005b05e4:
                            cVar5 = isInFunction();
                            if ((cVar5 != '\0') || (cVar5 = isStringType(), cVar5 != '\0')) {
                                cVar5 = isStringType();
                                if (cVar5 == '\0') {
                                    iVar11 = getCurrentScope();
                                    pcVar16 = strchr(*(char**)(iVar11 + 0xc), '.');
                                    if (pcVar16 == (char*)0x0) goto LAB_005b0625;
                                }
                                bVar3 = true;
                            }
LAB_005b0625:
                            cVar5 = isNumberType();
                            if (cVar5 == '\0') {
                                cVar5 = isNumberType();
                                if (cVar5 == '\0') {
                                    pushFloatFromStack();
                                    fStack_2c8 = in_XMM0;
                                    pushFloatFromStack();
                                    fVar19 = fStack_2c8;
                                } else {
                                    iVar11 = pushStringFromStack();
                                    if (!bVar4) goto LAB_005b0576;
                                    pushFloatFromStack();
                                    fVar19 = in_XMM0;
                                    in_XMM0 = (float)iVar11;
                                }
                                in_XMM0 = (float)((uint)(fVar19 - in_XMM0) & maskFloat);
                            } else {
                                pushStringFromStack();
                                if (bVar3) {
                                    pushFloatFromStack();
                                    in_XMM0 = 1.0f; // True
                                } else {
                                    pushStringFromStack();
                                }
                            }
                        }
                    } else {
                        iVar11 = getCurrentScope();
                        pcVar16 = *(char**)(iVar11 + 0xc);
                        iVar11 = getCurrentScope();
                        pcVar12 = *(char**)(iVar11 + 0xc);
                        do {
                            if (((*pcVar12 != *pcVar16) || (*pcVar12 == '\0')) ||
                                (pcVar1 = pcVar12 + 1, *pcVar1 != pcVar16[1])) break;
                            pcVar12 = pcVar12 + 2;
                            pcVar16 = pcVar16 + 2;
                        } while (*pcVar1 != '\0');
                    }
                } else {
                    pushFloatFromStack();
                    pushFloatFromStack();
                }
            } else {
                pushStringFromStack();
                pushStringFromStack();
            }
        }
        popStack();
        popStack();
        iVar11 = isFloatResult();
        if (iVar11 != 0) {
            popFloatResult();
            popStack(this);
            goto opcodeLoop;
        }
        break;
    case 0x4C: // 'L' - PushDuplicate?
        readValue(0);
        popStack(this);
        goto opcodeLoop;
    case 0x4E: // 'N' - NewObject (complex)?
        puVar13 = (uint*)readValue(0);
        puVar10 = (uint*)readValue(1);
        if (((~((byte)(*puVar10 >> 0xf) & 1) != 0) || ((~((byte)(*puVar13 >> 0xf) & 1) != 0)))
            goto defaultSwitch;
        cVar5 = isTraceEnabled();
        if ((cVar5 != '\0') &&
            ((cVar5 = isNumberType(), cVar5 != '\0' || (cVar5 = isStringType(), cVar5 != '\0')))) {
            getTraceOutput();
            iVar11 = pushStringFromStack();
            puVar13 = gDefaultValue;
            if (iVar11 >= 0) {
                puVar13 = (uint*)getRegisterObject();
            }
            endActionBlock();
            popStack();
            popStack();
            popStack(this);
            (**(code**)(&gTypeVtables + (*puVar13 & 0x7fff) * 4))(puVar13);
            goto opcodeLoop;
        }
        cVar5 = isClassDefined();
        if (cVar5 == '\0') {
            uVar15 = getStringFromValue(auStack_208, 0x100);
            puVar13 = (uint*)pushValueToStack(puVar10, 0, uVar15, 1, 0);
            endActionBlock();
            popStack();
            popStack();
            popStack(this);
            (**(code**)(&gTypeVtables + (*puVar13 & 0x7fff) * 4))(puVar13);
            goto opcodeLoop;
        }
        iVar11 = getCurrentScope();
        cVar5 = (*gClassResolver)(*(undefined4*)(iVar11 + 0xc), &uStack_2f8, &fStack_300);
        fVar19 = fStack_300;
        if (cVar5 == '\0') {
            uStack_2f8 = 0;
        }
        switch (uStack_2f8) {
        case 1:
            iVar11 = (*gAlloc)(0x24, 0);
            if (iVar11 == 0) {
                puStack_314 = (uint*)0x0;
            } else {
                puStack_314 = (uint*)constructCustomObject();
            }
            if (fVar19 != 0.0f) {
                initCustomObject(puStack_314);
            }
            endActionBlock();
            popStack();
            popStack();
            goto LAB_005b0e86;
        case 2:
            popStack();
            popStack();
            puVar13 = (uint*)(*gAlloc)(8, 0);
            if (puVar13 != (uint*)0x0) {
                *puVar13 = *puVar13 & 0xffff8006 | 6;
                *(undefined2*)((int)puVar13 + 2) = 0;
                *puVar13 = *puVar13 | 0x8000;
                puVar13[1] = (uint)fStack_300;
                in_XMM0 = fStack_300;
                popStack(this);
                goto opcodeLoop;
            }
            break;
        case 3:
            popStack();
            popStack();
            iVar11 = (*gAlloc)(8, 0);
            if (iVar11 != 0) {
                popStringResult();
                popStack(this);
                goto opcodeLoop;
            }
            break;
        case 4:
            popStack();
            popStack();
            iVar11 = (*gAlloc)(8, 0);
            if (iVar11 != 0) {
                popFloatResult();
                popStack(this);
                goto opcodeLoop;
            }
            break;
        default:
            goto defaultSwitch;
        }
        break;
    case 0x4F: // 'O' - Delete?
        uVar15 = readValue(0);
        readValue(1);
        uVar9 = readValue(2);
        cVar5 = isTraceEnabled();
        if ((cVar5 == '\0') ||
            ((cVar5 = isNumberType(), cVar5 == '\0' && (cVar5 = isStringType(), cVar5 == '\0')))) {
            cVar5 = isDebuggerActive(0);
            if ((cVar5 == '\0') && (cVar5 = isDebuggerSupported(), cVar5 == '\0')) {
                cVar5 = isClassDefined();
                if (cVar5 != '\0') {
                    uVar15 = getStringFromValue(auStack_208, 0x100);
                    iVar11 = getCurrentScope();
                    (*gDeleteProperty)(*(undefined4*)(iVar11 + 0xc), uVar15);
                }
            } else {
                iVar11 = getCurrentScope();
                setVariable(uVar9, 0, *(undefined4*)(iVar11 + 0xc), uVar15, 1, 0);
            }
        } else {
            getTraceOutput();
            pushStringFromStack(uVar15);
            addFunctionArg(uVar15);
        }
        popStack();
        popStack();
        popStack();
        goto opcodeLoop;
    case 0x50: // 'P' - NextFrame?
        readValue(0);
        cVar5 = isNumberType();
        if (cVar5 != '\0') {
            iVar11 = isActionInterrupted();
            if (iVar11 == 0) goto LAB_005b020f;
            pushStringFromStack();
            popStringResult();
            popStack();
            popStack(this);
            goto opcodeLoop;
        }
        iVar11 = isMovieClipLoaded();
        if (iVar11 != 0) {
            pushFloatFromStack();
            in_XMM0 = in_XMM0 + 1.0f;
            gotoFrame();
LAB_005b01f9:
            popStack();
            popStack(this);
            goto opcodeLoop;
        }
        goto LAB_005b020f;
    case 0x51: // 'Q' - PrevFrame?
        readValue(0);
        cVar5 = isNumberType();
        if (cVar5 == '\0') {
            iVar11 = isMovieClipLoaded();
            if (iVar11 != 0) {
                pushFloatFromStack();
                in_XMM0 = in_XMM0 - 1.0f;
                gotoFrame();
                popStack();
                popStack(this);
                goto opcodeLoop;
            }
        } else {
            iVar11 = isActionInterrupted();
            if (iVar11 != 0) {
                pushStringFromStack();
                popStringResult();
                goto LAB_005b01f9;
            }
        }
LAB_005b020f:
        popStack();
        popStack(this);
        goto opcodeLoop;
    case 0x52: // 'R' - SetRegister?
        readValue(0);
        puVar13 = (uint*)readValue(1);
        readValue(2);
        pcVar16 = (char*)getStringFromValue(auStack_208, 0x100);
        iVar11 = pushStringFromStack();
        if ((~((byte)(*puVar13 >> 0xf) & 1) == 0) {
            pushValueToStack(puVar13, 0, pcVar16, 1, 1);
            pushRegisterContext(context);
            popStack();
            popStack();
            popStack();
            setProperty(puVar13, iVar11);
            puVar13 = (uint*)readValue(0);
            if (((puVar13 != gDefaultValue) && (cVar5 = isTraceEnabled(), cVar5 != '\0')) &&
                (iVar11 = stricmp(pcVar16, "pop"), iVar11 == 0)) {
                uVar15 = readValue(0);
                puVar13 = (uint*)readValue(0);
                (**(code**)(&gTypeVtables + (*puVar13 & 0x7fff) * 4))(uVar15);
            }
            popRegisterContext();
        } else {
            iVar11 = iVar11 + 3;
            if (0 < iVar11) {
                do {
                    popStack();
                    iVar11 = iVar11 + -1;
                } while (iVar11 != 0);
            }
            popStack(this);
        }
        goto opcodeLoop;
    case 0x66: // 'f' - Less2?
        puVar13 = (uint*)readValue(0);
        puStack_314 = (uint*)readValue(1);
        if ((*puVar13 & 0x7fff) == 0x13) {
            puVar13 = gDefaultValue;
        }
        if ((*puStack_314 & 0x7fff) == 0x13) {
            puStack_314 = gDefaultValue;
        }
        cVar5 = isNumberType();
        if ((((cVar5 != '\0') || (cVar5 = isStringType(), cVar5 != '\0')) &&
             ((cVar5 = isNumberType(), cVar5 != '\0' || (cVar5 = isStringType(), cVar5 != '\0')))) ||
            (((*puStack_314 ^ *puVar13) & 0x7fff) == 0)) {
            switch (*puVar13 & 0x7fff) {
            case 1: // String type?
                iVar11 = getCurrentScope();
                pcVar16 = *(char**)(iVar11 + 0xc);
                iVar11 = getCurrentScope();
                pcVar12 = *(char**)(iVar11 + 0xc);
                do {
                    if (((*pcVar12 != *pcVar16) || (*pcVar12 == '\0')) ||
                        (pcVar1 = pcVar12 + 1, *pcVar1 != pcVar16[1])) break;
                    pcVar12 = pcVar12 + 2;
                    pcVar16 = pcVar16 + 2;
                } while (*pcVar1 != '\0');
                break;
            default:
                break;
            case 5: // Number? 
            case 7: // Boolean?
                pushStringFromStack();
                cVar5 = isNumberType();
                if (cVar5 == '\0') {
                    pushFloatFromStack();
                    in_XMM0 = 1.0f; // True
                } else {
                    pushStringFromStack();
                }
                break;
            case 6: // Float?
                pushFloatFromStack();
                fStack_2f4 = in_XMM0;
                cVar5 = isNumberType();
                if (cVar5 == '\0') {
                    pushFloatFromStack();
                    in_XMM0 = (float)((uint)(fStack_2f4 - in_XMM0) & maskFloat);
                } else {
                    iVar11 = pushStringFromStack();
                    in_XMM0 = (float)((uint)(fStack_2f4 - (float)iVar11) & maskFloat);
                }
            }
        }
        popStack();
        popStack();
        iVar11 = isFloatResult();
        if (iVar11 != 0) {
            popFloatResult();
            popStack(this);
            goto opcodeLoop;
        }
        break;
    case 0x67: // 'g' - GreaterThan?
        readValue(0);
        readValue(1);
        cVar5 = isInFunction();
        if ((cVar5 == '\0') || (cVar5 = isInFunction(), cVar5 == '\0')) {
            cVar5 = isStringType();
            if ((cVar5 == '\0') && (cVar5 = isStringType(), cVar5 == '\0')) {
                pushStringFromStack();
                pushStringFromStack();
            } else {
                pushFloatFromStack();
                pushFloatFromStack();
            }
        } else {
            iVar11 = getCurrentScope();
            pcVar16 = *(char**)(iVar11 + 0xc);
            iVar11 = getCurrentScope();
            stricmp(*(char**)(iVar11 + 0xc), pcVar16);
        }
LAB_005afdd2:
        iVar11 = (*gAlloc)(8, 0);
        if (iVar11 != 0) {
            popFloatResult();
        }
LAB_005afa10:
        popStack();
        popStack();
        local_308 = piVar6;
LAB_005afa1c:
        popStack(this);
        piVar6 = local_308;
        goto opcodeLoop;
    case 0x83: // -0x7d = 0x83 - Jump?
        piVar6 = (int*)(((uint)(local_308 + 1) & 0xfffffffc) + 8);
        cVar5 = isWithinFrame();
        if (cVar5 == '\0') {
            puStack_2b4 = &DAT_00e36da0;
            pcStack_2b0 = "..\\source\\Apt\\AptActionInterpreter.cpp";
            uStack_2ac = 0xb0a;
            uStack_2a8 = 2;
            puStack_2a4 = &DAT_01128ffc;
            FatalError();
        } else {
            jumpToFrame(*(undefined4*)(((uint)(local_308 + 1) & 0xfffffffc) + 4));
        }
        goto opcodeLoop;
    case 0x87: // -0x79 = 0x87 - RegisterStore?
        piVar6 = (int*)((uint)(local_308 + 1) & 0xfffffffc);
        if (*(int*)(this + 0x820 + *piVar6 * 4) != 0) {
            puVar13 = *(uint**)(this + 0x820 + *piVar6 * 4);
            (**(code**)(&gTypeVtables + (*puVar13 & 0x7fff) * 4))(puVar13);
        }
        uVar15 = readValue(0);
        *(undefined4*)(this + 0x820 + *piVar6 * 4) = uVar15;
        endActionBlock();
        piVar6 = piVar6 + 1;
        goto opcodeLoop;
    case 0x88: // -0x78 = 0x88 - StoreFlags?
        puVar14 = (undefined4*)((uint)(local_308 + 1) & 0xfffffffc);
        *(undefined4*)(this + 0x814) = *puVar14;
        *(undefined4*)(this + 0x818) = puVar14[1];
        piVar6 = puVar14 + 2;
        goto opcodeLoop;
    case 0x8C: // -0x74 = 0x8C - CallFunction?
        beginActionBlock();
        callMethodWithArgs(context, 0, *(undefined4*)((uint)(local_308 + 1) & 0xfffffffc), auStack_25c);
        enableTrace();
        popDynamic();
        iVar11 = getMovieClipDepth();
        if (iVar11 != -1) {
            enableTrace();
            setFrameIndex(iVar11);
        }
        popDynamicVariable();
        piVar6 = (undefined4*)((uint)(local_308 + 1) & 0xfffffffc) + 1;
        goto opcodeLoop;
    case 0x96: // -0x6a = 0x96 - PopN?
        piVar8 = (int*)((uint)(local_308 + 1) & 0xfffffffc);
        iVar11 = 0;
        piVar6 = piVar8 + 2;
        if (0 < *piVar8) {
            do {
                popStack(this);
                iVar11 = iVar11 + 1;
            } while (iVar11 < *piVar8);
        }
        goto opcodeLoop;
    case 0x99: // -0x67 = 0x99 - With?
        piVar6 = (int*)((int)((uint)(local_308 + 1) & 0xfffffffc) +
                        *(int*)((uint)(local_308 + 1) & 0xfffffffc) + 4);
        goto opcodeLoop;
    case 0x9A: // -0x66 = 0x9A - Push immediate?
        readValue(0);
        readValue(1);
        beginActionBlock();
        beginActionBlock();
        getBytecodeChunk(auStack_278);
        cVar5 = isWithinFrame();
        if (cVar5 == '\0') {
            puStack_28c = &DAT_00e36da0;
            pcStack_288 = "..\\source\\Apt\\AptActionInterpreter.cpp";
            uStack_284 = 0xb35;
            uStack_280 = 2;
            puStack_27c = &DAT_01128ffd;
            FatalError();
        } else {
            getBytecodeChunk(auStack_224);
            jumpToFrame(uStack_21c);
        }
        popStack();
        popStack();
        popDynamicVariable();
        popDynamicVariable();
        goto opcodeLoop;
    case 0x9B: // -0x65 = 0x9B - DefineFunction?
        puVar14 = (undefined4*)((uint)(local_308 + 1) & 0xfffffffc);
        local_308 = (int*)((int)puVar14 + puVar14[3] + 0x18);
        puVar14[4] = *(undefined4*)(this + 0x814);
        puVar14[5] = *(undefined4*)(this + 0x818);
        if (*(int*)(this + 0x604) < 1) {
            puStack_310 = (uint*)0x0;
        } else {
            puStack_310 = (uint*)getLocalScope();
            endActionBlock();
        }
        iVar11 = isFunctionRegistered();
        if (iVar11 == 0) {
            uVar15 = 0;
        } else {
            iVar11 = popDynamic();
            uVar15 = compileFunction(puVar14, puStack_310, *(undefined4*)(*(int*)(iVar11 + 8) + 4));
        }
        if (*(char*)*puVar14 == '\0') goto LAB_005afa1c;
        setVariable(context, 0, (char*)*puVar14, uVar15, 1, 1);
        piVar6 = local_308;
        goto opcodeLoop;
    case 0x9D: // -0x63 = 0x9D? Actually -99 = 0x9D - JumpIfNot?
        piVar6 = (int*)((uint)(local_308 + 1) & 0xfffffffc) + 1;
        readValue(0);
        iVar11 = pushStringFromStack();
        popStack();
        if (iVar11 != 0) {
            piVar6 = (int*)((int)piVar6 + *(int*)((uint)(local_308 + 1) & 0xfffffffc));
        }
        goto opcodeLoop;
    }
    popStack(this);
    goto opcodeLoop;
}