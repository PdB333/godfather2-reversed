// FUNC_NAME: PairTriggerTable::checkAndFire
void PairTriggerTable::checkAndFire(int firstKey, int secondKey)
{
    uint i = 0;
    if (g_pairCount != 0) {
        int* current = &g_pairTableBase; // starts at DAT_0122232c
        do {
            // Each entry occupies 3 ints; key1 is at current[-1], key2 at current[0]
            if ((current[-1] == firstKey) && (current[0] == secondKey)) {
                triggerCallback(); // calls FUN_00609ca0
                return;
            }
            i++;
            current += 3;
        } while (i < g_pairCount);
    }
}