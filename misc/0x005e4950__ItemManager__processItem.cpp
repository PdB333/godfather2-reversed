// FUNC_NAME: ItemManager::processItem
int __thiscall ItemManager::processItem(int thisPtr) {
    int successFlag = 0;
    int itemHandle = this->getItem(reinterpret_cast<void*>(DAT_01223514), &successFlag);
    if ((itemHandle != 0) && (successFlag != 0)) {
        return this->applyItemEffect(thisPtr, itemHandle);
    }
    return 0;
}