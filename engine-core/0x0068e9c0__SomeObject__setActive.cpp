// FUNC_NAME: SomeObject::setActive
void __thiscall SomeObject::setActive(void* this, int param) {
    FUN_004d3d90(param);
    *(uint8_t*)((uintptr_t)this + 0x10) = 1; // set active flag
}