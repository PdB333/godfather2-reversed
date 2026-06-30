// FUNC_NAME: Entity::isAlive
bool Entity::isAlive(void* thisPtr)
{
    // vtable pointer from global DAT_01223510 (likely Entity class vtable)
    // Call virtual function at vtable offset 0x38 (e.g., virtual bool isAlive())
    char result = ((char (*)(void*))(*(void**)(*(int*)0x01223510 + 0x38)))(thisPtr);
    return result != '\0';
}