// FUNC_NAME: SomeClass::forwardToBase
void __thiscall SomeClass::forwardToBase(void* this) {
    BaseClass::baseClassMethod(this);
}