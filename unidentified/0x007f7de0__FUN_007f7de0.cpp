// FUNC_NAME: SomeObject::getDataPointer
int SomeObject::getDataPointer() {
    int result = 0;
    if (this != 0 && *(int*)(this + 8) != 0) {
        result = *(int*)(this + 8);
    }
    return result;
}