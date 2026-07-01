// FUNC_NAME: Iterator::getCurrentData
int __thiscall Iterator::getCurrentData() {
    // Check if container pointer is null
    if (m_container == 0) {
        EA_ASSERT_FAIL(); // FUN_00b97aea - likely assertion failure
    }
    // Check if current index/pointer equals container's size (offset +4)
    if (m_current == m_container->size) {
        EA_ASSERT_FAIL();
    }
    // Return pointer to data at offset 12 from current element
    return (int)(m_current + 12);
}