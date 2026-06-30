// FUNC_NAME: bitmaskFromOneBasedIndex
int bitmaskFromOneBasedIndex(int index)
{
    if (index != 0) {
        return 1 << ((char)index - 1U & 0x1f);
    }
    return 0;
}