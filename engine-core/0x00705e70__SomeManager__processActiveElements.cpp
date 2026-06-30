// FUNC_NAME: SomeManager::processActiveElements
void __fastcall SomeManager::processActiveElements(void* thisPtr)
{
    uint count;            // uVar1
    uint index;            // uVar3
    bool conditionResult;  // iVar2

    // Assuming thisPtr is a pointer to SomeManager structure.
    // Offset 0x10: pointer to an array/metadata structure.
    // That structure at offset 0x04 holds the count of elements.
    uint* pMeta = *(uint**)((char*)thisPtr + 0x10);
    count = *(pMeta + 1);   // +4 from pMeta

    index = 0;
    if (count != 0) {
        do {
            conditionResult = checkCondition(index);   // FUN_00704110
            if (conditionResult) {
                performAction();                       // FUN_00481530
            }
            index++;
        } while (index < count);
    }
}