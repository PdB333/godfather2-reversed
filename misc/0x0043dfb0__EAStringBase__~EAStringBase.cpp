// FUNC_NAME: EAStringBase::~EAStringBase
void __thiscall EAStringBase::destructor(EAStringBase *this) {
    // Set vtable to this class's vtable (allows virtual calls during destruction)
    this->vtable = (VTableHeader*)&PTR_FUN_00da9810;
    // Free heap-allocated buffer if capacity exceeds small string threshold (15)
    if (this->capacity > 15) {
        FUN_009c8eb0(this->buffer); // likely operator delete(void*)
    }
    // Reset to small string optimization (16-byte inline buffer, capacity 15)
    this->capacity = 15;
    this->size = 0;
    this->buffer[0] = '\0'; // null-terminate
    // Set vtable to base class vtable for further destruction in derived destructors
    this->vtable = (VTableHeader*)&PTR_LAB_00e31044;
}