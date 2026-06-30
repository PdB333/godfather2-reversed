// FUNC_NAME: EA::Core::ListBase::incrementSize
void EA::Core::ListBase::incrementSize() {
    // +0x1c: size (number of nodes)
    if (*(int*)((char*)this + 0x1c) == 0x3fffffff) {
        // std::list<T> too long – throw length_error
        FUN_0043f9f0("list<T> too long", 0x10);
        // ... exception construction and throw omitted for clarity
    }
    *(int*)((char*)this + 0x1c) += 1;
}