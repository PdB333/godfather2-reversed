// FUNC_NAME: EARSScriptParser::parseToken
void EARSScriptParser::parseToken(
    int* context,          // +0x00: pointer to AI entity state? (Context structure)
    int* currentIndex,     // Accumulated character index (output as count)
    int* columnCounter,    // Column/benefit counter (output as benefit)
    float* outScore,       // Output score if applicable
    bool* outSuccess,      // Output success indicator (true if token parsed)
    int* tokenBuffer       // Pointer to token buffer (passed in EAX, base address for scanning)
)
{
    float local_3c = 0.0f;
    if (*context != 0) {
        // Read a value from entity state at offset +0x18 and multiply by a scalar (context[4])
        local_3c = (float)*(int*)(*context + 0x18) * (float)context[4];
    }
    float local_38 = 0.0f;
    if (context[1] != 0) {
        local_38 = (float)*(int*)(context[1] + 0x18) * (float)context[4];
    }
    local_38 = local_3c / local_38; // Ratio of two scaled values

    int local_48 = 0;
    if (outScore != nullptr) {
        *outScore = 0.0f;
    }
    if (outSuccess != nullptr) {
        *outSuccess = false;
    }

    int local_2c = 0;
    int local_28 = 0;
    uint local_24 = context[?]; // Actually uses an uninitialized local_24; assume it comes from a global or register
    local_24 = local_24 & 0xffff0000; // Keep only upper 16 bits (flags/index base)
    float local_44 = local_3c;
    int scanPtr = tokenBuffer; // Base scanning address from in_EAX
    int randomValue = FUN_004dd960(); // Random number or time seed

    int iVar2 = local_2c;
    do {
        int actionCount = 0;
        // Presumably retrieves next token/action count into local_34 (unused after? or used via local_24)
        char local_34[4];
        FUN_00487c70(&actionCount, local_34); // Populates actionCount and maybe modifies local_34

        // Consume actions: update indices and random values
        if (actionCount > 0) {
            do {
                local_2c = iVar2 + randomValue;
                randomValue = FUN_004dd960();
                local_28 = local_28 + 1;
                actionCount--;
                iVar2 = local_2c;
            } while (actionCount != 0);
        }
        *currentIndex += actionCount; // Accumulate total count

        if ((short)local_24 == 0) {
            return; // End of parsing (null)
        }
        if (context[1] == 0) {
            // Path when secondary entity pointer is null
            // Look up in context[0]'s 2D array (offset +0x44) using bytes of local_24 as row/col
            int* rowPtr = *(int**)(*context + 0x44 + ((local_24 >> 8) & 0xff) * 4);
            int* cellPtr = nullptr;
            if (rowPtr != nullptr) {
                cellPtr = rowPtr + (local_24 & 0xff);
            }
            if (cellPtr == nullptr || *cellPtr == 0) {
                local_48 = 0;
            }
            else if ((float)context[8] == DAT_00e2b05c) {
                // Execute some command with local_24 as parameter
                FUN_004cfec0(local_24);
                local_48 = local_24 & 0xffff; // Extract lower 16 bits as result
            }
        }
        else {
            // Path when secondary entity pointer exists
            int otherScanPtr = 0xffffffff;
            FUN_00487d50(&actionCount, &otherScanPtr, context[5]); // Get another action count and index
            // Consume those actions
            if (actionCount > 0) {
                do {
                    local_2c = iVar2 + randomValue;
                    randomValue = FUN_004dd960();
                    local_28 = local_28 + 1;
                    actionCount--;
                    iVar2 = local_2c;
                } while (actionCount != 0);
            }
            *currentIndex += actionCount;
            if ((int)otherScanPtr < 0) {
                goto LAB_00488049; // Use primary path
            }
            if (outSuccess != nullptr) {
                *outSuccess = true;
            }
            // Look up in context[1]'s 2D array (offset +0x44)
            int* rowPtr = *(int**)(context[1] + 0x44 + ((otherScanPtr & 0xffff) >> 8) * 4);
            int* cellPtr = nullptr;
            if (rowPtr != nullptr) {
                cellPtr = rowPtr + (otherScanPtr & 0xff);
            }
            if (cellPtr == nullptr || *cellPtr == 0) {
                local_48 = 0;
            }
            else {
                local_44 = (float)context[6] * local_3c; // Scale score
                if (outScore != nullptr && *outScore <= local_44 && local_44 != *outScore) {
                    *outScore = local_44;
                }
                local_48 = local_24 & 0xffff;
            }
        }

        // Update indices after processing each iteration
        local_2c = iVar2 + randomValue;
        float fVar3 = local_44;
        randomValue = FUN_004dd960();
        iVar2 = local_2c;
        local_28 = local_28 + 1;
        *currentIndex += 1;
        *columnCounter += 1;
        if (outScore != nullptr && *outScore <= fVar3 && fVar3 != *outScore) {
            *outScore = fVar3;
        }

        // Check for special token values (ASCII control characters)
        if ((short)local_24 == 0) {
            return;
        }
        if ((short)local_24 == 10) { // LF
            return;
        }
        if ((short)local_24 == 13) { // CR
            return;
        }

        // Token buffer scanning: look for specific characters in the buffer
        int iVar1 = local_2c + scanPtr;
        int local_18 = 0;
        undefined4 local_14 = 0;
        short local_10 = 0;
        int local_1c = iVar1;
        FUN_004dd960(); // Advance random state?
        // Check if current character is backslash (0x5c)
        if (local_10 == 0x5c) {
            local_18 = 0;
            local_14 = 0;
            local_10 = 0;
            local_1c = iVar1;
            int local_c = FUN_004dd960(); // Read another random?
            local_18 += local_c;
            FUN_004dd960();
            if (local_10 == 0x6e) { // 'n'
                return;
            }
        }
        // Reset and check for space (0x20)
        local_18 = 0;
        local_14 = 0;
        local_10 = 0;
        local_1c = iVar1;
        FUN_004dd960();
        if (local_10 == 0x20) {
            return;
        }
        // Check for '[' (0x5b) and '{' (0x7b)
        if ((short)local_24 == 0x5b || (short)local_24 == 0x7b) {
            return;
        }
    } while (true);
}