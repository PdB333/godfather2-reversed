// FUNC_NAME: SmartPtr::assign
class SmartPtr {
private:
    int* m_ptr; // pointer to ref-counted object

public:
    void assign(int* newPtr) {
        // Decrement reference count on old object
        if (m_ptr != nullptr) {
            int* refCount = m_ptr + 2; // offset +8 (2 ints) for reference count
            (*refCount)--;
            if (*refCount == 0) {
                // Call destructor via vtable (third entry, offset +8)
                (*(void(*)(int*))(*(int**)m_ptr + 2))();
            }
        }
        // Assign new pointer
        m_ptr = newPtr;
        if (newPtr != nullptr) {
            // Increment reference count on new object at offset +8
            *(int*)(newPtr + 8) += 1; // reinterpret_cast<int*>(newPtr)[2]
        }
    }
};
```