// FUNC_NAME: AptDisplayList::setDisplayListItem
void __thiscall AptDisplayList::setDisplayListItem(uint key) {
    uint* pOldItem = nullptr;
    getDisplayListItem(key, this, 0, (undefined (*) [4])0, &pOldItem);
    if (pOldItem != nullptr && ((*pOldItem >> 15) & 1) != 0) {
        // Assert: pOldItem should be null or undefined
        debugAssert("pOldItem == 0 || pOldItem->isUndefined()",
                    "..\\source\\Apt\\AptDisplayList.cpp", 0x54);
    }
    int* displayList = getActiveDisplayList();
    if (displayList != nullptr) {
        displayList[0x30 / 4] = (int)this; // +0x30: pointer to parent list
    }
}