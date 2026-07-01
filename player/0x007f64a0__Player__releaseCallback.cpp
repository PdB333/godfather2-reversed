// FUNC_NAME: Player::releaseCallback
// Address: 0x007f64a0
// Releases a function pointer stored at this+0x7a4 by calling it with argument 1 and nullifying it.
void __fastcall Player::releaseCallback() {
    // +0x7a4: mCallback (void (*)(int))
    if (mCallback != nullptr) {
        mCallback(1);
        mCallback = nullptr;
    }
}