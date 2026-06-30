// FUNC_NAME: CImageBuffer::init
int __fastcall CImageBuffer::init(undefined4 param_3, char param_2, undefined4 param_4, int param_5,
                                  undefined4 param_6, undefined4 param_7, undefined4 param_8, char param_9,
                                  byte param_10, char param_11, int param_12, int param_13)
{
    int thisPtr = DAT_012066a0;  // global singleton instance
    DAT_012058ba = 1;           // enable flag

    if (thisPtr == 0) {
        return 0;
    }

    // Store parameters into the object
    *(undefined4 *)(thisPtr + 0x222c) = param_3;  // +0x222c: data/format
    *(bool *)(thisPtr + 0x2207) = param_12 != 0;  // +0x2207: bool flag
    *(undefined1 *)(thisPtr + 0x2208) = (byte)1;   // +0x2208: byte (always 1)
    *(char *)(thisPtr + 0x2204) = param_2;         // +0x2204: char (alpha transparency? scale?)
    int iVar3 = (-(uint)(param_2 != (char)0) & 2) + 2;  // 2 if param_2==0, 4 otherwise
    *(int *)(thisPtr + 0x2200) = iVar3;            // +0x2200: mip level count?
    if (iVar3 < param_13) {
        *(int *)(thisPtr + 0x2200) = param_13;
    }
    if (0x10 < *(int *)(thisPtr + 0x2200)) {
        *(undefined4 *)(thisPtr + 0x2200) = 0x10;  // cap at 16
    }
    *(undefined1 *)(thisPtr + 0x2205) = param_10;   // +0x2205: byte
    *(char *)(thisPtr + 0x2206) = param_11;         // +0x2206: char
    if ((param_11 != (char)0) || (param_2 != (char)0)) {
        byte uVar2 = 1;
    } else {
        byte uVar2 = 0;
    }
    *(short *)(thisPtr + 0x221c) = in_AX;          // +0x221c: uninitialized (compiler artifact)
    *(undefined1 *)(thisPtr + 0x2209) = uVar2;     // +0x2209: byte flag
    *(undefined4 *)(thisPtr + 0x2214) = param_4;   // +0x2214: width/stride?
    *(undefined4 *)(thisPtr + 0x220c) = 0;         // +0x220c: zero
    *(undefined4 *)(thisPtr + 0x2210) = 0;         // +0x2210: zero
    *(int *)(thisPtr + 0x2218) = param_5;          // +0x2218: pointer to palette/table?
    *(undefined4 *)(thisPtr + 0x2220) = param_6;   // +0x2220: unknown
    *(undefined4 *)(thisPtr + 0x2224) = param_7;   // +0x2224: unknown
    *(undefined4 *)(thisPtr + 0x2228) = param_8;   // +0x2228: unknown
    *(undefined4 *)(thisPtr + 0x24) = 0;           // +0x24: clear

    // Call sub-function with param_7 and computed index from param_5
    FUN_00676750(thisPtr, param_7, (int)*(short *)(param_5 + -2 + in_AX * 2));

    int local_8 = *(int *)(thisPtr + 0x3c);   // +0x3c: height?
    int iVar3 = *(int *)(thisPtr + 0x38);     // +0x38: width?
    *(undefined4 *)(thisPtr + 0x48) = 0;      // +0x48: flag
    if ((0xb503 < local_8 - iVar3) || (0xb503 < *(int *)(thisPtr + 0x44) - *(int *)(thisPtr + 0x40))) {
        *(undefined4 *)(thisPtr + 0x48) = 1;  // set flag if size difference exceeds threshold
    }

    int local_4 = 0;
    do {
        local_8 = (local_8 + 0x40) >> 6;
        iVar3 = (iVar3 - 0x40) >> 6;
        int iVar5 = (local_8 - iVar3) + 1;

        if ((local_4 == 0) && (*(char *)(thisPtr + 0x2209) == (char)0)) {
            // First level, flag = 0
            undefined4* puVar4 = (undefined4*)0x0;
LAB_006772c8:
            *(undefined4**)(thisPtr + 0x160) = puVar4;  // +0x160: high-res buffer pointer
            if (puVar4 != (undefined4*)0x0) {
                puVar4 = puVar4 - iVar3;
            }
            *(undefined4**)(thisPtr + 0x15c) = puVar4;  // +0x15c: offset buffer
            *(int *)(thisPtr + 0x164) = iVar3;           // +0x164: start index
            iVar3 = *(int *)(thisPtr + 0x40);            // update from another field
            *(int *)(thisPtr + 0x168) = local_8;         // +0x168: end index
            local_8 = *(int *)(thisPtr + 0x44);
        } else {
            // Second level or flag set
            undefined4* puVar4;
            if (iVar5 < 0x21) {
                if (local_4 == 0) {
                    puVar4 = (undefined4*)(thisPtr + 0xdc);  // +0xdc: local buffer for level 0?
                } else {
                    puVar4 = (undefined4*)(thisPtr + 0x4c);  // +0x4c: local buffer for level 1?
                }
            } else {
                puVar4 = (undefined4*)FUN_00673070();  // allocate new memory
            }
            undefined4* puVar6 = puVar4;
            if (0 < iVar5) {
                for (; iVar5 != 0; iVar5--) {
                    *puVar6 = 0;
                    puVar6++;
                }
            }
            if (local_4 == 0) goto LAB_006772c8;
            // Set up second level pointers
            *(undefined4**)(thisPtr + 0xd0) = puVar4;     // +0xd0: low-res buffer
            *(undefined4**)(thisPtr + 0xcc) = puVar4 - iVar3; // +0xcc: offset buffer
            *(int *)(thisPtr + 0xd4) = iVar3;             // +0xd4: start index
            *(int *)(thisPtr + 0xd8) = local_8;           // +0xd8: end index
        }
        local_4++;
        if (1 < local_4) {
            *(undefined4 *)(thisPtr + 0x21f8) = 0;   // +0x21f8: clear
            FUN_00676300();                           // call finalize/init
            *(undefined4 *)(thisPtr + 0x1c) = 0;     // +0x1c: clear
            if (param_9 == (char)3) {
                FUN_00676fa0(thisPtr);                // extra initialization for type 3
            }
            return thisPtr;
        }
    } while (true);
}