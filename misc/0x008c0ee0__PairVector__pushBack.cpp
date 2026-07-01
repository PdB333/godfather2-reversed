// FUNC_NAME: PairVector::pushBack
void __thiscall PairVector::pushBack(int first, int second)
{
    int oldCapacity = this->m_capacity; // +0x194
    if (this->m_count == oldCapacity) // +0x190 (400)
    {
        int newCapacity = (oldCapacity == 0) ? 1 : oldCapacity * 2;
        FUN_008bddc0(newCapacity); // reallocate internal buffer
    }
    int *entry = this->m_array + this->m_count * 2; // +0x18c, each entry 8 bytes
    this->m_count++;
    if (entry != (int *)0x0)
    {
        entry[0] = first;
        entry[1] = second;
    }
}