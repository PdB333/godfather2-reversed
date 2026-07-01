// FUNC_NAME: NetConnection::readPacket
void __thiscall NetConnection::readPacket(int* thisPtr, undefined4 param_2, uint bitStreamPtr)
{
    uint* puVar1;
    byte bVar2;
    uint uVar3;
    char cVar4;
    uint uVar5;
    uint uVar6;
    int iVar7;
    code* pcVar8;
    bool bVar9;
    int unaff_retaddr;
    undefined4 uVar10;
    int local_8[2];

    uVar3 = bitStreamPtr;
    // Initialize bitstream reading? (param_2 might be a buffer or size)
    FUN_00472830(param_2, bitStreamPtr);

    // Read first bit: check if there are more bits
    uVar5 = *(uint*)(bitStreamPtr + 0x18); // current bit index
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1; // overflow flag
    } else {
        bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc)); // byte array
        *(int*)(bitStreamPtr + 0x18) = *(int*)(bitStreamPtr + 0x18) + 1;
        if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
            // Bit is set: read 32-bit value and call handler
            FUN_0064b9e0(0x20, &bitStreamPtr); // read 32 bits into bitStreamPtr
            FUN_008b0890(thisPtr + -0x16, bitStreamPtr); // call handler with base object
        }
    }

    // Read second bit
    uVar5 = *(uint*)(bitStreamPtr + 0x18);
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1;
    } else {
        bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc));
        *(int*)(bitStreamPtr + 0x18) = *(int*)(bitStreamPtr + 0x18) + 1;
        if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
            FUN_0064b9e0(0x20, &bitStreamPtr);
            // Modify a flag in the object at thisPtr[0x167]
            *(uint*)(thisPtr[0x167] + 0x18) = *(uint*)(thisPtr[0x167] + 0x18) & 0xfffdffff;
            (**(code**)(*(int*)thisPtr[0x167] + 0x3c))(bitStreamPtr); // virtual call
            *(uint*)(thisPtr[0x167] + 0x18) = *(uint*)(thisPtr[0x167] + 0x18) | 0x20000;
        }
    }

    // Read third bit
    uVar5 = *(uint*)(bitStreamPtr + 0x18);
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1;
    } else {
        bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc));
        *(int*)(bitStreamPtr + 0x18) = *(int*)(bitStreamPtr + 0x18) + 1;
        if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
            uVar5 = thisPtr[0x222]; // bitfield at offset 0x888
            puVar1 = (uint*)(thisPtr + 0x222);
            bitStreamPtr = CONCAT31(bitStreamPtr._1_3_, (char)(uVar5 >> 1)) & 0xffffff01;
            FUN_0064b9e0(0x80, puVar1); // read 128 bits? Actually 0x80 = 128 bits, but likely a different meaning
            if (((((byte)(uVar5 >> 10) & 1) != ((byte)(*puVar1 >> 10) & 1)) && (thisPtr[0x1bd] != 0)) &&
               (thisPtr[0x1bd] != 0x48)) {
                if ((*puVar1 >> 10 & 1) == 0) {
                    pcVar8 = *(code**)(thisPtr[-0x16] + 0x260); // base object vtable
                } else {
                    pcVar8 = *(code**)(thisPtr[-0x16] + 0x25c);
                }
                (*pcVar8)();
            }
            uVar5 = *puVar1 >> 1;
            if (((uVar5 & 1) == 0) || ((byte)bitStreamPtr != 0)) {
                if (((uVar5 & 1) != 0) || ((byte)bitStreamPtr == ((byte)uVar5 & 1))) goto LAB_008075f9;
                uVar10 = 0;
            } else {
                uVar10 = 4;
            }
            (**(code**)(thisPtr[-0x16] + 0x234))(uVar10, 1); // virtual call
        }
    }

