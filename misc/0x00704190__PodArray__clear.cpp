// FUNC_NAME: PodArray::clear
void __thiscall PodArray::clear(void)
{
    int count = this->m_count;  // +0x04
    PodElement* base = this->m_data;  // +0x00

    // Destroy elements in reverse order (from count-1 down to 0)
    while (count > 0) {
        count--;
        if (base[count].m_handle != 0) {  // first 4 bytes of an 8-byte element
            destroyElement(&base[count]);  // FUN_004daf90
        }
    }

    // Free the element array memory
    if (this->m_data != 0) {
        freeMemory(this->m_data);  // FUN_009c8f10
    }
}