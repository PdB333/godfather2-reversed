// FUNC_NAME: BaseDataManager::getElementByKey
// Address: 0x006f5dd0
// This function looks up an element in an array of 0x24-byte structures by a key (hash/ID).
// The this pointer has a data block at +0x0c, which contains (at +0x04) a pointer to the array,
// and (at +0x02) a short used as a parameter for the hash/index lookup function.
// The called function (0x006f5d80) returns an index or -1.

int __thiscall BaseDataManager::getElementByKey(void* this, unsigned int key)
{
    int* pDataBlock = *(int**)((char*)this + 0x0c);
    if (pDataBlock == nullptr) {
        return 0;
    }

    int* pArray = *(int**)((char*)pDataBlock + 0x04);   // +0x04: pointer to element array
    short countOrId = *(short*)((char*)pDataBlock + 0x02); // +0x02: count or lookup parameter

    if (pArray != nullptr && countOrId != 0) {
        int index = FUN_006f5d80(key, countOrId);   // converts key to array index (or -1)
        if (index != -1) {
            // Each element is 0x24 bytes
            return (int)pArray + index * 0x24;
        }
    }
    return 0;
}