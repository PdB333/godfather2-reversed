// FUNC_NAME: findAdjacentIndex
uint __thiscall findAdjacentIndex(int this, int key)
{
    int count = *(int *)(this + 0xC);
    if (count == 0) {
        return 0xFFFFFFFF;
    }
    if (count == 1) {
        return 0;
    }

    uint currentIdx = *(uint *)(this + 0x4);  // +0x4: current index
    int nextIdx;
    if (currentIdx < count - 1U) {
        nextIdx = currentIdx + 1;
    } else {
        nextIdx = 0;
    }

    // Check if current-next pair matches the key
    if (adjacentComparison(key,
                           *(int *)(*(int *)(this + 0x8) + currentIdx * 4) + 4,
                           *(int *)(*(int *)(this + 0x8) + nextIdx * 4) + 4)) {
        return currentIdx;
    }

    // Linear search through all pairs (with wrap-around)
    uint i = 0;
    uint countVal = *(uint *)(this + 0xC);
    while (i < countVal) {
        int next;
        if (i < countVal - 1) {
            next = i + 1;
        } else {
            next = 0;
        }
        if (adjacentComparison(key,
                               *(int *)(*(int *)(this + 0x8) + i * 4) + 4,
                               *(int *)(*(int *)(this + 0x8) + next * 4) + 4)) {
            return i;
        }
        countVal = *(uint *)(this + 0xC);
        i++;
    }

    return 0xFFFFFFFF;
}