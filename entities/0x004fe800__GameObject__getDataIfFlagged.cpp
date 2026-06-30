// FUNC_NAME: GameObject::getDataIfFlagged
int32_t GameObject::getDataIfFlagged(int32_t flag) {
    if (flag != 0) {
        // Calls internal getter at 0x004fde70 which retrieves the actual value
        return getInternalData();
    }
    return 0;
}