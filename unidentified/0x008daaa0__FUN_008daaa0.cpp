//FUNC_NAME: UnknownClass::forwardCall
void UnknownClass::forwardCall(void* arg1, void* arg2) {
    // Simple wrapper that forwards to the actual implementation at 0x0046dd00
    FUN_0046dd00(this, arg1, arg2);
}