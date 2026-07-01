// FUNC_NAME: UnknownClass::resetInternalState
int __thiscall UnknownClass::resetInternalState(int this) {
    resetComponent();  // 6x call to clear component state
    resetComponent();
    resetComponent();
    resetComponent();
    resetComponent();
    resetComponent();
    return this;
}