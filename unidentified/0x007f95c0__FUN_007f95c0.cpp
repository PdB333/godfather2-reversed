// FUNC_NAME: BaseClass::invokeVirtualAt264
// Function at 0x007f95c0: Calls virtual method at vtable offset 0x264 (index 0x99)
void __thiscall BaseClass::invokeVirtualAt264() {
    // Read vtable pointer from this (first member), then offset and call
    // This is a forward to another virtual function.
    (*(void (__thiscall**)(BaseClass*))(*reinterpret_cast<uintptr_t*>(this) + 0x264))(this);
}