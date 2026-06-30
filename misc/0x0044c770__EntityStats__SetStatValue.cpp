// FUNC_NAME: EntityStats::SetStatValue
struct EntityStats
{
    // offset 0x3c: m_statArray (int array)
    int m_statArray[1]; // size unknown from this function alone
};

void __thiscall EntityStats::SetStatValue(int index, int value)
{
    this->m_statArray[index] = value;
}