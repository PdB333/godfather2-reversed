// FUNC_NAME: SomeClass::findIndexByQuadKey
uint __thiscall SomeClass::findIndexByQuadKey(int *quadKey)
{
    uint index = 0;
    if (m_nCount != 0) {
        int **ptr = m_pArray;
        do {
            int *obj = *ptr; // each element is pointer to an object with quad key at +0x50
            if ((obj[0x50/4] == quadKey[0]) &&   // offset 0x50
                (obj[0x54/4] == quadKey[1]) &&   // offset 0x54
                (obj[0x58/4] == quadKey[2]) &&   // offset 0x58
                (obj[0x5C/4] == quadKey[3])) {   // offset 0x5C
                return index;
            }
            index++;
            ptr++;
        } while (index < m_nCount);
    }
    return 0xFFFFFFFF; // not found
}