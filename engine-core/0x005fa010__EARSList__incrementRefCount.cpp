// FUNC_NAME: EARSList::incrementRefCount
void EARSList::incrementRefCount() {
    // Check if the reference count (offset +0x1c) is at maximum allowable value
    if (m_refCount == 0x3fffffff) {
        // If at maximum, throw a "list<T> too long" exception using EA's internal mechanism
        // The original code calls FUN_0043f9f0("list<T> too long", 0x10) and constructs an exception object
        // For reconstruction, we simulate the behavior with a standard exception
        throw std::length_error("list<T> too long");
    }
    // Increment the reference count
    ++m_refCount;
}