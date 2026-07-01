// FUNC_NAME: Object::getContainer
int __thiscall getContainer() {
    // +0xC8: pointer to embedded sub-object (located at this + 0x48)
    if (*(int*)(this + 0xC8) != 0) {
        return *(int*)(this + 0xC8) - 0x48;
    }
    return 0;
}