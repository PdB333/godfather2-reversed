// FUNC_NAME: CIndexedList::getEntryAtIndex
uint32_t __thiscall CIndexedList::getEntryAtIndex(int thisPtr, int index) {
    // +0x30: base of an array of 4-byte entries (pointers/values)
    return *(uint32_t*)(thisPtr + 0x30 + index * 4);
}