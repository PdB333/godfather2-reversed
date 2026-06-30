// FUNC_NAME: BaseObject::deallocate
void __thiscall BaseObject::deallocate(void)
{
    // +0x00: vtable pointer assumed (not accessed here)
    if (this != (void *)0x0) {
        // Call cleanup function (likely virtual or static release)
        this->cleanup();  // FUN_00665b80
        // Free the memory block pointed to by 'this'
        free(this);
    }
    return;
}