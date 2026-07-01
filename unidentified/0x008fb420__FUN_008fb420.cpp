// FUNC_NAME: UnknownClass::getComponentHandle
// Address: 0x008fb420
// Returns a handle from a component/state object referenced at this+0x43c.
// The handle is stored at component+0x68. If the component is null or equals 0x48 (invalid state marker), returns 0.
// The redundant inner check suggests original likely had two separate branches.
int __fastcall UnknownClass::getComponentHandle(void* this) {
    // +0x43c: pointer to a component/state object (e.g., action state, behavior tree)
    int* componentPtr = *(int**)((unsigned char*)this + 0x43c);
    if (componentPtr != nullptr && componentPtr != (int*)0x48) {
        // Note: componentPtr is guaranteed non-zero here, so the next branch is tautological.
        if (componentPtr != nullptr) {
            // +0x68: handle (e.g., action ID, state ID, resource handle)
            return *(int*)((unsigned char*)componentPtr + 0x68);
        }
        // Fallback: global invalid handle (previously at 0xb0)
        extern int g_invalidHandle;
        return g_invalidHandle;
    }
    return 0;
}