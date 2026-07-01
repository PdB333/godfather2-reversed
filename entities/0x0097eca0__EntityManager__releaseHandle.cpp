// FUNC_NAME: EntityManager::releaseHandle
void EntityManager::releaseHandle(int handle) {
    if (handle != 0) {
        FUN_009823b0(); // Global pre-release cleanup (e.g., decrement manager ref count)
        FUN_009c8eb0(handle); // Internal release routine for the handle/pointer
    }
}