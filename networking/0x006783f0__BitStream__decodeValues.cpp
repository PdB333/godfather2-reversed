// FUNC_NAME: BitStream::decodeValues

void __thiscall BitStream::decodeValues(byte flags, byte*& inputPtr, ushort* outputArray)
{
    byte bVar1;
    bool bVar2;
    bool bVar3;
    byte* pbVar4 = inputPtr;
    byte* pbVar5;
    byte bVar6;
    ushort uVar7;
    int iVar8;
    byte bVar9;
    short sVar10;
    ushort uVar11;
    byte bVar12;
    ushort uVar13;
    short sVar14;
    short sVar15;
    bool bVar16;
    ushort local_20;
    ushort local_1c;
    int local_14;
    ushort* local_8;

    uVar13 = 0;
    bVar6 = 0;
    uVar11 = 0;
    local_1c = 0;

    if (*(char*)(this + 8) == '\0')
    {
        // Simple decoding mode
        uVar13 = 0;
        local_1c = 0;
        uVar11 = 0;

        if ((flags & 4) == 0)
        {
            if ((flags & 1) != 0)
            {
                uVar11 = (ushort)*pbVar4; // Read literal count (1 byte)
                pbVar4++;
            }
            if ((flags & 2) != 0)
            {
                bVar6 = *pbVar4; // Read match count (1 byte)
                goto LAB_00678756;
            }
        }
        else
        {
            uVar11 = (ushort)(*pbVar4 & 0xf); // Literal count from low nibble
            bVar6 = *pbVar4 >> 4;             // Match count from high nibble
LAB_00678756:
            local_1c = (ushort)bVar6;
            uVar13 = (ushort)bVar6;
            pbVar4++;
        }

        sVar15 = 0; // matchIndex
        sVar14 = 0; // literalIndex

        if ((int)(short)uVar13 + (int)(short)uVar11 != 0)
        {
            uVar7 = 0; // running value
            do
            {
                bVar6 = *pbVar4; // control byte with 4 nibbles (each 2 bits)
                pbVar4++;
                local_14 = 0;
                do
                {
                    // Process literal set (first group)
                    if (sVar14 < (short)uVar11)
                    {
                        if ((bVar6 & 1) == 0)
                        {
                            // 1-byte delta
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                        else
                        {
                            // 2-byte value
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                    }
                    else
                    {
                        if ((short)local_1c <= sVar15) break;
                        if ((bVar6 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                        }
                        outputArray[sVar15 + 0x42] = uVar7;
                        sVar15++;
                    }

                    // Process match set (second group) – nibble bit 1
                    if (sVar14 < (short)uVar11)
                    {
                        if ((bVar6 >> 1 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                    }
                    else
                    {
                        if ((short)local_1c <= sVar15) break;
                        if ((bVar6 >> 1 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                        }
                        outputArray[sVar15 + 0x42] = uVar7;
                        sVar15++;
                    }

                    // Process nibble bit 2
                    if (sVar14 < (short)uVar11)
                    {
                        if ((bVar6 >> 2 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                    }
                    else
                    {
                        if ((short)local_1c <= sVar15) break;
                        if ((bVar6 >> 2 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                        }
                        outputArray[sVar15 + 0x42] = uVar7;
                        sVar15++;
                    }

                    // Process nibble bit 3
                    if (sVar14 < (short)uVar11)
                    {
                        if ((bVar6 >> 3 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                            outputArray[sVar14 + 1] = uVar7;
                            sVar14++;
                        }
                    }
                    else
                    {
                        if ((short)local_1c <= sVar15) break;
                        if ((bVar6 >> 3 & 1) == 0)
                        {
                            uVar7 = uVar7 + *pbVar4;
                            pbVar4++;
                        }
                        else
                        {
                            bVar1 = *pbVar4;
                            pbVar5 = pbVar4 + 1;
                            pbVar4 += 2;
                            uVar7 = (ushort)bVar1 * 0x100 + (ushort)*pbVar5;
                        }
                        outputArray[sVar15 + 0x42] = uVar7;
                        sVar15++;
                    }

                    local_14 += 4;
                    bVar6 = bVar6 >> 4; // next nibble
                } while (local_14 < 8);
            } while ((int)sVar15 + (int)sVar14 < (int)(short)uVar13 + (int)(short)uVar11);
        }

        outputArray[0] = uVar11; // Store literal count
        outputArray[0x41] = local_1c; // Store match count
        inputPtr = pbVar4;
        return;
    }

    // Complex decoding mode
    bVar1 = 0;
    bVar3 = false;
    switch(flags & 3)
    {
    case 0:
        local_1c = 0;
        uVar11 = 0;
        goto switchD_00678434_default;
    case 1:
        bVar12 = *pbVar4 & 0xf;     // Literal count from low nibble
        bVar9 = *pbVar4 >> 4;       // Match count from high nibble
        break;
    case 3:
        bVar3 = true;               // Three-byte mode?
    case 2:
        bVar12 = *pbVar4;           // Literal count (1 byte)
        pbVar4++;
        bVar9 = *pbVar4;            // Match count (1 byte)
        break;
    default:
        goto switchD_00678434_default;
    }
    uVar11 = (ushort)bVar12;
    local_1c = (ushort)bVar9;
    pbVar4++;

switchD_00678434_default:
    bVar12 = 0;
    sVar15 = 0; // literalIndex
    local_8 = outputArray + 1;
    sVar10 = 0; // matchIndex
    sVar14 = 0;
    bVar2 = false; // flag for half-byte alignment

    do
    {
        if (sVar15 < (short)uVar11)
        {
            local_14 = (int)sVar15;
            sVar15 = sVar15 + 1;
            bVar16 = local_14 == 0;
            if (bVar16)
            {
                local_8 = outputArray + 1;
                uVar13 = 0;
                bVar6 = flags >> 4 & 1; // Flag bit 4 for literal delta mode?
            }
            else
            {
LAB_00678517:
                if (!bVar16 && -1 < local_14)
                {
                    if ((flags & 0x40) == 0)
                    {
                        bVar6 = 0;
                    }
                    else if (sVar14 == 0)
                    {
                        if (bVar2)
                        {
                            bVar12 = *pbVar4 & 0xf;
                            pbVar4++;
                            bVar2 = false;
                            sVar14 = 3;
                            bVar1 = bVar12;
                            bVar6 = bVar12;
                        }
                        else
                        {
                            bVar12 = *pbVar4 >> 4;
                            bVar2 = true;
                            sVar14 = 3;
                            bVar1 = bVar12;
                            bVar6 = bVar12;
                        }
                    }
                    else
                    {
                        bVar12 = bVar12 >> 1;
                        sVar14 = sVar14 - 1;
                        bVar1 = bVar12;
                        bVar6 = bVar12;
                    }
                }
            }
        }
        else
        {
            if ((short)local_1c <= sVar10) break;
            local_14 = (int)sVar10;
            sVar10 = sVar10 + 1;
            bVar16 = local_14 == 0;
            if (!bVar16) goto LAB_00678517;
            local_8 = outputArray + 0x42;
            bVar6 = flags >> 5 & 1; // Flag bit 5 for match delta mode?
            uVar13 = 0;
        }

        if ((bVar6 & 1) == 0)
        {
            // 1-byte delta
            if (bVar2)
            {
                pbVar5 = pbVar4 + 1;
                local_20 = (ushort)(byte)(*pbVar4 << 4);
                local_20 = local_20 + (pbVar4[1] >> 4);
            }
            else
            {
                local_20 = (ushort)*pbVar4;
                pbVar5 = pbVar4 + 1;
            }
        }
        else if (bVar3)
        {
            // 3-byte value (with nibble alignment)
            if (bVar2)
            {
                pbVar5 = pbVar4 + 2;
                local_20 = (ushort)(byte)(*pbVar4 << 4) * 0x100 + (ushort)pbVar4[1] * 0x10 +
                           (ushort)(*pbVar5 >> 4);
                bVar12 = bVar1;
            }
            else
            {
                local_20 = (ushort)*pbVar4 * 0x100 + (ushort)pbVar4[1];
                pbVar5 = pbVar4 + 2;
            }
        }
        else if (bVar2)
        {
            // 2-byte value with nibble alignment
            local_20 = (char)(*pbVar4 << 4) * 0x10 + (ushort)pbVar4[1];
            pbVar5 = pbVar4 + 2;
            bVar2 = false;
        }
        else
        {
            // 2-byte value with nibble alignment (alternate)
            pbVar5 = pbVar4 + 1;
            local_20 = (char)*pbVar4 * 0x10 + (ushort)(pbVar4[1] >> 4);
            bVar2 = true;
        }

        uVar13 = uVar13 + local_20;
        local_8[local_14] = uVar13;
        pbVar4 = pbVar5;
    } while( true );

    // Post-processing for match array
    if ((flags & 4) != 0)
    {
        iVar8 = (int)(short)local_1c;
        while (-1 < iVar8 + -1)
        {
            outputArray[iVar8 + 0x42] = outputArray[iVar8 + 0x41];
            iVar8 = iVar8 - 1;
        }
        local_1c = local_1c + 1;
    }

    if ((local_1c & 1) != 0)
    {
        iVar8 = (int)(short)local_1c;
        local_1c = local_1c + 1;
        outputArray[iVar8 + 0x42] = (outputArray + iVar8 + 0x42)[-1];
    }

    // Clean up half-byte alignment
    if (bVar2)
    {
        pbVar4 = pbVar4 + 1;
    }

    outputArray[0] = uVar11;
    outputArray[0x41] = local_1c;
    inputPtr = pbVar4;
    return;
}