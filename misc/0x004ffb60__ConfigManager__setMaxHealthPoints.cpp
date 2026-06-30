// FUNC_NAME: ConfigManager::setMaxHealthPoints
void __thiscall ConfigManager::setMaxHealthPoints(void* this_ptr, int playerIndex)
{
    int value = 0x50; // 80 health points
    FUN_004eba90(this_ptr, playerIndex, &value, 1); // generic setter: (object, index, valuePtr, size)
    return;
}