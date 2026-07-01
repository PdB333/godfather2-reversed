// FUNC_NAME: ConfigManager::getCategoryValue

int __thiscall ConfigManager::getCategoryValue(uint this, uint param_1) // this likely points to some config manager, param_1 is user passed? Actually param_1 passed to internal calls, so maybe it's a second argument to this function? The signature: undefined FUN_008e9ae0(void) but decompiled shows one param. It might be a member function taking one argument besides this. We assume this is a member function with one extra argument.
{
    int result = -1;
    
    // First category attempt
    this->setCategory(0x369ac561); // Hash for "categoryA"
    this->selectIndex(1); // index 1
    if (!this->isValid()) {
        int* data = this->getData();
        result = *(data + 2); // offset +0x8 (size of int = 4)
    }
    
    // Second category attempt
    this->setCategory(0xa5975eb2); // Hash for "categoryB"
    this->selectIndex(0); // index 0
    if (!this->isValid()) {
        int* data = this->getData();
        result = *(data + 2); // offset +0x8
    }
    
    int retVal = 1;
    if (result != -1) {
        retVal = result;
    }
    return retVal;
}