// FUNC_NAME: EntityHierarchy::getNestedChildByOffsets
int EntityHierarchy::getNestedChildByOffsets(int this) {
    int index; // iterative child index
    int childPtr; // derived pointer to child entry

    // First level: read child index from offset +0x20, multiply by 4 for stride
    index = *(int *)(this + 0x20); // +0x20: first child index
    // Compute pointer to child entry: base + (childIndex * 4) + 0x40 (base offset for child array?)
    childPtr = index * 4 + 0x40 + *(int *)(index * 4 + 0x30 + this) * 4; // +0x30: some offset table / multiplier
    // Second level: use childPtr as index into another offset table (+0x10 from prior)
    childPtr = childPtr + 0x10 + *(int *)(childPtr + this) * 4;
    // Third level: final offset
    childPtr = childPtr + 0x10 + *(int *)(childPtr + this) * 4;
    return childPtr + 0x10 + *(int *)(childPtr + this) * 4;
}