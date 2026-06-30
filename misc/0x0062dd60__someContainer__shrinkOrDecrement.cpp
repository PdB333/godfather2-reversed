// FUNC_NAME: someContainer::shrinkOrDecrement
uint FUN_0062dd60(ContainerClass* this) {
    // Call base or helper
    someBaseMethod();
    int iVar1 = someCheckMethod(this);
    if (iVar1 == 0) {
        // Decrement count or adjust pointer at +0x08
        this->field_08 = this->field_08 - 8;
    }
    return 1;
}