LAB_008075f9:
    // Read fourth bit
    uVar5 = *(uint*)(bitStreamPtr + 0x18);
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1;
    } else {
        bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc));
        *(int*)(bitStreamPtr + 0x18) = *(int*)(bitStreamPtr + 0x18) + 1;
        if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
            FUN_0064b9e0(0x20, &bitStreamPtr);
            thisPtr[0x226] = bitStreamPtr; // store value at offset 0x898
            FUN_0064b9e0(0x20, &bitStreamPtr);
            thisPtr[0x227] = bitStreamPtr; // offset 0x89C
            FUN_0064b9e0(0x20, &bitStreamPtr);
            thisPtr[0x228] = bitStreamPtr; // offset 0x8A0
        }
    }

    // Read fifth bit (and possibly a sixth bit inside)
    uVar5 = *(uint*)(bitStreamPtr + 0x18);
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1;
    } else {
        bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc));
        uVar6 = uVar5 + 1;
        *(uint*)(bitStreamPtr + 0x18) = uVar6;
        if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
            // Read another bit (sixth)
            if (*(uint*)(bitStreamPtr + 0x2c) < uVar6) {
                *(undefined1*)(bitStreamPtr + 0x1c) = 1;
            } else {
                bVar2 = *(byte*)((uVar6 >> 3) + *(int*)(bitStreamPtr + 0xc));
                *(uint*)(bitStreamPtr + 0x18) = uVar5 + 2;
                if ((bVar2 & (byte)(1 << ((byte)uVar6 & 7))) != 0) {
                    // Read a string or data into thisPtr+0x1fb
                    FUN_004a9d10(bitStreamPtr, thisPtr + 0x1fb);
                }
            }
            // Read a 32-bit value
            FUN_0064b9e0(0x20, &bitStreamPtr);
            if (bitStreamPtr != 0xffffffff) {
                FUN_007f8750(bitStreamPtr); // handle object ID?
            }
            // Read another 32-bit value
            FUN_0064b9e0(0x20, &bitStreamPtr);
            uVar5 = bitStreamPtr;
            if ((bitStreamPtr != 0xffffffff) && (bitStreamPtr != thisPtr[0x7a8])) {
                (**(code**)(*thisPtr + 0x28))(0x80); // virtual call
                thisPtr[0x7a8] = uVar5; // store new ID
            }
            // Read another 32-bit value
            FUN_0064b9e0(0x20, &bitStreamPtr);
            if (bitStreamPtr != 0) {
                FUN_007f82a0(bitStreamPtr); // handle another object?
            }
            // Read another bit (seventh)
            uVar5 = *(uint*)(bitStreamPtr + 0x18);
            if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
                *(undefined1*)(bitStreamPtr + 0x1c) = 1;
                bVar9 = false;
            } else {
                bVar9 = (*(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc)) & (byte)(1 << ((byte)uVar5 & 7))) != 0;
                *(uint*)(bitStreamPtr + 0x18) = uVar5 + 1;
            }
            FUN_00805c00(0); // some function
            cVar4 = FUN_0089c630(); // check something
            if (cVar4 != '\0') {
                FUN_008a1290(thisPtr + -0x16); // call on base object
            }
            if ((((thisPtr[0x7a7] != -1) && (thisPtr[0x7a8] != -1)) && (thisPtr[0x7a2] != 0)) && (!bVar9)) {
                FUN_009847c0(0xffffffff);
                if (*(int**)(DAT_0112b9b4 + 0x40) != (int*)0x0) {
                    (**(code**)(**(int**)(DAT_0112b9b4 + 0x40) + 0xc4))(thisPtr + -0x16);
                }
            }
        }
    }

    // Read eighth bit
    uVar5 = *(uint*)(bitStreamPtr + 0x18);
    if (*(uint*)(bitStreamPtr + 0x2c) < uVar5) {
        *(undefined1*)(bitStreamPtr + 0x1c) = 1;
        return;
    }
    bVar2 = *(byte*)((uVar5 >> 3) + *(int*)(bitStreamPtr + 0xc));
    *(int*)(bitStreamPtr + 0x18) = *(int*)(bitStreamPtr + 0x18) + 1;
    if ((bVar2 & (byte)(1 << ((byte)uVar5 & 7))) != 0) {
        FUN_004a8ec0(0);
        FUN_004a9360(bitStreamPtr, local_8);
        iVar7 = FUN_004a8f00();
        if (iVar7 == 0) {
            if ((local_8[0] != -0x1e98fd1) && ((thisPtr[0x1bd] == 0 || (thisPtr[0x1bd] == 0x48))) {
                FUN_004547e0(-(uint)(thisPtr != (int*)0x58) & (uint)thisPtr, local_8, 0);
            }
        } else {
            bitStreamPtr = 0;
            cVar4 = (**(code**)(*(int*)(iVar7 + -0x58) + 0x10))(0x4ecfbe13, &bitStreamPtr);
            if ((cVar4 != '\0') && (unaff_retaddr != 0)) {
                (**(code**)(thisPtr[-0x16] + 600))(unaff_retaddr);
                return;
            }
        }
    }
    return;
}