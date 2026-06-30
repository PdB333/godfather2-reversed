// FUNC_NAME: StreamManager::getInstance
// Global stream manager singleton getter. Lazily instantiates the manager via custom allocator.
int* StreamManager::getInstance()
{
    static int* instance = nullptr; // DAT_01205664
    if (instance == nullptr)
    {
        // Allocate 200 bytes (size of StreamManager object) using custom allocator.
        int* mem = (int*)StreamManager::allocateMemory(200, 0);
        if (mem != nullptr)
        {
            // Construct the object
            instance = StreamManager::constructor();
            StreamManager::onCreate();
            return instance;
        }
        instance = nullptr;
        StreamManager::onCreate();
    }
    return instance;
}