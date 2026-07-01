// FUNC_NAME: Presentation::updateColorEffects
void __fastcall Presentation::updateColorEffects(int this) {
    int *pEffectList = (int *)(this + 0xb0); // +0xB0: linked list head of color effects
    int *pGameData = *(int **)(this + 0x58); // +0x58: pointer to large game data structure

    // Check if effect list is empty or has a sentinel value (0x48 = 72)
    if (*pEffectList == 0 || *pEffectList == 0x48) {
        // Read default color from game data at offset 0x2C34 (16 bytes)
        int colorR = *(int *)(pGameData + 0x2C34 / 4);
        int colorG = *(int *)(pGameData + 0x2C38 / 4);
        int colorB = *(int *)(pGameData + 0x2C3C / 4);
        int colorA = *(int *)(pGameData + 0x2C40 / 4);

        // Check if alternative color at offset 0x215C is not a magic constant and not zero
        int altR = *(int *)(pGameData + 0x215C / 4);
        int altG = *(int *)(pGameData + 0x2160 / 4);
        int altB = *(int *)(pGameData + 0x2164 / 4);
        int altA = *(int *)(pGameData + 0x2168 / 4);

        // Magic constants (RGBA?): 0xBABDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
        if ((altR != 0xBABDBDBA || altG != 0xBEEFBEEF || altB != 0xEAC15A55 || altA != 0x91100911) &&
            (altR != 0 || altG != 0 || altB != 0 || altA != 0)) {
            // Use alternative color
            colorR = altR;
            colorG = altG;
            colorB = altB;
            colorA = altA;
        }

        // Hash the color to get an index (adds 0x48 if non-zero)
        int newIndex = hashColor(&colorR, &colorA); // FUN_00448100
        if (newIndex != 0) {
            newIndex += 0x48;
        }

        // Update the effect list head if changed
        if (*pEffectList != newIndex) {
            if (*pEffectList != 0) {
                freeEffect(pEffectList); // FUN_004daf90
            }
            *pEffectList = newIndex;
            if (newIndex != 0) {
                *(int *)(this + 0xB4) = *(int *)(newIndex + 4); // +0xB4: next pointer?
                *(int **)(newIndex + 4) = pEffectList; // Link back
            }
        }

        // Iterate over effects from game data at offset 0x2494
        int effectIterator = *(int *)((char *)pGameData + 0x2494); // +0x2494: iterator handle
        char flag = 0;
        int prevCount = 0;
        int currentCount = 0;
        int *pEffect = 0;

        do {
            int iteratorState = getIteratorState(effectIterator); // FUN_00424c90
            if (iteratorState == 4) {
                return;
            }

            if (flag == 0) {
                currentCount = getNextEffect(effectIterator, &pEffect, 0); // FUN_00425030
                flag = 1;
                prevCount = currentCount;
            } else {
                currentCount = getNextEffect(effectIterator, &pEffect, &currentCount);
                if (prevCount == currentCount) {
                    return;
                }
            }
        } while (pEffect == 0 ||
                 (*(int (**)(void))(*pEffect + 0x10))() != (void *)0x00e078fa); // vtable check

        // Apply effect to the list head or a fixed address
        if (*pEffectList != 0) {
            applyEffect(*pEffectList + 0x20); // FUN_006d75e0
        } else {
            applyEffect(0x68); // FUN_006d75e0
        }
    }
}