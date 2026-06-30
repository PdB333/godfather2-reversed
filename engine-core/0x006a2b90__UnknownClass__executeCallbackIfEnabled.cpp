// FUNC_NAME: UnknownClass::executeCallbackIfEnabled
void __fastcall UnknownClass::executeCallbackIfEnabled(void *this) {
    // Checks some condition via a helper function (FUN_006a2950)
    bool isEnabled = (bool)isCallbackEnabled();  // Assumes returns a bool
    if (isEnabled) {
        // Retrieve function pointer stored at +0x98
        void (*callback)() = *(void (**)())((char *)this + 0x98);
        callback();
    }
}