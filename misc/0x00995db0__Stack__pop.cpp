// FUNC_NAME: Stack::pop
// Stack of fixed-size elements (0xC0 bytes each)
// Structure at this: [0x00] int* m_pArray; [0x04] int m_nCount;
void __thiscall Stack::pop(void)
{
    // Process the element at index (m_nCount - 1)
    processElement(m_pArray + (m_nCount - 1) * 0xC0);
    // Decrement the count (pop off top element)
    m_nCount = m_nCount - 1;
}