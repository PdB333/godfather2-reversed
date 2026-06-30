// FUNC_NAME: StreamManager::FindMatchingObject

int __fastcall StreamManager::FindMatchingObject(short* pKey)
{
    int count = *(int*)((char*)this + 0x24); // +0x24: number of elements in the array
    if (count > 0)
    {
        int** ppItems = *(int***)((char*)this + 0x2c); // +0x2c: pointer to array of element pointers
        for (int i = 0; i < count; i++)
        {
            int* pItem = ppItems[i];
            // Compare key fields against element fields
            if (pKey[0] == *(short*)((char*)pItem + 0x100) &&   // +0x100: first short field
                pKey[1] == *(short*)((char*)pItem + 0x102) &&   // +0x102: second short field
                *(int*)(pKey + 2) == *(int*)((char*)pItem + 0x104) && // +0x104: first int field
                *(int*)(pKey + 4) == *(int*)((char*)pItem + 0x108) && // +0x108: second int field
                *(int*)(pKey + 6) == *(int*)((char*)pItem + 0x10c) && // +0x10c: third int field
                *(int*)(pKey + 8) == *(int*)((char*)pItem + 0x110) )  // +0x110: fourth int field
            {
                return (int)pItem; // Return pointer to matching element
            }
        }
    }
    return 0; // Not found
}