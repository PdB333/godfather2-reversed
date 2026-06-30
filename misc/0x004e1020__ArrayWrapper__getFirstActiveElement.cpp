// FUNC_NAME: ArrayWrapper::getFirstActiveElement
void __thiscall ArrayWrapper::getFirstActiveElement(void)
{
    // +0x00: m_pArray – pointer to a { int* data; int count; } structure
    ArrayHeader* array = *(ArrayHeader**)this;
    // +0x04: m_currentIndex
    this[1] = 0;
    // +0x08: m_currentValue
    this[2] = 0;
    
    if (array == nullptr) {
        return;
    }
    
    do {
        uint index = this[1]; // currentIndex
        if (index >= (uint)array->count) {
            return;
        }
        int value = array->data[index];
        this[2] = value; // store the found value
        this[1] = index + 1; // advance index for potential next call
    } while (value == 0); // skip zeros, stop at first non-zero
}