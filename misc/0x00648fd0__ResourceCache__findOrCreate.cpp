// FUNC_NAME: ResourceCache::findOrCreate
// Role: Thread-safe lookup of a resource by key. If found, increments reference count and returns pointer to data. Otherwise returns default value.

class ResourceCache {
public:
    // +0x1b8: pointer to CRITICAL_SECTION (or custom lock)
    // +0x17c: default return value
    // +0x... other members

    // __thiscall
    void* findOrCreate(void* key) {
        CRITICAL_SECTION* lock = *(CRITICAL_SECTION**)(this + 0x1b8);
        if (lock != nullptr) {
            EnterCriticalSection(lock);
            // Note: The original code manipulates lock[1].DebugInfo - likely a misdecompilation of a ref count increment
            // It's actually incrementing some member of the lock-like structure
            reinterpret_cast<unsigned int*>(lock + 1)++;
        }

        int result = this->internalFind(key); // At 0x00649040
        if (result != 0) {
            // At 0x006492f0 - likely ref count increment on result
            refCountIncrement(result); 
            void* value = *(void**)(result + 8);
            if (lock != nullptr) {
                // Mirror of the increment above - decrement lock ref count
                reinterpret_cast<unsigned int*>(lock + 1)--;
                LeaveCriticalSection(lock);
            }
            return value;
        }

        if (lock != nullptr) {
            reinterpret_cast<unsigned int*>(lock + 1)--;
            LeaveCriticalSection(lock);
        }
        return *(void**)(this + 0x17c);
    }

private:
    void* internalFind(void* key); // 0x00649040
    void refCountIncrement(void* obj); // 0x006492f0
};