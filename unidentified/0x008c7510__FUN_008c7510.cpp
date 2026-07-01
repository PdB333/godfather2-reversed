// FUNC_NAME: SomeClass::getComponent
void* __thiscall SomeClass::getComponent(void* thisObj) {
    void* subObj = getSubObject(thisObj);
    if (subObj != nullptr) {
        return *(void**)((uint8_t*)subObj + 0x50); // +0x50: pointer to component data
    }
    return nullptr;
}