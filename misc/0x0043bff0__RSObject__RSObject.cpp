// FUNC_NAME: RSObject::RSObject
// Brief: Constructor for RSObject. Calls base initialization then optionally self-destructs if flag bit 0 is set.
// WARNING: Self-deallocation upon construction is unusual; may indicate a temporary object or a bug.
// The callee at 0x0043c050 is a global base initializer.
// The callee at 0x009c8eb0 is likely an operator delete or custom deallocator.

void BaseInit();  // global init function, addr 0x0043c050
void Deallocate(void* ptr);  // memory deallocation function, addr 0x009c8eb0

RSObject* __thiscall RSObject::RSObject(uint8_t flags) {
    BaseInit();  // perform base initialization
    if (flags & 0x01) {
        Deallocate(this);  // deallocate the object immediately
    }
    return this;  // return pointer to (potentially freed) object
}