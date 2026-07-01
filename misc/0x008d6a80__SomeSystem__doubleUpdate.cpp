// FUNC_NAME: SomeSystem::doubleUpdate
// Address: 0x008d6a80
// Calls an internal update function twice, likely for fixed-timestep or double-buffer processing.
void SomeSystem::doubleUpdate() {
    int count = 2;
    do {
        FUN_008d5e20(this); // internal update step
        count--;
    } while (count != 0);
}