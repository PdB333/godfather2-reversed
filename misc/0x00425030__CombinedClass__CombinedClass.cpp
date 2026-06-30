// FUNC_NAME: CombinedClass::CombinedClass

void CombinedClass::CombinedClass(BaseClass* thisBase, AnotherClass* thatBase) {
    // Call base class constructor at 0x00424c90
    BaseClass::BaseClass(thisBase);
    // Call second base class or member initializer at 0x004a2030
    AnotherClass::init(thatBase);
}