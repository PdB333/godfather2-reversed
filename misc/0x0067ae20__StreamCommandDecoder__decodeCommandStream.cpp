// FUNC_NAME: StreamCommandDecoder::decodeCommandStream

void StreamCommandDecoder::decodeCommandStream(byte* data, uint16 dataLength, int param3, int param4, int param5, int param6, int param7, int param8, int param9)
{
    byte b;
    byte* cursor;
    short sVar4;
    byte* ptr148; // +0x148 in local? Actually local variables named by offsets
    uint uVar10;
    uint local_168;
    uint local_164;
    byte* local_160;
    int* local_15c;
    int local_158;
    byte* local_154;
    uint local_150;
    int local_14c;
    byte* local_148;
    short local_144;
    int local_140;
    int local_13c;
    int local_138;
    int local_134;
    int local_130;
    uint local_12c;
    // Stack arrays for short stacks
    short asStack_10e[64];
    short auStack_8c[64];
    short local_c;
    short local_a;
    short local_8;
    short local_6;
    int local_170;
    int local_16c;
    // Save/restore state from offsets +0x38, +0x3a, +0x3c (likely 32-bit coordinates)
    uint64 savedX, savedY, savedZ;
    // Flag at +0x0d: 0 or 1 indicates path open
    // Flag at +0x02: if non-zero, initial state

    b = *data;
    cursor = data + 1;
    sVar4 = 0;
    local_148 = 0;
    local_150 = 0;
    local_164 = 0;
    local_160 = 0;
    local_13c = 0;
    local_140 = 1; // some default value
    // local_168 = b (combined with previous top? Not used)
    local_168 = (b & 0xFF) << 24; // Actually the code does CONCAT31, but we ignore
    if ((char)b < 0) // High bit set -> nested command block
    {
        if ((b & 0x40) != 0)
        {
            // Skip one byte? Actually read count and then skip variable length strings?
            b = *cursor;
            uVar10 = b;
            cursor = data + 2;
            if (b != 0)
            {
                do {
                    uVar10--;
                    cursor += *cursor + 2;
                } while (uVar10 != 0);
            }
        }
        local_168 = (b & 0x3f); // Number of sub-commands
        if (local_168 != 0)
        {
            do {
                FUN_00678a20(this, &cursor, &local_140, &param3);
                uVar10 = local_12c & 0xFFFF;
                *(int*)(*(int*)(this + 4) + 4) = *(int*)(*(int*)(this + 4) + 0xC) + *(int*)(this + 0x2C) + local_130; // Some offset computation
                byte* tempBuffer = (byte*)FUN_00673070(); // Allocate temp buffer
                local_15c = (int*)*(int*)(this + 4);
                if (uVar10 != 0)
                {
                    int tempOffset = local_15c[1];
                    int base = *local_15c;
                    if (uVar10 != 0)
                    {
                        byte* src = (byte*)(base + tempOffset);
                        byte* dst = tempBuffer;
                        memmove(dst, src, uVar10); // Simplified memcpy
                    }
                    local_15c[1] = tempOffset + uVar10;
                }
                // Recursive call for sub-command
                decodeCommandStream(tempBuffer, local_130, local_12c, local_140, local_138, local_13c, local_134, param9);
                // Free tempBuffer? The code checks if tempBuffer != 0 then frees via something
                if (tempBuffer)
                {
                    *(int*)(*(int*)(*(int*)this + 0xC) + *(int*)(tempBuffer - 8) * 4) = 0;
                    int* piVar1 = (int*)(*(int*)this + 4);
                    *piVar1 = *piVar1 - 1;
                    (*DAT_01206694)(tempBuffer - 0x10); // Custom free
                }
                local_168--;
            } while (local_168 != 0);
            return;
        }
    }
    else
    {
        // Initialize stack arrays
        local_110 = 0;
        local_8e = 0;
        local_c = 0;
        local_a = 0;
        FUN_006783f0(this, local_168, &cursor, &local_110); // Parse header? Uses local_168 which is original b?
        if ((local_168 & 8) != 0)
        {
            // Skip a block with string lengths
            b = *cursor;
            uVar10 = b;
            cursor++;
            if (b != 0)
            {
                do {
                    uVar10--;
                    cursor += *cursor + 2;
                } while (uVar10 != 0);
            }
        }
        // Save current transform (3 8-byte values? Actually likely 32-bit each, but saved as 8 bytes)
        savedX = *(uint64*)(this + 0x38);
        savedY = *(uint64*)(this + 0x3A);
        savedZ = *(uint64*)(this + 0x3C);
        FUN_0067bc80(param5, param6, param7, param8);
        *(byte*)(this + 0x0D) = 0; // Reset dirty flag
        if (*(byte*)(this + 2) == 0) // First time?
        {
            // Main command loop
            // local_160 is end pointer: data + (dataLength - 1)
            local_160 = data + (dataLength - 1);
            local_8 = 0;
            local_6 = 0;
            local_c = 0;
            local_a = 0;
            local_148 = cursor;
            local_144 = 0;
            local_164 = 0xFFFFFFFF;
            byte* endPtr = local_160;
            while ((local_148 < endPtr) || (local_148 == endPtr && local_144 == 0))
            {
                FUN_00678e60(&local_110, &local_164); // Read command word
                short command = (short)local_164;
                if (command == 0)
                {
                    // End path? If dirty, close path, then moveTo current position
                    if (*(byte*)(this + 0x0D))
                    {
                        FUN_00677e80(); // endPath
                        *(byte*)(this + 0x0D) = 0;
                    }
                    FUN_0067bd40((int)(short)local_140 << 16, &local_170, &local_16c);
                    int x = (uint)local_170 >> 16;
                    int y = (uint)local_16c >> 16;
                    FUN_00677f80(x, y, 1); // moveTo
                    *(byte*)(this + 0x0D) = 1;
                }
                else if (command == 1)
                {
                    // Relative move? Load two random-like values
                    local_16c = FUN_00676010();
                    local_16c += param8;
                    int iVar12 = (int)(short)local_140;
                    int iVar7 = FUN_00676010();
                    local_170 = FUN_00676010();
                    local_170 += iVar7 + param7;
                    FUN_0067bd40(iVar12 << 16, &local_170, &local_16c);
                    x = (uint)local_170 >> 16;
                    y = (uint)local_16c >> 16;
                    FUN_00677f80(x, y, 1);
                    endPtr = local_160;
                }
                else if (command == 2)
                {
                    // LineTo from stack
                    FUN_0067bd40((int)(short)local_140 << 16, &local_170, &local_16c);
                    FUN_0067bd40((int)(short)local_13c << 16, &local_14c, &local_158);
                    FUN_0067bd40((int)(short)local_138 << 16, &local_15c, &local_168);
                    x = (uint)local_170 >> 16;
                    y = (uint)local_16c >> 16;
                    int x2 = (uint)local_14c >> 16;
                    int y2 = (uint)local_158 >> 16;
                    int x3 = (uint)local_15c >> 16;
                    int y3 = (uint)local_168 >> 16;
                    FUN_00677f80(x, y, 0); // ???
                    FUN_00677f80(x2, y2, 0);
                    FUN_00677f80(x3, y3, 1);
                }
            }
            // Restore saved transform
            *(uint64*)(this + 0x38) = savedX;
            *(uint64*)(this + 0x3A) = savedY;
            *(uint64*)(this + 0x3C) = savedZ;
            if (*(byte*)(this + 0x0D))
            {
                FUN_00677e80();
                *(byte*)(this + 0x0D) = 0;
            }
        }
        else
        {
            // Second branch: parse opcodes
            do {
                b = *cursor;
                cursor++;
                switch (b >> 4)
                {
                case 0: // End
                    if (*(byte*)(this + 0x0D))
                    {
                        FUN_00677e80();
                        *(byte*)(this + 0x0D) = 0;
                    }
                    *(uint64*)(this + 0x38) = savedX;
                    *(uint64*)(this + 0x3A) = savedY;
                    *(uint64*)(this + 0x3C) = savedZ;
                    return;
                case 1: // Break? (falls through to push)
                    break;
                case 2: // Push from asStack_10e
                    local_c = asStack_10e[b & 0xF];
                    FUN_0067bd40((int)local_c << 16, &local_170, &local_16c);
                    sVar4 = (short)((uint)local_170 >> 16);
                    // sVar11 = (short)((uint)local_16c >> 16);
                    // goto unified code
                    goto finishOp;
                case 3: // Push from auStack_8c
                    local_a = auStack_8c[b & 0xF];
                    sVar4 = local_c;
                    break;
                case 4: // MoveTo
                    if (*(byte*)(this + 0x0D))
                        FUN_00677e80();
                    FUN_0067bd40((int)sVar4 << 16, &local_170, &local_16c);
                    sVar4 = (short)((uint)local_170 >> 16);
                    FUN_00677f80(sVar4, (short)((uint)local_16c >> 16), 1);
                    *(byte*)(this + 0x0D) = 1;
                    goto loop;
                case 5: // Another move
                    if (*(byte*)(this + 0x0D))
                        FUN_00677e80();
                    FUN_0067bd40((int)sVar4 << 16, &local_170, &local_16c);
                    sVar4 = (short)((uint)local_170 >> 16);
                    FUN_00677f80(sVar4, (short)((uint)local_16c >> 16), 1);
                    *(byte*)(this + 0x0D) = 1;
                    goto loop;
                case 6: // Multiple lines
                    FUN_0067bd40((int)sVar4 << 16, &local_170, &local_16c);
                    sVar4 = (short)((uint)local_170 >> 16);
                    // sVar11 = (short)((uint)local_16c >> 16);
                    // Also process local_148/local_150 and local_164/local_160
                    FUN_0067bd40((int)(short)local_148 << 16, &local_14c, &local_158);
                    local_148 = (byte*)((uint)local_14c >> 16);
                    local_150 = (uint)local_158 >> 16;
                    FUN_0067bd40((int)(short)local_164 << 16, &local_15c, &local_168);
                    local_164 = (uint)local_15c >> 16;
                    local_160 = (byte*)((uint)local_168 >> 16);
                    FUN_00677f80(sVar4, (short)((uint)local_16c >> 16), 0);
                    FUN_00677f80((int)(short)local_148, (int)(short)local_150, 0);
                    FUN_00677f80((int)(short)local_160, (int)(short)local_164, 1);
                    goto loop;
                case 7: // Similar to 6
                    FUN_0067bd40((int)sVar4 << 16, &local_170, &local_16c);
                    sVar4 = (short)((uint)local_170 >> 16);
                    FUN_0067bd40((int)(short)local_148 << 16, &local_14c, &local_158);
                    local_148 = (byte*)((uint)local_14c >> 16);
                    local_150 = (uint)local_158 >> 16;
                    FUN_0067bd40((int)(short)local_164 << 16, &local_15c, &local_168);
                    // fall through to default label
                default: // default case handles bezier curve?
                    // This complex default case loads multiple random values and transforms
                    // Followed by calls to FUN_00677f80
                    // ...
                    goto loop;
                }
                // For opcodes 1,2,3 we have break; after switch, code continues:
                FUN_0067bd40((int)sVar4 << 16, &local_170, &local_16c);
                sVar4 = (short)((uint)local_170 >> 16);
                // sVar11 = (short)((uint)local_16c >> 16);
            finishOp:
                // sVar11 and sVar4 set
                FUN_00677f80(sVar4, sVar11, 1);
            loop:
                ;
            } while (true);
        }
    }
    return;
}