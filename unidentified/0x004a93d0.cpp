// FUN_004a93d0: GameObject::applyInitialFlags
void GameObject::applyInitialFlags(int param_2) {
    int obj = param_2;
    applyFlag(0x80, param_2);          // Set bit 0x80 in some field at param_2
    applyFlag(0x20, &param_2);         // Apply bit 0x20 to param_2 itself (modifies pointer?)
    *(int *)(obj + 0x10) = param_2;    // Store modified value at offset 0x10 (flags field)
    return;
}