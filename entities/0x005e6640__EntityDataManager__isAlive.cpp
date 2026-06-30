// FUNC_NAME: EntityDataManager::isAlive
bool isAlive(void* entity) {
    // Global singleton pointer to EntityDataManager (vtable +0x38 is isAlive virtual function)
    char result = (*(bool (__thiscall**)(void*))(*g_pEntityDataManager + 0x38))(entity);
    return result != '\0';
}