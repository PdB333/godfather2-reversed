// FUNC_NAME: CallbackList::executeCallbacks

class CallbackList {
public:
    // Fields offsets:
    // +0x00: void** m_callbackPtrs   (array of pointers to callback objects)
    // +0x04: int    m_count          (number of callbacks)
    void** m_callbackPtrs; // array of pointers to callback objects
    int    m_count;        // number of callbacks

    // Iterates over all callbacks in reverse order, calling each with argument 0,
    // then clears the list.
    void executeCallbacks();
};

void CallbackList::executeCallbacks() {
    int count = this->m_count;
    if (count != 0) {
        // Iterate from last to first
        for (int i = count - 1; i >= 0; --i) {
            // Retrieve the callback object pointer from the array
            void* callbackObj = this->m_callbackPtrs[i];
            // The callback object's first member (offset +0x00) is a function pointer
            // This function takes an integer argument and returns void.
            void (*callbackFunc)(int) = *(void (**)(int))callbackObj;
            // Invoke the callback with argument 0
            callbackFunc(0);
        }
        // Clear the count to indicate all callbacks have been processed
        this->m_count = 0;
    }
}