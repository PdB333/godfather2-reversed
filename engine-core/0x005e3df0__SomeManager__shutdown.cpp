// FUNC_NAME: SomeManager::shutdown
void SomeManager::shutdown(void* param_1)
{
    if (DAT_01223510 != (int *)0x0) {
        // Call virtual function at vtable offset 0xcc (shutdown/cleanup)
        (**(code **)(*DAT_01223510 + 0xcc))(param_1);
    }
    return;
}