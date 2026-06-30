// Xbox PDB: AptCharacterInst::objectMemberLookup
// FUNC_NAME: AptCharacterFactory::createCharacter
// Function address: 0x005b77c0
// Role: Factory method that creates various AptCharacter-related objects based on type ID and optional string input.
// Sources: from "..\\source\\Apt\\AptCharacter.cpp"
// The function takes a context pointer (param_1, often 0) and a name string (param_2).
// It uses two different factory flows depending on whether a global character manager pointer is valid.

uint* AptCharacterFactory::createCharacter(int contextPtr, char* charName)
{
    byte bVar1;
    char cVar2;
    char* pcVar3;
    int typeIdObj;
    int charData;
    undefined4 uVar6;
    byte* pbVar7;
    uint* resultObj;
    int iVar9;
    bool bVar10;
    float value;
    float local_174;
    // ... many unused local variables from debug info

    // First flow: get character manager and check if string is valid
    void* charMgr = getCharacterManager(); // FUN_0059c3b0
    cVar2 = isStringValid(); // FUN_0059c950 - returns non-zero if string is ok
    pcVar3 = charName;
    if (cVar2 != '\0') {
        // compute string length
        do {
            cVar2 = *pcVar3;
            pcVar3 = pcVar3 + 1;
        } while (cVar2 != '\0');

        typeIdObj = getTypeIdFromString(); // FUN_005b4780
        if (typeIdObj == 0) goto LAB_005b7dbd;

        charData = getCharacterData(); // FUN_0059c810
        switch(*(int*)(typeIdObj + 4)) {
        case 1:
            // Allocate and initialize a character in different sub-modes (subtypes)
            resultObj = (uint*)(*g_allocFunc)(0x24, 0); // DAT_0119caf0, size 36 bytes
            if (resultObj == (uint*)0x0) {
                resultObj = (uint*)0x0;
            } else {
                resultObj = (uint*)allocateCharacter36(); // FUN_0059cae0
            }
            switch(*(int*)(charData + 0x40)) {
            case 0:
                initializeCharacter(resultObj); // FUN_005b8920
                return resultObj;
            case 1:
                initializeCharacter(resultObj);
                return resultObj;
            case 2:
                initializeCharacter(resultObj);
                return resultObj;
            default:
                initializeCharacter(resultObj);
                return resultObj;
            }
        case 2:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectA(); // FUN_005a8580
            return resultObj;
        case 3:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectB(); // FUN_0059cb20
            return resultObj;
        case 4:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectA(); // same as case 2
            return resultObj;
        case 5:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectB();
            return resultObj;
        default:
            // error: unknown type, log assert
            logAssertion("..\\\\source\\\\Apt\\\\AptCharacter.cpp", 3.48783e-42, 2.8026e-45);
            goto LAB_005b7dbd;
        case 7:
            // temporary push/pop context
            pushContext(); // FUN_005a0950
            getSomeLocalObject(&local_15c); // FUN_005a92b0
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) {
                popContext(); // FUN_005a0b30
                return (uint*)0x0;
            }
            resultObj = (uint*)createSmallObjectB();
            popContext();
            return resultObj;
        case 8:
            return g_singletonA; // DAT_0119cbbc
        case 9:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectB();
            return resultObj;
        case 10:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectA();
            return resultObj;
        case 0xb:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectB();
            return resultObj;
        case 0xc:
            // Complex case: handles singleton or cached object
            if (*(int*)(charData + 0x18) == 0) {
                // first time: allocate 36-byte object and store in cache
                resultObj = (uint*)(*g_allocFunc)(0x24, 0);
                if (resultObj == (uint*)0x0) {
                    uVar6 = 0;
                } else {
                    uVar6 = allocateCharacter36();
                }
                *(int*)(charData + 0x18) = uVar6;
                registerAllocation(); // FUN_0059c690
                initializeCharacter(*(int*)(charData + 0x18));
                return *(uint**)(charData + 0x18);
            }
            if (*(int*)(charData + 0x1c) == 0) goto returnCachedObject;
            // iterate through linked list to find matching object
            int iter = getCharacterManager();
            while (iter != 0 && (cVar2 = checkSomeCondition(), cVar2 == '\0')) {
                iter = *(int*)(iter + 0x54);
            }
            resultObj = (uint*)findOrCreateObject(iter, 0, *(int*)(*(int*)(charData + 0x1c) + 0xc), 1, 1); // FUN_005aea60
            if ((~(*resultObj >> 0xf) & 1) != 0) goto returnCachedObject;
            pushContext();
            getSomeLocalObject(&local_15c);
            if (*(int*)(charData + 0x20) == 0) {
                // replace cached object with new one
                destroyObject(*(uint**)(charData + 0x18)); // virtual destructor via vtable
                resultObj = (uint*)(*g_allocFunc)(0x24, 0);
                if (resultObj == (uint*)0x0) {
                    uVar6 = 0;
                } else {
                    uVar6 = allocateWithDifferentConstructor(); // FUN_005abfb0
                }
                *(int*)(charData + 0x18) = uVar6;
                registerAllocation();
            } else {
                // compare strings to decide whether to replace
                pbVar7 = *(byte**)(*(int*)(charData + 0x20) + 0xc);
                do {
                    bVar1 = *pbVar7;
                    bVar10 = bVar1 < *local_154;
                    if (bVar1 != *local_154) {
                        iVar9 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
                        if (iVar9 != 0) goto replaceCachedObject;
                        break;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = pbVar7[1];
                    bVar10 = bVar1 < local_154[1];
                    if (bVar1 != local_154[1]) {
                        iVar9 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
                        if (iVar9 != 0) goto replaceCachedObject;
                        break;
                    }
                    pbVar7 += 2;
                    local_154 += 2;
                } while (bVar1 != 0);
            }
            popContext();
returnCachedObject:
            return *(uint**)(charData + 0x18);
        case 0xd:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectB();
            return resultObj;
        case 0xe:
            // Create a float value object (8 bytes) with default value
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            value = *(float*)(charData + 0x48) + g_floatConstant; // DAT_00e2d99c
            break;
        case 0xf:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            value = *(float*)(charData + 0x44) + g_floatConstant;
            *resultObj = *resultObj & 0xffff8006 | 6;
            goto setResultFlags;
        case 0x10:
            resultObj = (uint*)(*g_allocFunc)(0x24, 0);
            if (resultObj == (uint*)0x0) {
                initializeCharacter(0);
                return (uint*)0x0;
            }
            resultObj = (uint*)allocateCharacter36();
            initializeCharacter(resultObj);
            return resultObj;
        case 0x11:
            if (*(uint**)(charData + 0x1c) == (uint*)0x0) {
                return g_singletonA;
            }
            return *(uint**)(charData + 0x1c);
        case 0x12:
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            resultObj = (uint*)createSmallObjectA();
            return resultObj;
        case 0x13:
            // Decide which float to use based on sub-type
            if (*(int*)(charData + 0x40) == 3) {
                value = *(float*)(charData + 0x50);
            } else {
                value = *(float*)(charData + 0x48);
            }
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            value = 0.0f;
            if (0.0f <= value) {
                value = value;
            }
            break;
        case 0x14:
            if (*(int*)(charData + 0x40) == 3) {
                value = *(float*)(charData + 0x4c);
            } else {
                value = *(float*)(charData + 0x44);
            }
            resultObj = (uint*)(*g_allocFunc)(8, 0);
            if (resultObj == (uint*)0x0) return (uint*)0x0;
            value = 0.0f;
            if (0.0f <= value) {
                value = value;
            }
            *resultObj = *resultObj & 0xffff8006 | 6;
            goto setResultFlags;
        }
        // Common code for cases 0xe, 0xf, 0x13, 0x14: set value and flags
        *resultObj = *resultObj & 0xffff8006 | 6;
setResultFlags:
        *(short*)((int)resultObj + 2) = 0;
        *resultObj = *resultObj | 0x8000;
        resultObj[1] = (uint)value;
        return resultObj;
    }

LAB_005b7dbd:
    // Second flow: alternate factory (when character manager is not available)
    if (contextPtr == 0) {
        return (uint*)0x0;
    }
    cVar2 = checkOtherCondition(0); // FUN_0059c5c0
    if (cVar2 == '\0') {
        return (uint*)0x0;
    }
    // compute string length
    do {
        cVar2 = *charName;
        charName = charName + 1;
    } while (cVar2 != '\0');
    typeIdObj = getTypeIdFromString2(); // FUN_005b46c0
    if (typeIdObj == 0) {
        return (uint*)0x0;
    }
    int charData2 = getCharacterManager(); // FUN_0059c3b0
    iVar9 = getThirdPointer(); // FUN_005a3f20
    value = 0.0f;
    switch(*(int*)(typeIdObj + 4)) {
    case 1:
        value = *(float*)(charData2 + 0x48);
        break;
    case 2:
        value = *(float*)(charData2 + 0x4c);
        break;
    case 3:
        if (*(int*)(charData2 + 0x50) == 0) {
            value = *(float*)(charData2 + 0x38) * g_multiplier; // DAT_00e2b050
        } else {
            value = *(float*)(*(int*)(charData2 + 0x50) + 8);
        }
        break;
    case 4:
    case 5:
    case 6:
        // assertion cases: log error and return null
        logAssertion("..\\\\source\\\\Apt\\\\AptCharacter.cpp", /*line*/ 0x9ed, 2);
        break;
    case 7:
        if (*(int*)(charData2 + 0x50) == 0) {
            value = *(float*)(charData2 + 0x10) * g_multiplier;
        } else {
            value = *(float*)(*(int*)(charData2 + 0x50) + 0x1c);
        }
        break;
    case 8:
        if (*(int*)(charData2 + 0x50) == 0) {
            value = g_defaultValue; // DAT_00e2b1a4
        } else {
            value = *(float*)(*(int*)(charData2 + 0x50) + 0x2c);
        }
        break;
    case 9:
        // Compute value from two fields
        computeSomething(charData2); // FUN_005b5a40
        value = local_168 - (float)local_170;
        goto clampValue;
    case 10:
        computeSomething(charData2);
        value = local_164 - (float)local_16c;
clampValue:
        if (value < 0.0f) {
            value = 0.0f;
        }
        break;
    case 0xb:
        computeSomethingElse(); // FUN_005b5d20
        value = *(float*)(*(int*)(charData2 + 0x50) + 0x18);
        break;
    case 0xc:
        // Create a new 36-byte object and return it
        computeAnotherThing(charData2); // FUN_005ae2a0
        resultObj = (uint*)(*g_allocFunc)(0x24, 0);
        if (resultObj == (uint*)0x0) return (uint*)0x0;
        resultObj = (uint*)allocateSpecificObject(); // FUN_005a84a0
        return resultObj;
    case 0xd:
        value = (float)*(int*)(*(int*)(iVar9 + 8) + 8);
        break;
    case 0xe:
        return *(uint**)(charData2 + 0x34);
    default:
        goto defaultReturnNull;
    case 0x10:
        logAssertion("..\\\\source\\\\Apt\\\\AptCharacter.cpp", 0xb02, 2);
        break;
    case 0x18:
        return g_singletonB; // DAT_0119cbc8
    case 0x19:
        return g_singletonC; // DAT_0119cbc0
    case 0x1a:
        return g_singletonD; // DAT_0119cbc4
    case 0x1b:
        return g_singletonE; // DAT_0119cbcc
    case 0x1c:
        return g_singletonF; // DAT_0119cbb4
    case 100:
        if (g_singleton100 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0); // 80 bytes
            if (resultObj == (uint*)0x0) {
                g_singleton100 = (uint*)0x0;
            } else {
                g_singleton100 = (uint*)createComplexObject(funcPointer); // FUN_005a86f0 with FUN_005b6340
            }
            registerAllocation();
        }
        return g_singleton100; // DAT_012055c0
    case 0x65:
        if (g_singleton101 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton101 = (uint*)0x0;
            } else {
                g_singleton101 = (uint*)createComplexObject("QSUVWj");
            }
            registerAllocation();
        }
        return g_singleton101; // DAT_012055cc
    case 0x67:
        if (g_singleton102 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton102 = (uint*)0x0;
            } else {
                g_singleton102 = (uint*)createComplexObject(&functionAt5b62c0);
            }
            registerAllocation();
        }
        return g_singleton102; // DAT_012055bc
    case 0x68:
        if (g_singleton103 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton103 = (uint*)0x0;
            } else {
                g_singleton103 = (uint*)createComplexObject(&functionAt5b62a0);
            }
            registerAllocation();
        }
        return g_singleton103; // DAT_012055b8
    case 0x69:
        if (g_singleton104 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton104 = (uint*)0x0;
            } else {
                g_singleton104 = (uint*)createComplexObject(FUN_005b6640);
            }
            registerAllocation();
        }
        return g_singleton104; // DAT_012055c4
    case 0x6d:
        if (g_singleton105 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton105 = (uint*)0x0;
            } else {
                g_singleton105 = (uint*)createComplexObject(&functionAt5b69b0);
            }
            registerAllocation();
        }
        return g_singleton105; // DAT_012055d0
    case 0x6e:
        if (g_singleton106 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton106 = (uint*)0x0;
            } else {
                g_singleton106 = (uint*)createComplexObject(FUN_005b6ca0);
            }
            registerAllocation();
        }
        return g_singleton106; // DAT_012055dc
    case 0x73:
        if (g_singleton107 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton107 = (uint*)0x0;
            } else {
                g_singleton107 = (uint*)createComplexObject(FUN_005b6a20);
            }
            registerAllocation();
        }
        return g_singleton107; // DAT_012055d4
    case 0x78:
        if (g_singleton108 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton108 = (uint*)0x0;
            } else {
                g_singleton108 = (uint*)createComplexObject(FUN_005b6a80);
            }
            registerAllocation();
        }
        return g_singleton108; // DAT_012055d8
    case 0x79:
        if (g_singleton109 == (uint*)0x0) {
            resultObj = (uint*)(*g_allocFunc)(0x50, 0);
            if (resultObj == (uint*)0x0) {
                g_singleton109 = (uint*)0x0;
            } else {
                g_singleton109 = (uint*)createComplexObject(FUN_005b6850);
            }
            registerAllocation();
        }
        return g_singleton109; // DAT_012055c8
    }

    // Fallback: create an 8-byte result with the computed value
    resultObj = (uint*)(*g_allocFunc)(8, 0);
    if (resultObj == (uint*)0x0) {
defaultReturnNull:
        return (uint*)0x0;
    }
    *resultObj = *resultObj & 0xffff8006 | 6;
    *(short*)((int)resultObj + 2) = 0;
    *resultObj = *resultObj | 0x8000;
    resultObj[1] = (uint)value;
    return resultObj;
}