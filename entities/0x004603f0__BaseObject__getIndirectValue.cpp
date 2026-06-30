// FUNC_NAME: BaseObject::getIndirectValue
int __thiscall BaseObject::getIndirectValue() {
    // +0x220: validity flag or pointer indicating whether data at +0x21c is valid
    // +0x21c: pointer to a pointer to the actual value (double indirection)
    int result = 0;
    if (*(int*)((char*)this + 0x220) != 0) {
        result = **(int**)((char*)this + 0x21c);
    }
    return result;
}