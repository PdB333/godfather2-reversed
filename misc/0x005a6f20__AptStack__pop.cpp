// FUNC_NAME: AptStack::pop
void AptStack::pop(void)
{
    // Assertion: stack must not be empty
    if (this->size <= 0) {
        // Assertion failed: "size() > 0"
        // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptStack.h, line 0x23
        // Trigger debug break if assertion enabled
        if (DAT_01128fa3 != '\0') {
            // Call assertion handler (likely __debugbreak or similar)
            // Inline assembly: int 3
            __asm { int 3 };
        }
        return;
    }

    // Get the top element (index = size - 1)
    uint32_t element = this->data[this->size - 1];  // +0x04 per element, offset from this

    // Call destructor based on element type (low 15 bits index into vtable)
    typedef void (*DestructorFunc)(uint32_t*);
    DestructorFunc destructor = ((DestructorFunc*)DAT_0103aee0)[element & 0x7FFF];
    destructor(&element);

    // Decrement stack size
    this->size--;
}