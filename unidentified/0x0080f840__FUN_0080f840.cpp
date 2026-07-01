// FUNC_NAME: UnknownClass::copyFieldTo // 0x0080f840 - Copies a field value from this object to another
void __thiscall UnknownClass::copyFieldTo(UnknownClass* dest) {
    // Retrieve the field from this object via an internal getter
    int fieldValue = this->getField(); // FUN_00445f00
    // Set the field on the destination object via an internal setter
    dest->setField(fieldValue); // FUN_00446600
}