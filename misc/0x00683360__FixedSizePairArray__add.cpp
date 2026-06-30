// FUNC_NAME: FixedSizePairArray::add
void __thiscall FixedSizePairArray::add(int value1, int value2)
{
    uint index = *(uint *)(this + 0x88);   // m_count, number of pairs currently stored
    if (index < 0x10)                      // maximum capacity of 16 pairs
    {
        *(int *)(this + 8 + index * 8) = value1;      // m_array[index].first at +0x00
        *(int *)(this + 0xc + index * 8) = value2;    // m_array[index].second at +0x04
        *(int *)(this + 0x88) = index + 1;            // increment count
    }
}