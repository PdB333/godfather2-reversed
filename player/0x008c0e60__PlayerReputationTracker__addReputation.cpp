// FUNC_NAME: PlayerReputationTracker::addReputation
void __thiscall PlayerReputationTracker::addReputation(int this, int id, float delta)
{
    // +0x190: m_reputationCount (uint)
    // +0x18c: m_reputationEntries (array of int pairs: [id, value])
    uint count = *(uint *)(this + 0x190);
    if (count == 0) {
        return;
    }

    int *entries = *(int **)(this + 0x18c);
    uint index = 0;
    while (entries[index * 2] != id) {
        index++;
        if (index >= count) {
            return; // ID not found
        }
    }

    // Found entry at index, modify the value (stored as int, treated as float)
    if (delta != 0.0f) {
        float currentValue = (float)entries[index * 2 + 1];
        float newValue = currentValue + delta;
        if (newValue < 0.0f) {
            newValue = 0.0f;
        }
        entries[index * 2 + 1] = (int)newValue;

        // Notify or update after reputation change
        FUN_008be890();
    }
}