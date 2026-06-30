// FUNC_NAME: Entity::shutdown
void __thiscall Entity::shutdown(void)
{
    // +0x9a: byte flag indicating if shutdown has been performed
    // +0x60: pointer to a child object (or some resource)
    if (*(char *)(this + 0x9a) == '\0' && *(int *)(this + 0x60) != 0) {
        // Call cleanup function on the child with a 0 argument (likely a reset or release)
        FUN_00408a00(*(int *)(this + 0x60), 0);
    }
    *(char *)(this + 0x9a) = 1;
}