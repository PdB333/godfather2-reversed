// FUNC_NAME: AudioDataManager::decodeVariableLengthData
byte* __fastcall decodeVariableLengthData(byte* in_EAX, uint param_2, float param_3, float* param_4)
{
    byte* pbVar1;
    byte bVar2;
    byte* pbVar3;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    uint uVar7;
    float fVar8;
    float fVar9;

    fVar8 = DAT_00e2b1a4; // Some constant, likely 1.0f
    bVar2 = *in_EAX;
    uVar5 = bVar2 & 0xf; // Lower nibble: data type
    uVar4 = (uint)in_EAX[1] << 4 | (uint)(bVar2 >> 4); // Upper nibble + next byte: count/offset

    if (uVar5 == 5) {
        // Type 5: Variable-length encoded data
        pbVar1 = (byte*)((*(ushort*)(in_EAX + 2) - 2) + (int)(in_EAX + 2)); // Pointer to data start
        pbVar3 = in_EAX + 4;
        if (uVar4 != 0) {
            while (true) {
                bVar2 = *pbVar3;
                uVar7 = (uint)pbVar3[1] << 4 | (uint)(bVar2 >> 4); // Next element's offset/count
                uVar5 = uVar7 - 1; // Adjusted offset
                uVar4 = uVar4 - 1;
                uVar6 = bVar2 & 0xf; // Sub-type
                if (param_2 < uVar5) break; // If requested position is before this element
                if (uVar6 == 0xe) {
                    uVar7 = uVar7 + 7 >> 3; // Bit count to byte count
                } else {
                    uVar7 = *(int*)(&DAT_00e2c2e0 + uVar6 * 4) * uVar7; // Size multiplier based on type
                }
                pbVar3 = pbVar3 + *(int*)(&DAT_00e2c2a4 + uVar6 * 4) + uVar7; // Advance to next element
                param_2 = param_2 - uVar5; // Decrease remaining offset
                param_3 = param_3 - (*(float*)(&DAT_00e2c320 + (uVar5 >> 8) * 4) * DAT_00e445d0 +
                                    *(float*)(&DAT_00e2c320 + (uVar5 & 0xff) * 4)); // Adjust time
                if (uVar4 == 0) {
                    return pbVar3; // Reached end of elements
                }
            }
            // Found the element containing the requested position
            if (uVar6 == 0xc) {
                *param_4 = 0.0f; // Zero value
                param_4[4] = 0.0f;
                return pbVar1;
            }
            if (uVar6 == 0xd) {
                *param_4 = DAT_00e2b1a4; // Constant value
                param_4[4] = fVar8;
                return pbVar1;
            }
            if ((bVar2 & 0xf) == 0) {
                FUN_0057c0f0(); // Some helper function
                *param_4 = param_3;
                param_4[4] = param_3;
                return pbVar1;
            }
            if (uVar6 == 0xe) {
                fVar9 = DAT_00e2b1a4;
                if ((pbVar3[(param_2 >> 3) + 2] >> ((byte)param_2 & 7) & 1) == 0) {
                    fVar9 = 0.0f;
                }
                *param_4 = fVar9;
                fVar9 = 0.0f;
                if ((pbVar3[(param_2 + 1 >> 3) + 2] >> ((byte)param_2 + 1 & 7) & 1) != 0) {
                    fVar9 = fVar8;
                }
                param_4[4] = fVar9;
                return pbVar1;
            }
            FUN_0057c390(uVar6, param_3); // Handle other types
            pbVar3 = pbVar1;
        }
        return pbVar3;
    }
    // Non-variable-length types
    if (uVar5 == 0xc) {
        fVar8 = 0.0f;
    } else if (uVar5 != 0xd) {
        if ((bVar2 & 0xf) == 0) {
            *param_4 = (float)((uint)*(uint3*)(in_EAX + 2) << 8); // 24-bit integer
            param_4[4] = *param_4;
        } else {
            if (uVar5 == 0xe) {
                fVar9 = DAT_00e2b1a4;
                if ((in_EAX[(param_2 >> 3) + 2] >> ((byte)param_2 & 7) & 1) == 0) {
                    fVar9 = 0.0f;
                }
                *param_4 = fVar9;
                fVar9 = 0.0f;
                if ((in_EAX[(param_2 + 1 >> 3) + 2] >> ((byte)param_2 + 1 & 7) & 1) != 0) {
                    fVar9 = fVar8;
                }
                param_4[4] = fVar9;
                return in_EAX + _UNK_00e2c2dc + (uVar4 + 7 >> 3); // Bit-aligned data
            }
            FUN_0057c390(uVar5, param_3);
        }
        goto LAB_0057c829;
    }
    *param_4 = fVar8;
    param_4[4] = fVar8;
LAB_0057c829:
    return in_EAX + *(int*)(&DAT_00e2c2a4 + uVar5 * 4) + *(int*)(&DAT_00e2c2e0 + uVar5 * 4) * uVar4;
}