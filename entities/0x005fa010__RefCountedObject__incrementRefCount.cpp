// FUNC_NAME: RefCountedObject::incrementRefCount
// Address: 0x005fa010
// Role: Increments reference count at offset 0x1c, throws if overflow (0x3fffffff)
void RefCountedObject::incrementRefCount()
{
    int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1c);
    if (*refCount == 0x3fffffff) {
        // Overflow: throw standard "list<T> too long" exception (MSVC pattern)
        // This path setups the exception object and calls _Throw.
        throw std::exception("list<T> too long");
    }
    ++(*refCount);
}