// FUNC_NAME: SomeClass::releaseResources
void __thiscall SomeClass::releaseResources(void) {
    // Offset +0x8: pointer to first resource
    // Offset +0x14: pointer to second resource
    if (*(void**)((uint32_t)this + 0x14) != 0) {
        FUN_009c8f10(*(void**)((uint32_t)this + 0x14));
    }
    if (*(void**)((uint32_t)this + 8) != 0) {
        FUN_009c8f10(*(void**)((uint32_t)this + 8));
    }
}