// FUN_00453830: GameObject::getTotalSize
int GameObject::getTotalSize() {
    int baseSize = getBaseSize(&(this->field_4)); // +0x4: some data
    return baseSize + 0x100; // add constant overhead of 256
}