// FUNC_NAME: getEncodedFlagFromSubObject
uint __fastcall getEncodedFlagFromSubObject(void* thisPtr, uint inputMask)
{
    uint result = inputMask & 0xFFFFFF00;
    int* pSubObj = *(int**)((int)thisPtr + 0x5C); // +0x5C: pointer to sub-object or null/0x48 sentinel
    if (pSubObj != (int*)0 && pSubObj != (int*)0x48)
    {
        int subObjAddr = (int)pSubObj;
        if (subObjAddr != 0)
        {
            bool flag = (*(byte*)(subObjAddr + 0xD4) & 0x79) != 0; // 0xD4: flags byte, 0x79 = 0111 1001
            uint encodedIndex = ((uint)(subObjAddr - 0x48) >> 8) << 8; // upper 24 bits derived from pointer offset
            return encodedIndex | (flag ? 1 : 0);
        }
        // If sub-object pointer is somehow zero despite check, use a global/other flag at fixed address 0x11C
        return (uint)((*(byte*)0x11C & 0x79) != 0);
    }
    return result;
}