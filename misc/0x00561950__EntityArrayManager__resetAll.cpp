// FUNC_NAME: EntityArrayManager::resetAll

void EntityArrayManager::resetAll()
{
    int index = 0;
    if (0 < *(int *)(this + 4)) // +0x4: count of elements
    {
        char *elementPtr = (char *)(this + 0x20); // +0x20: start of array (each element 0x30 bytes)
        do
        {
            *elementPtr = 1; // mark as active/reset flag
            index++;
            elementPtr += 0x30; // stride 48 bytes per element
        } while (index < *(int *)(this + 4));
    }
    FUN_00aad120(*(undefined4 *)(this + 4)); // some per-component manager reset
    index = 0;
    if (0 < *(int *)(this + 4))
    {
        do
        {
            FUN_00aad110(); // per-element initialization
            index++;
        } while (index < *(int *)(this + 4));
    }
    return;
}