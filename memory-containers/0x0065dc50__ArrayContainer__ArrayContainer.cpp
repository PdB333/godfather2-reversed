// FUNC_NAME: ArrayContainer::ArrayContainer
void ArrayContainer::ArrayContainer(void)
{
    // Allocate 0x400 bytes = 128 elements * 8 bytes each
    void* pData = (void*)FUN_009c8e80(0x400);
    if (pData == (void*)0x0) {
        pData = (void*)0x0;
    }
    else {
        // Construct 128 objects of size 8 at the allocated memory using the constructor at LAB_0065d990
        _vector_constructor_iterator_(pData, 8, 0x80, (_func_void_ptr_void_ptr *)&LAB_0065d990);
    }
    // Set container members
    this->m_pData = pData;      // +0x00: pointer to allocated memory
    this->m_capacity = 0x80;    // +0x04: capacity = 128
    this->m_size = 0;           // +0x08: current size = 0
    this->m_unknown = 0;        // +0x0C: some flag or initial value = 0
    return;
}