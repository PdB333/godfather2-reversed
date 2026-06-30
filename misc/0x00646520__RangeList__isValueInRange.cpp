// FUNC_NAME: RangeList::isValueInRange
uint __thiscall RangeList::isValueInRange(int this, uint value) {
    // this +0x448: sentinel node (end-of-list indicator)
    // this +0x464: pointer to first node in linked list
    // this +0x468: threshold value for range comparison
    uint *node; // pointer to current node (each node: [0] start, [1] length, [7] next)

    if (*(uint *)(this + 0x468) != 0) {
        // iterate through circular linked list until sentinel
        for (node = *(uint **)(this + 0x464); node != (uint *)(this + 0x448); node = (uint *)node[7]) {
            if ((node[0] <= value) && (value < node[0] + node[1])) {
                // value falls within [start, start+length)
                return (uint)(*(uint *)(this + 0x468) < value);
            }
        }
    }

    // value not in any range; return a non-zero value derived from sentinel address
    // (likely used to indicate "not found")
    return (uint)node & 0xffffff00;
}