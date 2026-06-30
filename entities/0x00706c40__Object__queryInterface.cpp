// FUNC_NAME: Object::queryInterface
bool __thiscall Object::queryInterface(uint interfaceId, void** outInterface) {
    if (interfaceId == 0x4ecfbe13) {
        *outInterface = this;
        return true;
    }
    *outInterface = nullptr;
    if (interfaceId == 0x38523fc3) {
        *outInterface = this;
    }
    return *outInterface != nullptr;
}