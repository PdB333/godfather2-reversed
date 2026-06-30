// FUNC_NAME: isObjectAlive
// Function address: 0x004b1940
// Role: Checks whether an object (passed as first argument) is alive/active by calling a virtual method at vtable offset 0x34 (index 13) on the object.
// The vtable is obtained from a global pointer stored at DAT_01223510, which likely points to a vtable for a specific class.

bool isObjectAlive(void* object) {
    // Global pointer to the vtable for this object's class
    void** vtable = *(void***)DAT_01223510;  // DAT_01223510 is a pointer to the vtable pointer
    // Virtual function at offset 0x34 (size of 4 bytes per entry -> index 13)
    typedef bool (__thiscall *VirtualIsAliveFunc)(void*);
    VirtualIsAliveFunc isAlive = (VirtualIsAliveFunc)vtable[0x34 / 4];
    // Call the virtual method and return whether it returned non-zero
    return isAlive(object) != 0;
}