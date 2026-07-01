// FUNC_NAME: CSACrewComponent::CSACrewComponent
int __thiscall CSACrewComponent::CSACrewComponent(int thisPtr, byte allocFlag) {
    // Set vtable pointer at this+0x18 (likely a second vtable or RTTI pointer for multiple inheritance)
    *(void***)(thisPtr + 0x18) = &PTR_LAB_00e355fc;

    // Call base class constructor (e.g., SimObject or Component base)
    FUN_0064d150();

    // If allocFlag has bit 0 set, this is constructed on the heap — call the free function (e.g., operator delete)
    // This pattern occurs in custom allocators where a flag indicates whether the memory was dynamically allocated.
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(thisPtr);
    }

    return thisPtr;
}