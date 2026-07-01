// FUNC_NAME: CallbackOwner::initializeWithCallback
void __fastcall CallbackOwner::initializeWithCallback(CallbackOwner* this) {
    // Initialize sub-object at offset 0x10 (likely a base class or inner data)
    FUN_0070b6a0(&this->baseObject); // +0x10

    // Call the stored function pointer at offset 0x8 (e.g., a virtual dispatcher or callback)
    // This is a direct function pointer call, not through vtable
    this->callbackFunc(); // +0x8
}