// FUNC_NAME: ResourceHandle::release
void __fastcall ResourceHandle::release(int* param_1)
{
    // Check if the managed pointer is non-null
    if (*param_1 != 0) {
        // Call the destructor/release function on the pointed object
        FUN_004daf90(param_1);
        // Nullify the pointer to avoid dangling references
        *param_1 = 0;
    }
}