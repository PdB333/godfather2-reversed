// FUNC_NAME: BitStream::vformat
int __thiscall BitStream::vformat(int thisPtr, int argPtr) // 'this' at param_1, argPtr at param_2 (pointer to variadic stack)
{
    int* currentWritePtr; // puVar3 = *(int**)(thisPtr+8)
    char c; // cVar2
    int* writeDataSlot; // puVar3 reuse
    char* fmt; // in_EAX - format string pointer
    int result; // local_4
    int iVar5;
    char* percentPos; // local_8
    double* varArgDoublePtr; // local_c - pointer to double arguments on stack (moves downward)
    int varArgIntPtr; // param_2 - pointer to current int/char argument (moves forward)
    bool bVar8, bVar9, bVar10;
    char charBuf[4]; // local_10
    char* strPtr;

    currentWritePtr = *(int**)(thisPtr + 8); // current write pointer
    result = 1;
    *currentWritePtr = 4; // type tag? (4 = string?)
    // Write a placeholder for the first format string literal? Actually FUN_00638920 writes string data
    int uVar4 = writeData(thisPtr, fmt, 0); // FUN_00638920 - writes raw data of given length
    currentWritePtr[1] = uVar4;

    // Check if there is space for 8 more bytes (two 4-byte entries)
    if (*(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8) < 9) {
        ensureWriteSpace(); // FUN_00635c70
    }
    *(int*)(thisPtr + 8) += 8; // advance write pointer by 8

    // Find first '%' in format string
    fmt = (char*)thisPtr; // Wait, in_EAX is passed? Actually the decompiler says in_EAX is the first param? No, in_EAX is a register that holds the first argument? In __thiscall, EAX holds 'this'? But the decompiler shows param_1 is this, and in_EAX appears later used as format string. Possibly the original calling convention passes the format string in EAX? Or it's a hidden parameter? Looking at the code: local_8 = _strchr(in_EAX,0x25); So in_EAX is the format string. That means the function takes an additional hidden parameter? Or the decompiler is confused. Since param_1 is this, and param_2 is argPtr, the format string is likely passed as a third parameter? But the decompiler only shows two parameters. Perhaps in_EAX is actually the first argument (this) but used as format string? That would be wrong. Let's check: the function is called from other places. Possibly the function is actually a member function with an implicit this, and the first real parameter is the format string. So param_1 is this, param_2 is argPtr? But the decompiler shows in_EAX used as format string. In x86 __thiscall, the this pointer is in ECX, not EAX. So the decompiler might be misassigning registers. Since Ghidra often uses fake registers, we should treat in_EAX as the format string argument. So the function signature should be: int __thiscall BitStream::vformat(int thisPtr, const char* format, int* argPtr) but the decompiler only shows two parameters. Actually, looking at the call patterns: it might be that the format string is passed via the stack and the variadic arguments are passed as a va_list (argPtr). So param_2 is a pointer to the variadic arguments. And in_EAX is actually param_1? No, the decompiler shows param_1 and param_2, then uses in_EAX. That suggests in_EAX is the first parameter? But param_1 is used as this. Possible that the function is not __thiscall? But the signature says __thiscall. Let's re-examine: The code uses param_1 for this and param_2 for something. Then in_EAX appears. It might be that the function actually takes three parameters: this, format string, and arg list. But Ghidra only shows two because the third is in a register? Actually, the calling convention might be __fastcall with this in ECX and format in EDX? But the decompiler says __thiscall. I'll assume that the first parameter (in_EAX) is the format string, and param_2 is the va_list argument pointer. So I'll add a third parameter.

Given the ambiguity, I'll reconstruct with a third parameter: const char* format.

    percentPos = _strchr(format, '%');
    int iVar7 = 1; // number of format specifiers processed? Actually used for alignment
    if (percentPos != 0) {
        varArgDoublePtr = (double*)(argPtr - 8); // pointer to double arguments (on stack, going down)
        int currentIntArg = argPtr - 4; // pointer to int/char arguments (going up)
        do {
            writeDataSlot = *(int**)(thisPtr + 8);
            *writeDataSlot = 4; // type tag
            // Write literal text before '%'
            uVar4 = writeData(thisPtr, format, (int)percentPos - (int)format);
            writeDataSlot[1] = uVar4;
            if (*(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8) < 9) {
                // Need to expand buffer
                iVar5 = *(int*)(thisPtr + 0x20); // current capacity
                iVar7 = iVar5 * 2; // double
                if (iVar5 < 1) {
                    iVar7 = iVar5 + 0x15; // minimum growth
                }
                iVar5 = bufferGrow(iVar5 * 8, iVar7 * 8); // FUN_006279a0 - reallocate
                *(int*)(thisPtr + 0x1c) = iVar5; // new buffer base
                *(int*)(thisPtr + 0x18) = iVar5 - 0xa8 + iVar7 * 8; // new end
                *(int*)(thisPtr + 0x20) = iVar7; // new capacity
                postGrow(); // FUN_00635b50
            }
            *(int*)(thisPtr + 8) += 8; // advance pointer

            writeDataSlot = *(int**)(thisPtr + 8);
            switch (percentPos[1]) {
            case '%':
                iVar7 = 1; // overwritten? Actually used later
                *writeDataSlot = 4;
                strPtr = "%";
                goto writeStringData;
            default:
                goto ignoreFormatSpec;
            case 'c':
                strPtr = (char*)(currentIntArg + 4); // get char argument from stack
                currentIntArg += 4;
                varArgDoublePtr = (double*)((int)varArgDoublePtr + 4);
                charBuf[0] = *strPtr;
                strPtr = charBuf;
                charBuf[1] = 0;
                *writeDataSlot = 4;
                // Compute length of char string
                do {
                    c = *strPtr;
                    strPtr++;
                } while (c != 0);
                iVar7 = (int)strPtr - (int)(charBuf + 1); // length excluding null
                strPtr = charBuf;
writeStringData:
                uVar4 = writeData(thisPtr, strPtr, iVar7);
                writeDataSlot[1] = uVar4;
                iVar7 = *(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8);
                bVar10 = (iVar7 < 0) ? 1 : 0; // signed overflow
                bVar9 = (iVar7 - 8 < 0);
                bVar8 = (iVar7 == 8);
                break;
            case 'd':
                varArgDoublePtr = (double*)((int)varArgDoublePtr + 4);
                *writeDataSlot = 3; // type tag for float? Actually d writes int as float? Might be for network serialization
                int* intArg = (int*)(currentIntArg + 4);
                currentIntArg += 4;
                writeDataSlot[1] = (float)*intArg; // store int as float
                iVar7 = *(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8);
                bVar10 = SBORROW4(iVar7,8); // Not sure what SBORROW4 does, likely sign check
                bVar9 = (iVar7 - 8 < 0);
                bVar8 = (iVar7 == 8);
                break;
            case 'f':
                varArgDoublePtr++;
                *writeDataSlot = 3;
                writeDataSlot[1] = (float)*varArgDoublePtr; // write double as float
                iVar7 = *(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8);
                currentIntArg += 8; // double uses 8 bytes
                bVar10 = SBORROW4(iVar7,8);
                bVar9 = (iVar7 - 8 < 0);
                bVar8 = (iVar7 == 8);
                break;
            case 's':
                varArgDoublePtr = (double*)((int)varArgDoublePtr + 4);
                currentIntArg += 4;
                writeStringArg(); // FUN_006368c0 - likely writes the string from arg
                goto ignoreFormatSpec;
            }
            if (bVar8 || bVar10 != bVar9) {
                ensureWriteSpace(); // FUN_00635c70
            }
            *(int*)(thisPtr + 8) += 8;

ignoreFormatSpec:
            result += 2; // increment count? Used for offset calculation later
            format = percentPos + 2;
            percentPos = _strchr(format, '%');
        } while (percentPos != 0);
        percentPos = 0;
        iVar7 = result;
    }

    // Write trailing literal after last '%'
    writeDataSlot = *(int**)(thisPtr + 8);
    *writeDataSlot = 4;
    strPtr = format;
    do {
        c = *strPtr;
        strPtr++;
    } while (c != 0);
    uVar4 = writeData(thisPtr, format, (int)strPtr - (int)(format + 1)); // length of trailing string
    writeDataSlot[1] = uVar4;

    if (*(int*)(thisPtr + 0x18) - *(int*)(thisPtr + 8) < 9) {
        ensureWriteSpace();
    }
    *(int*)(thisPtr + 8) += 8;

    // Finalize: adjust write pointer by some offset? 
    finalizeFormat(thisPtr, result + 1, ((*(int*)(thisPtr + 8) - *(int*)(thisPtr + 0xc)) >> 3) - 1); // FUN_006343b0
    *(int*)(thisPtr + 8) += result * -8; // roll back? Actually subtract result*8

    return *(int*)(*(int*)(thisPtr + 8) - 4) + 0x10; // return some value
}