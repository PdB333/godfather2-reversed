// FUNC_NAME: RefCounted::incrementRefCount
void RefCounted::incrementRefCount() {
    // +0x1c: reference count field
    int& refCount = *(int*)((char*)this + 0x1c);
    if (refCount == 0x3fffffff) {
        // Sentinel value indicates overflow or "too long" – throw an exception
        // Debug assertion message
        FUN_0043f9f0("list<T> too long", 0x10);
        // Setup exception throw (standard MSVC pattern)
        // ... (exception handling code omitted for clarity)
        std::_Throw((exception*)&local_24);
    }
    refCount++;
}