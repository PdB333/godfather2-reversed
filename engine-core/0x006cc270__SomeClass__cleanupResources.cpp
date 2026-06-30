// FUNC_NAME: SomeClass::cleanupResources
void __thiscall SomeClass::cleanupResources(void)
{
    // Free and null the second pointer (offset +0x8)
    if (this->field8 != 0) {
        releasePointerField(&this->field8); // FUN_004daf90
    }
    // Free and null the first pointer (offset +0x0)
    if (this->field0 != 0) {
        releasePointerField(&this->field0); // FUN_004daf90
    }
}