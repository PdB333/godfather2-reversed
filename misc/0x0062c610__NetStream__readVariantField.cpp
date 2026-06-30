// FUNC_NAME: NetStream::readVariantField
undefined4 NetStream::readVariantField(void)
{
    int fieldCount;
    long long *floatFieldPtr;
    int baseOffset2;
    uint offsetSum;
    undefined4 result;
    undefined4 *outputPtr;
    int baseOffset3;
    uint searchIndex;
    undefined2 fpuControl;
    float floatValue;
    undefined4 tempLocal1;
    int baseOffset1;
    long long tempLL;
    int tempInt1;
    uint tempUint;
    int tempInt2;
    undefined4 tempLocal2;

    // Access the data source pointer (at +0xC) and its base (at -4)
    fieldCount = *(int *)(*(int *)(this + 0xC) + -4);
    // Check type byte at fieldCount+7 to determine if field0 exists
    if ((*(char *)(fieldCount + 7) == '\0') || ((int *)(fieldCount + 0x10) == (int *)0x0)) {
        baseOffset1 = 0;
    }
    else if (*(int *)(fieldCount + 0x10) == 4) {
        // Type 4: direct offset from data pointer +0x14
        baseOffset1 = *(int *)(fieldCount + 0x14) + 0x10;
    }
    else {
        // Other types: resolve via helper
        tempInt1 = resolveVariantType(this);
        if (tempInt1 == 0) {
            baseOffset1 = 0;
        }
        else {
            baseOffset1 = *(int *)(fieldCount + 0x14) + 0x10;
        }
        // Sanity check on buffer capacity?
        if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
            handleBufferOverflow();
        }
    }

    // Now compute second offset (field1)
    tempInt2 = 0;
    fieldCount = *(int *)(*(int *)(this + 0xC) + -4);
    if ((*(char *)(fieldCount + 7) == '\0') || ((int *)(fieldCount + 0x10) == (int *)0x0)) {
        tempLocal1 = 0;
    }
    else if (*(int *)(fieldCount + 0x10) == 4) {
        tempLocal1 = *(int *)(*(int *)(fieldCount + 0x14) + 0xC);
    }
    else {
        tempInt1 = resolveVariantType(this);
        if (tempInt1 == 0) {
            tempLocal1 = 0;
        }
        else {
            tempLocal1 = *(int *)(*(int *)(fieldCount + 0x14) + 0xC);
        }
    }

    // Third field (field2) if byte at +7 > 1
    fieldCount = *(int *)(*(int *)(this + 0xC) + -4);
    if ((1 < *(byte *)(fieldCount + 7)) && ((int *)(fieldCount + 0x18) != (int *)0x0)) {
        if (*(int *)(fieldCount + 0x18) == 4) {
            baseOffset3 = *(int *)(fieldCount + 0x1C) + 0x10;
        }
        else {
            baseOffset3 = resolveVariantType(this);
            if (baseOffset3 == 0) {
                baseOffset3 = 0;
            }
            else {
                baseOffset3 = *(int *)(fieldCount + 0x1C) + 0x10;
            }
            if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
                handleBufferOverflow();
            }
        }
    }

    tempInt1 = baseOffset1; // local_118
    tempInt2 = this;       // local_110 (unused after?)
    offsetSum = tempLocal1 + baseOffset1; // local_114

    // Fourth field (field3) if byte at +7 >= 3
    fieldCount = *(int *)(*(int *)(this + 0xC) + -4);
    if (*(byte *)(fieldCount + 7) < 3) {
        floatFieldPtr = (long long *)0x0;
    }
    else {
        floatFieldPtr = (long long *)(fieldCount + 0x20);
    }

    if (floatFieldPtr == (long long *)0x0) {
LAB_0062c780:
        floatValue = 0.0f;
    }
    else {
        if ((int)*floatFieldPtr != 3) {
            // If not type 3, try to resolve; if type 4, use a different path
            if (((int)*floatFieldPtr != 4) || (fieldCount = resolveLongLongField(&tempLocal1), fieldCount == 0)) {
                goto LAB_0062c780;
            }
            floatFieldPtr = &tempLL;
        }
        floatValue = *(float *)((int)floatFieldPtr + 4);
    }

    // Prepare rounded index
    tempLocal1 = CONCAT22((short)((uint)floatValue >> 0x10), fpuControl); // preserve FPU state
    tempLL = (long long)ROUND(floatValue);
    searchIndex = (int)tempLL + baseOffset1; // uVar8

    // Loop to find a valid entry
    if (searchIndex <= offsetSum) {
        do {
            tempLocal2 = 0;
            tempUint = findEntryAtIndex(&tempInt1, searchIndex, baseOffset3); // FUN_0062bd60
            if (tempUint != 0) {
                fieldCount = tempUint - baseOffset1;
                if (tempUint == searchIndex) {
                    fieldCount = fieldCount + 1;
                }
                outputPtr = *(undefined4 **)(this + 8);
                *outputPtr = 3; // Tag: type 3 (float?)
                outputPtr[1] = (float)fieldCount;
                *(int *)(this + 8) = *(int *)(this + 8) + 8; // Advance output pointer
                fieldCount = *(int *)(this + 8);
                tempInt2 = *(int *)(*(int *)(this + 0xC) + -4);
                if (*(byte *)(tempInt2 + 7) < 3) {
                    outputPtr = (undefined4 *)0x0;
                }
                else {
                    outputPtr = (undefined4 *)(tempInt2 + 0x20);
                }
                // Copy the found value (two dwords) from output buffer? Actually this overwrites the just-written data?
                *outputPtr = *(undefined4 *)(fieldCount + -8);
                outputPtr[1] = *(undefined4 *)(fieldCount + -4);
                *(int *)(this + 8) = *(int *)(this + 8) + -8; // Undo the increment??
                result = finalizeEntry(searchIndex, tempUint); // FUN_0062c1b0
                return result;
            }
            searchIndex = searchIndex + 1;
        } while (searchIndex <= offsetSum);
    }
    return 0;
}