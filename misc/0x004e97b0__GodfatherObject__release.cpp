// FUNC_NAME: GodfatherObject::release
void __thiscall GodfatherObject::release(void) {
    // this is passed in EAX (register)
    if (this) {
        // Check vtable pointer: if non-null and not a specific sentinel (0x48)
        // 0x48 likely indicates a partially constructed or already destroyed object
        if (this->vtablePtr && this->vtablePtr != reinterpret_cast<void*>(0x48)) {
            FUN_00449e90(); // Base cleanup: detach from manager, invalidate state
        }
        FUN_004e97e0(); // Derived cleanup: release resources, notify listeners
    }
}