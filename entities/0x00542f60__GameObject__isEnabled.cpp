// FUNC_NAME: GameObject::isEnabled
// Function at 0x00542f60: Virtual boolean getter via vtable offset 0x1fc
bool GameObject::isEnabled() {
    // Call virtual function at vtable+0x1fc (index 127) and return non-zero result
    int result = (**(int (**)())(*(int*)this + 0x1fc))();
    return result != 0;
}