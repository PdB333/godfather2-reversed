// FUNC_NAME: GameObjectManager::clearAll
void __thiscall GameObjectManager::clearAll() {
    uint32_t count = *(uint32_t*)(this + 0x14);          // +0x14: number of items
    if (count != 0) {
        uint32_t i = 0;
        do {
            void* item = *(void**)(*(int*)(this + 0x10) + i * 4); // +0x10: pointer to array of item pointers
            FUN_004514c0(item, 0, 0, 0, 0);                       // reset/clear each item
            i++;
        } while (i < count);
    }
}