// FUNC_NAME: AptStack::pop
// Function address: 0x005a6ff0
// EA Apt internal: pops the top element from a stack container with debug assertion for non-empty.
// Defined in apt\_AptStack.h (line 0x23 = 35)

void AptStack::pop() {
    // unaff_EDI is this->m_size (pointer to integer count)
    // If stack is not empty, destroy top element and decrement count
    if (m_size > 0) {
        // Call destructor via vtable of the element at index m_size
        // element is a pointer; first field is vtable pointer
        uint elementVtable = *(uint*)m_data[m_size];
        // vtable entry at offset (elementVtable & 0x7fff) * 4
        void (*destructor)(void*) = (void (*)(void*))(&DAT_0103aee0 + (elementVtable & 0x7fff) * 4);
        destructor((void*)m_data[m_size]);
        m_size--;
    } else {
        // Debug assertion: stack underflow
        const char* expr = "size() > 0";
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptStack.h";
        int line = 0x23; // 35
        int assertType = 2; // Assert type (e.g., FATAL)
        // Global assert enable flag (initialized to non-zero in debug builds)
        if (DAT_01128fa4 != 0) {
            int* tlsRecord = *(int**)(*(int**)(__readfsdword(0x2C)) + 0x30);
            uint flags = 1; // default?
            if (tlsRecord) {
                flags = (*(code**)(tlsRecord[0] + 8))(&expr, "size() > 0"); // assertion handler call
            }
            if ((flags & 2) != 0) {
                DAT_01128fa4 = 0; // disable further assertions
            }
            // Trigger debug break (int3) if needed
            if ( (tlsRecord || assertType == 4) && 
                 ((flags & 1) || (assertType == 0 || assertType == 1)) ) {
                __debugbreak();
            }
        }
    }
}