// FUNC_NAME: FixedSizeArray::initialize
void __thiscall FixedSizeArray::initialize(void)
{
    // Allocate 0x400 bytes for 128 elements of size 8
    void *pArray = operator_new(0x400); // FUN_009c8e80
    if (pArray == nullptr) {
        pArray = nullptr;
    } else {
        // Call element constructor for each slot (size=8, count=128)
        // _vector_constructor_iterator_ calls LAB_0065d990 for each element
        _vector_constructor_iterator_(pArray, 8, 0x80, (_func_void_ptr_void_ptr *)&LAB_0065d990);
    }
    // Store array pointer and metadata
    m_pArray = pArray;       // +0x00
    m_capacity = 0x80;       // +0x04
    m_count = 0;             // +0x08
    m_someIndex = 0;         // +0x0C
}