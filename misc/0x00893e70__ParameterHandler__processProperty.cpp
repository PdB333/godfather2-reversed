// FUNC_NAME: ParameterHandler::processProperty
// Function address: 0x00893e70
// Role: Generic property access dispatcher for parameter data (get/set/add/multiply)
// Uses hash IDs to identify properties, supports 5 operations: 1=get, 2=set, 3=add, 4=multiply
// param_1: this - likely a ParameterHandler instance with derived object pointer at +0x38
// param_2: outValue - output/input float value depending on operation
// param_3: propertyHash - CRC32 hash of property name
// param_4: sourceData - pointer to a structure with fields at +8 (int), +0xC (int), +0x10 (byte flags)
// param_5: operationType - 1=GET, 2=SET, 3=ADD, 4=MULTIPLY
// param_6, param_7: additional context (passed to setPropertyValue)

__thiscall unsigned char ParameterHandler::processProperty(int thisPtr, float* outValue, unsigned int propertyHash, int sourceData, int operationType, undefined4 param6, undefined4 param7)
{
    float fVar1;
    int iVar2;
    int* piVar3;
    float10 fVar4;
    int roundedValue;

    if (propertyHash < 0x61d5bbab) {
        // Hash: 0x61d5bbaa -> some integer property at sourceData+8
        if (propertyHash == 0x61d5bbaa) {
            if (operationType != 1) return 0;
            *outValue = (float)*(int*)(sourceData + 8);
            return 1;
        }
        // Hash: 0x1722f6a0 -> random value property
        if (propertyHash == 0x1722f6a0) {
            if (operationType != 1) return 0;
            iVar2 = getRandomObject(); // FUN_00892cd0
            if (iVar2 != 0) {
                getRandomObject();
                fVar4 = (float10)getRandomFloat(); // FUN_007352b0
                *outValue = (float)fVar4;
                return 1;
            }
            *outValue = g_defaultRandomValue; // _DAT_00d5780c
            return 1;
        }
        // Hash: 0x471e201b -> another integer property at sourceData+0xC (signed conversion)
        if (propertyHash == 0x471e201b) {
            if (operationType != 1) return 0;
            fVar1 = (float)*(int*)(sourceData + 0xc);
            if (*(int*)(sourceData + 0xc) < 0) {
                fVar1 = fVar1 + g_floatAdjustment; // DAT_00e44578
            }
            *outValue = fVar1;
            return 1;
        }
        // Hash: 0x4ea8b900 -> property controlled by flags byte at sourceData+0x10 bit0
        if (propertyHash == 0x4ea8b900) {
            if ((*(unsigned char*)(sourceData + 0x10) & 1) == 0) return 0;
            iVar2 = getSomeGlobal(); // FUN_006ebfd0
            if (operationType == 1) {
                *outValue = *(float*)(iVar2 + 0x100);
                return 1;
            }
            if (operationType != 3) return 0;
            // Operation 3: add, but clamped between g_maxThreshold and g_bigNumber - value
            fVar1 = *outValue;
            if (g_maxThreshold <= fVar1) {
                playSoundEffect(fVar1, 4); // FUN_008c09a0
                return 1;
            }
            playSoundEffect(g_bigNumber - fVar1, 10);
            return 1;
        }
    }
    else {
        // Hash: 0xe7ad7581 -> bit test at sourceData+0x10 bit2
        if (propertyHash == 0xe7ad7581) {
            if (operationType != 1) return 0;
            *outValue = (float)((*(unsigned char*)(sourceData + 0x10) >> 2) & 1);
            return 1;
        }
        // Hash: 0xe83af06c -> property using derived object at this+0x38
        if (propertyHash == 0xe83af06c) {
            if (*(int*)(thisPtr + 0x38) == 0) return 0;
            if (*(int*)(thisPtr + 0x38) == 0x48) return 0; // offset sentinel?
            if (operationType == 1) {
                // Get: uses derived object field at +0x1ed0
                int derivedBase = *(int*)(thisPtr + 0x38);
                if (derivedBase == 0) {
                    iVar2 = 0;
                }
                else {
                    iVar2 = derivedBase - 0x48; // adjust to derived object start
                }
                float val = (float)*(int*)(iVar2 + 0x1ed0);
                if (*(int*)(iVar2 + 0x1ed0) < 0) {
                    val = val + g_floatAdjustment;
                }
                *outValue = val;
                return 1;
            }
            if (operationType == 2) {
                // Set: call setField on derived object, using dereferenced vtable
                int derivedBase = *(int*)(thisPtr + 0x38);
                if (derivedBase == 0) {
                    piVar3 = (int*)0x0;
                }
                else {
                    piVar3 = (int*)(derivedBase - 0x48);
                }
                roundedValue = (int)(longlong)round(*outValue);
                // Call vtable method at offset 0x1dc (setField)
                (**(code**)(*piVar3 + 0x1dc))(roundedValue);
                return 1;
            }
            if (operationType != 3) {
                if (operationType != 3) return 0;
                // Add: uses derived object, adjust base pointer for setField
                int derivedBase = *(int*)(thisPtr + 0x38);
                if (derivedBase == 0) {
                    piVar3 = (int*)0x0;
                    iVar2 = 0;
                }
                else {
                    piVar3 = (int*)(derivedBase - 0x48);
                    iVar2 = derivedBase - 0x48;
                }
                roundedValue = (int)(longlong)round(*outValue);
                // Call with offset: add to existing field at +0x1ed0
                (**(code**)(*piVar3 + 0x1dc))(roundedValue + *(int*)(iVar2 + 0x1ed0));
                return 1;
            }
            // Fallthrough: operationType 2 (set) handled above, 3 (add) handled, so only 2 left in this block? Reorder.
        }
    }

    // Fallback: if sourceData flags (bits 0 and 2) allow, look up property in a table
    if (((*(unsigned char*)(sourceData + 0x10) & 5) == 0) || (iVar2 = findPropertyEntry(propertyHash), iVar2 == 0)) {
        // FUN_00893470 - finds a property entry by hash
        return 0;
    }
    if (operationType == 1) {
        *outValue = *(float*)(iVar2 + 8);
        return 1;
    }
    if (operationType == 2) {
        setPropertyValue(iVar2, *outValue, param6, param7); // FUN_00894d00
        return 1;
    }
    if (operationType == 3) {
        setPropertyValue(iVar2, *(float*)(iVar2 + 8) + *outValue, param6, param7);
        return 1;
    }
    if (operationType == 4) {
        setPropertyValue(iVar2, *(float*)(iVar2 + 8) * *outValue, param6, param7);
        return 1;
    }
    return 0;
}