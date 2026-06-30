// 0x004AA700 - InputController::getButtonState (reads controller button state from TLS and returns enum 1/2/3)
char __fastcall InputController::getButtonState(void* this) {
    // Access thread-local storage (TLS) pointer at FS:[0x2C], then dereference two levels
    // to reach a global input state array. The field at this+0x18 is an index/offset into that array.
    uint state = (*(uint*)(*(int*)(*(int*)__readfsdword(0x2C) + 8) + 0x7C + *(int*)((char*)this + 0x18))) & 0xC;

    // Map the masked bits (0,4,8,12) to an action code:
    // 0 = idle, 4 = held/pressed? , 8 = just pressed? , 12 = same as 4
    if (state == 0)
        return 1;          // Idle state
    if (state == 4)
        return 3;          // Held / continuous state
    if (state == 8)
        return 2;          // Just pressed (edge)
    return 3;              // Fallback (also 12 maps here)
}