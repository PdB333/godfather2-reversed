// FUNC_NAME: StreamObject::release
int __thiscall StreamObject::release(void) {
    int result = 0;
    if (*(char *)(this + 0x490) != '\0') {
        FUN_005e8300(this); // stop or cancel the stream
        *(char *)(this + 0x490) = 0; // clear active flag
        if (*(int *)(this + 0x494) != 0) {
            // call cleanup callback stored at +0x4a0
            (**(code **)(this + 0x4a0))(*(int *)(this + 0x494));
        }
        *(int *)(this + 0x494) = 0; // clear callback context
        *(int *)(this + 0x49c) = 0; // clear other pointer
        *(int *)(this + 0x498) = 0; // clear another pointer
        result = 1;
    }
    return result;
}