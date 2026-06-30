// FUNC_NAME: InputManager::createInstance
void InputManager::createInstance()
{
    MemoryManager* allocator = MemoryManager::getInstance(); // FUN_009c8f80
    void* memBlock = allocator->allocate(0x908); // 0x908 = size of InputManager
    InputManager* instance = nullptr;
    
    if (memBlock != nullptr)
    {
        // Call constructor on allocated memory (FUN_004b25f0)
        instance = new (memBlock) InputManager();
    }
    
    // Register the new instance in a global hash table (FUN_00423cf0)
    uint32_t hash = reinterpret_cast<uint32_t>(instance) % 
                    *(uint32_t*)(*(int32_t*)(DAT_01223398 + 8) + 8); // bucketCount from hash table header
    
    // Hash table insertion: (void* key, InputManager*& obj, uint hash)
    // The original code passes addresses of local variables for some reason; we simplify.
    gInputManagerHashTable.insert(instance, hash);
}