// FUNC_NAME: SimManager::isValidHandle
bool SimManager::isValidHandle(int32_t handle) {
    int32_t index = this->findObjectByHandle(handle);
    return index != -1;
}