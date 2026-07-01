// FUNC_NAME: Entity::deactivate
// Function address: 0x008458b0
// Role: Deactivates the entity, calling a cleanup routine if currently active.
void __thiscall Entity::deactivate(void)
{
    // Check if the active flag at offset +0x34 is set.
    if (*(char *)(this + 0x34) != '\0') {
        // Call cleanup/shutdown function (likely this->stop() or similar)
        FUN_0041e7d0(0);
    }
    // Clear the active flag.
    *(char *)(this + 0x34) = 0;
}