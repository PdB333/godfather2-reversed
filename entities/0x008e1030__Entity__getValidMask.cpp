// FUNC_NAME: Entity::getValidMask
uint Entity::getValidMask(uint mask) {
    char result;
    // Virtual function at vtable+0x10: returns nonzero if mask is valid/available
    result = (this->vtable->validateMask)(mask, (int*)&result);  // actual param is address of local
    return (result != 0) ? mask : 0;
}