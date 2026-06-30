//FUNC_NAME: InputManager::findBestMatchingEntry
int __fastcall InputManager::findBestMatchingEntry(uint inputFlags)
{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    int bestIndex;
    uint bestScore;
    uint *tablePtr;

    // Quick check if inputFlags matches the last stored value
    if (inputFlags == g_lastMatchedFlags) {
        return g_bestMatchIndex;
    }

    uint invertedFlags = ~inputFlags;
    g_bestMatchIndex = 0;
    bestScore = 0;
    uint mask = invertedFlags & 0xfffffff5; // Clear bits 1 and 3? (0xA inverted)
    tablePtr = &g_inputMappingTable[0]; // DAT_01198f54
    int row = 2;
    do {
        // Check 5 entries per row: offsets -27, 0, +27, +54, +81 relative to tablePtr
        // Entry 1: tablePtr[-27]
        uVar1 = tablePtr[-27];
        if ((((mask & uVar1) == 0) &&
            (((uVar3 = (uVar1 ^ inputFlags) & 0x78c, uVar3 == 0 ||
              ((uVar3 == 8 && ((inputFlags & 8) != 0)) || ((uVar1 & 0xfffff8ff) == 0)))) &&
             ((uVar3 = (uVar1 & inputFlags) - (invertedFlags & uVar1), bestScore < uVar3 &&
              (g_bestMatchIndex = row - 2, bestScore = uVar3, uVar1 == inputFlags)))))) ||
            // Entry 2: tablePtr[0]
            (((uVar1 = *tablePtr, (mask & uVar1) == 0 &&
              (((uVar3 = (uVar1 ^ inputFlags) & 0x78c, uVar3 == 0 || ((uVar3 == 8 && ((inputFlags & 8) != 0)))
                ) || ((uVar1 & 0xfffff8ff) == 0)))) &&
             ((uVar3 = (uVar1 & inputFlags) - (invertedFlags & uVar1), bestScore < uVar3 &&
              (g_bestMatchIndex = row - 1, bestScore = uVar3, uVar1 == inputFlags)))))) ||
            // Entry 3: tablePtr[27]
            (((((uVar1 = tablePtr[27], (mask & uVar1) == 0 &&
               ((uVar3 = (uVar1 ^ inputFlags) & 0x78c, uVar3 == 0 ||
                (((uVar3 == 8 && ((inputFlags & 8) != 0)) || ((uVar1 & 0xfffff8ff) == 0)))))) &&
              ((uVar3 = (uVar1 & inputFlags) - (invertedFlags & uVar1), bestScore < uVar3 &&
               (g_bestMatchIndex = row, bestScore = uVar3, uVar1 == inputFlags)))) ||
             // Entry 4: tablePtr[54]
             ((uVar1 = tablePtr[54], (mask & uVar1) == 0 &&
              ((((uVar3 = (uVar1 ^ inputFlags) & 0x78c, uVar3 == 0 ||
                 ((uVar3 == 8 && ((inputFlags & 8) != 0)))) || ((uVar1 & 0xfffff8ff) == 0)) &&
               ((uVar3 = (uVar1 & inputFlags) - (invertedFlags & uVar1), bestScore < uVar3 &&
                (g_bestMatchIndex = row + 1, bestScore = uVar3, uVar1 == inputFlags)))))))) ||
            // Entry 5: tablePtr[81]
            (((uVar1 = tablePtr[81], (mask & uVar1) == 0 &&
              ((uVar3 = (uVar1 ^ inputFlags) & 0x78c, uVar3 == 0 ||
               (((uVar3 == 8 && ((inputFlags & 8) != 0)) || ((uVar1 & 0xfffff8ff) == 0)))))) &&
             ((uVar3 = (uVar1 & inputFlags) - (invertedFlags & uVar1), bestScore < uVar3 &&
              (g_bestMatchIndex = row + 2, bestScore = uVar3, uVar1 == inputFlags)))))))) break;
        tablePtr += 135; // 0x87, advance to next row (5 entries * 27)
        uVar1 = row + 3;
        row += 5;
    } while (uVar1 < 0x37); // 55 entries total (11 rows * 5)

    g_lastInputFlags = inputFlags; // DAT_01205538
    // Store the matched value from the table at the best index
    g_lastMatchedFlags = (&g_inputMappingTable[0])[g_bestMatchIndex * 27]; // DAT_0120553c
    return g_bestMatchIndex;
}