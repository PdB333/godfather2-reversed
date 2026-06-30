// FUNC_NAME: Texture::createFromParams
int __fastcall Texture::createFromParams(void* thisPtr, char format, void* param3, void* param4, int param5, void* param6, void* param7, void* param8, char param9, unsigned char param10, char param11, int param12, int param13)
{
    // Note: in_AX (short) is passed in AX register, likely width/height or mip level
    short in_AX;
    int iVar1 = globalTextureManager; // DAT_012066a0
    byte bVar;
    int iVar3;
    uint* puVar4;
    int iVar5;
    uint* puVar6;
    int width, height;

    globalTextureManager->initialized = 1; // DAT_012058ba
    if (globalTextureManager == 0) {
        return 0;
    }

    // Store parameters into the texture object
    globalTextureManager->field_222c = (int)param3;  // +0x222c
    globalTextureManager->field_2207 = (param12 != 0); // +0x2207 (bool)
    globalTextureManager->field_2208 = 1;              // +0x2208 (byte)
    globalTextureManager->field_2204 = format;          // +0x2204 (char)

    // Determine initial mip level based on format flag
    iVar3 = (-(uint)(format != '\0') & 2) + 2; // 2 if format==0, 4 otherwise
    globalTextureManager->field_2200 = iVar3;   // +0x2200 (int)
    if (iVar3 < param13) {
        globalTextureManager->field_2200 = param13;
    }
    if (globalTextureManager->field_2200 > 0x10) {
        globalTextureManager->field_2200 = 0x10;
    }

    globalTextureManager->field_2205 = param10;          // +0x2205 (byte)
    globalTextureManager->field_2206 = param11;          // +0x2206 (char)

    bVar = 0;
    if ((param11 != '\0') || (format != '\0')) {
        bVar = 1;
    }
    globalTextureManager->field_2209 = bVar;             // +0x2209 (byte)

    globalTextureManager->field_221c = in_AX;            // +0x221c (short) - register value
    globalTextureManager->field_2214 = (int)param4;      // +0x2214
    globalTextureManager->field_220c = 0;                // +0x220c (int)
    globalTextureManager->field_2210 = 0;                // +0x2210 (int)
    globalTextureManager->field_2218 = param5;           // +0x2218 (int) - possibly pointer to mip offsets
    globalTextureManager->field_2220 = (int)param6;      // +0x2220
    globalTextureManager->field_2224 = (int)param7;      // +0x2224
    globalTextureManager->field_2228 = (int)param8;      // +0x2228
    globalTextureManager->field_24 = 0;                  // +0x24

    // Initialize something related to mip data from param7 and a short at param5+in_AX*2
    FUN_00676750(globalTextureManager, param7, (int)*(short*)(param5 - 2 + in_AX * 2));

    // Get current width/height from the object
    int currentWidth = globalTextureManager->surfaceWidth;   // +0x3c
    int currentHeight = globalTextureManager->surfaceHeight; // +0x38
    int storedWidth = globalTextureManager->storedWidth;     // +0x44
    int storedHeight = globalTextureManager->storedHeight;   // +0x40

    globalTextureManager->field_48 = 0; // flag

    // Check if dimensions exceed a threshold (0xb503 = 46339)
    if ((currentWidth - currentHeight > 0xb503) || (storedWidth - storedHeight > 0xb503)) {
        globalTextureManager->field_48 = 1; // set flag
    }

    int stage = 0;
    do {
        // Compute new width/height for this mip level (divide by 64 with rounding)
        int mipWidth = (currentWidth + 0x40) >> 6;
        int mipHeight = (currentHeight + -0x40) >> 6;
        // Actually the second is (currentHeight - 64) >> 6, but careful with sign
        // The decompiler shows: local_8 + 0x40 >> 6 and iVar3 + -0x40 >> 6
        // We'll implement as integer math
        int tempWidth = (currentWidth + 64) / 64;
        int tempHeight = (currentHeight - 64) / 64; // note: may be negative

        int mipCount = (tempWidth - tempHeight) + 1;

        if (stage == 0 && globalTextureManager->field_2209 == '\0') {
            // First stage and no mip flag: use null pointers?
            puVar4 = null;
            goto set_surface;
        }
        else {
            if (mipCount < 0x21) {
                if (stage == 0) {
                    puVar4 = (uint*)(globalTextureManager + 0xdc); // static buffer
                }
                else {
                    puVar4 = (uint*)(globalTextureManager + 0x4c); // static buffer
                }
            }
            else {
                puVar4 = (uint*)FUN_00673070(); // allocate dynamic memory
            }
            puVar6 = puVar4;
            if (0 < mipCount) {
                for (int i = 0; i < mipCount; i++) {
                    *puVar6 = 0;
                    puVar6++;
                }
            }
            if (stage == 0) {
set_surface:
                globalTextureManager->surfacePtr   = puVar4; // +0x160
                globalTextureManager->adjustedPtr  = puVar4 ? (uint*)(puVar4 - tempHeight) : 0; // +0x15c
                globalTextureManager->surfaceStart = tempHeight; // +0x164
                globalTextureManager->surfaceEnd   = tempWidth;  // +0x168
                // Update for next stage
                currentHeight = globalTextureManager->storedHeight; // +0x38 (or 0x40? original code uses iVar3 from earlier)
                currentWidth = globalTextureManager->storedWidth;   // +0x3c? Actually uses iVar3 and local_8 from 0x40/0x44?
                // The original code: iVar3 = *(int *)(iVar1 + 0x40); local_8 = *(int *)(iVar1 + 0x44);
                // That sets for the second stage. So we read them again.
                stage = 1; // will cause loop to exit after second iteration
                continue;
            }
            else {
                globalTextureManager->mipChainPtr = puVar4;   // +0xd0
                globalTextureManager->mipAdjusted  = (uint*)(puVar4 - tempHeight); // +0xcc
                globalTextureManager->mipStart     = tempHeight; // +0xd4
                globalTextureManager->mipEnd       = tempWidth;  // +0xd8
            }
        }
        stage++;
        if (stage > 1) {
            // Final initialization
            globalTextureManager->field_21f8 = 0; // +0x21f8
            FUN_00676300();
            globalTextureManager->field_1c = 0;   // +0x1c
            if (param9 == 0x03) {
                FUN_00676fa0(globalTextureManager); // post init
            }
            return (int)globalTextureManager;
        }
    } while (true);
}