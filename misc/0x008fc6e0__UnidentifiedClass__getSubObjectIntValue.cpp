// FUNC_NAME: UnidentifiedClass::getSubObjectIntValue
int UnidentifiedClass::getSubObjectIntValue() {
    // +0x1c: pointer to sub-object (e.g., data component)
    int* subObj = *(int**)(this + 0x1c);
    if (subObj != 0) {
        // +0x74: field within sub-object (e.g., count, flag, or ID)
        return *(int*)(subObj + 0x74);
    }
    return 0;
}