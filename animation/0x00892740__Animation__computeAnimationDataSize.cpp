// FUNC_NAME: Animation::computeAnimationDataSize
int __thiscall Animation::computeAnimationDataSize(int this)
{
    // Offsets +0x40, +0x70, +0xA0, +0xD0 are counts of elements (e.g., bone indices) for four limbs or groups
    int totalCount = *(int*)(this + 0x40)
                  + *(int*)(this + 0x70)
                  + *(int*)(this + 0xA0)
                  + *(int*)(this + 0xD0);

    // Multiply by 4 (size of each element in bytes) and add base header offset 0x60
    return totalCount * 4 + 0x60;
}