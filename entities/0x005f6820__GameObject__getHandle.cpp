// FUNC_NAME: GameObject::getHandle
bool __thiscall GameObject::getHandle(void** outHandle) const {
    // +0x38: handle/pointer member
    if (outHandle != nullptr) {
        *outHandle = (void*)this->field_0x38;
    }
    return (this->field_0x38 != 0);
}