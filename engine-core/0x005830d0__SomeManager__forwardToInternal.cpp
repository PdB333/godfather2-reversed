// FUNC_NAME: SomeManager::forwardToInternal
void SomeManager::forwardToInternal(undefined4 param) {
    // Dereference pointer at this+0x4 to get internal object
    // and call its method with param
    FUN_005781f0(*(undefined4*)((int)this + 4), param);
}