// FUNC_NAME: SimManager::processNextEntity
undefined4 __thiscall SimManager::processNextEntity(uint this, undefined4 outIndex, undefined4 *skipData)
{
    undefined2 *dataPtr;
    uint iterator;

    iterator = this;
    advanceIterator(&iterator, &outIndex); // FUN_0098b550: advance iterator, output index
    if (iterator != this + 0x218) {
        if (skipData != (undefined4 *)(iterator + 0x14)) { // +0x14: data pointer field in iterator
            dataPtr = *(undefined2 **)(iterator + 0x14);
            if (dataPtr == (undefined2 *)0x0) {
                dataPtr = &GLOBAL_DEFAULT_DATA; // DAT_00e2df14
            }
            processElement(dataPtr, 0, *(undefined4 *)(iterator + 0x18)); // FUN_004dbb10: process data with param
        }
        return 1;
    }
    return 0;
}