// FUNC_NAME: CallbackHolder::executeCallback
void __thiscall CallbackHolder::executeCallback() {
    // +0x2c: function pointer (callback)
    // +0x30: context pointer (argument to callback)
    if (this->callbackFunc != nullptr) {
        this->callbackFunc(this->callbackContext);
    }
}