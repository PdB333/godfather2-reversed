// FUNC_NAME: FormatString::processFormat
// Address: 0x0062c970
// Role: Processes a format string with capture indices (e.g., %1, %2) and writes output to a buffer.
// Uses a token stream (from this->tokenStream) and a capture array (this->captures).
// Handles literal characters and format specifiers, with error handling for invalid captures.

void __thiscall FormatString::processFormat(int this, int* bufferPtr, undefined4 param3, undefined4 param4)
{
    byte* pbVar1;
    int iVar2;
    int iVar3;
    int* piVar4;
    int* piVar5;
    int iVar6;
    int* piVar7;

    // Get token stream structure
    piVar5 = *(int**)(this + 8);
    iVar6 = piVar5[3]; // current token pointer
    piVar7 = (int*)(iVar6 + 0x10); // token data start
    piVar4 = (int*)piVar5[2]; // end of token stream

    // Check if there is a valid token (type 3 or 4)
    if (((piVar7 < piVar4) && (piVar7 != (int*)0x0)) &&
        ((iVar3 = *piVar7, iVar3 == 4 || (iVar3 == 3))))
    {
        if ((piVar7 < piVar4) && (piVar7 != (int*)0x0))
        {
            if (iVar3 == 4)
            {
                // Token type 4: literal string? Get offset to string data
                iVar6 = *(int*)(iVar6 + 0x14) + 0x10;
            }
            else
            {
                // Token type 3: format specifier? Check validity
                iVar3 = FUN_00633990(piVar5);
                if (iVar3 == 0)
                {
                    iVar6 = 0;
                }
                else
                {
                    iVar6 = *(int*)(iVar6 + 0x14) + 0x10;
                }
                // Check if buffer needs flushing
                if (*(uint*)(piVar5[4] + 0x20) <= *(uint*)(piVar5[4] + 0x24))
                {
                    FUN_00627360(); // flush buffer
                }
            }
        }
        else
        {
            iVar6 = 0;
        }

        // Get the string data pointer from the token
        iVar3 = piVar5[3];
        piVar7 = (int*)(iVar3 + 0x10);
        if ((piVar7 < (int*)piVar5[2]) && (piVar7 != (int*)0x0))
        {
            if (*piVar7 == 4)
            {
                piVar5 = *(int**)(*(int*)(iVar3 + 0x14) + 0xc);
            }
            else
            {
                iVar2 = FUN_00633990(piVar5);
                if (iVar2 == 0)
                {
                    piVar5 = (int*)0x0;
                }
                else
                {
                    piVar5 = *(int**)(*(int*)(iVar3 + 0x14) + 0xc);
                }
            }
        }
        else
        {
            piVar5 = (int*)0x0;
        }

        // Iterate over the string data, writing characters to buffer
        piVar7 = (int*)0x0;
        if (piVar5 != (int*)0x0)
        {
            do
            {
                if (*(char*)((int)piVar7 + iVar6) == '%')
                {
                    // Found a '%' - check for capture index
                    pbVar1 = (byte*)((int)piVar7 + iVar6 + 1);
                    piVar7 = (int*)((int)piVar7 + 1);
                    iVar3 = _isdigit((uint)*pbVar1);
                    if (iVar3 == 0)
                    {
                        // Not a digit - write '%' as literal
                        if ((bufferPtr + 0x83 <= (int*)*bufferPtr) && (iVar3 = FUN_00628940(), iVar3 != 0))
                        {
                            FUN_006289a0(bufferPtr); // flush buffer
                        }
                        *(undefined1*)*bufferPtr = *(undefined1*)((int)piVar7 + iVar6);
                        *bufferPtr = *bufferPtr + 1;
                    }
                    else
                    {
                        // Digit found - it's a capture index (e.g., %1, %2)
                        iVar3 = *(char*)((int)piVar7 + iVar6) + -0x31; // convert ASCII to index (0-based)
                        if (((iVar3 < 0) || (*(int*)(this + 0xc) <= iVar3)) ||
                            (*(int*)(this + 0x14 + iVar3 * 8) == -1))
                        {
                            // Invalid capture index
                            piVar4 = (int*)FUN_00627bd0("invalid capture index");
                            goto LAB_0062cae8;
                        }
                        // Process the capture
                        FUN_0062c150();
                        FUN_00628c50();
                    }
                }
                else
                {
                    // Regular character - write to buffer
                    if ((bufferPtr + 0x83 <= (int*)*bufferPtr) && (iVar3 = FUN_00628940(), iVar3 != 0))
                    {
                        FUN_006289a0(bufferPtr); // flush buffer
                    }
                    *(undefined1*)*bufferPtr = *(undefined1*)((int)piVar7 + iVar6);
                    *bufferPtr = *bufferPtr + 1;
                }
                piVar7 = (int*)((int)piVar7 + 1);
                if (piVar5 <= piVar7)
                {
                    return;
                }
            } while (true);
        }
    }
    else
    {
        // Error path: invalid token encountered
LAB_0062cae8:
        *piVar4 = *piVar7;
        piVar4[1] = piVar7[1];
        piVar5[2] = piVar5[2] + 8; // advance token stream
        iVar6 = FUN_0062c1b0(param3, param4);
        FUN_006362d0(piVar5, piVar5[2] - (iVar6 * 8 + 8), 1); // shift tokens
        piVar7 = (int*)(piVar5[2] + -8);
        if ((piVar7 != (int*)0x0) && ((*piVar7 == 4 || (*piVar7 == 3))))
        {
            FUN_00628c50();
            return;
        }
        piVar5[2] = (int)piVar7;
    }
    return;
}