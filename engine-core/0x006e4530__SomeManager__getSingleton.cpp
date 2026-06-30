// FUNC_NAME: SomeManager::getSingleton
void SomeManager::getSingleton(int **outPtr)
{
    int *factoryPtr = *(int **)((int)this + 0x100); // +0x100: pointer to object factory/manager
    int local_4 = 0;
    int *tempPtr = 0;

    // First lookup with hash 0x383225a1 (unknown string)
    char result = ((char (*)(int))(*(int **)(*factoryPtr + 0x10)))(0x383225a1);
    if ((result == '\0') || (local_4 == 0))
    {
        local_4 = 0;
        // Second lookup with hash 0x55859efa (unknown string)
        result = ((char (*)(int, int*))(*(int **)(*factoryPtr + 0x10)))(0x55859efa, &local_4);
        if ((result == '\0') ||
            ((local_4 == 0 || (*(int *)(local_4 + 0xffc) == 0)) ||
             (local_4 = *(int *)(local_4 + 0xffc) + -0x48, local_4 == 0)))
        {
            *outPtr = (int *)&outPtr; // sentinel: store address of output pointer itself
            return;
        }
    }
    *outPtr = *(int **)(local_4 + 0x2894); // +0x2894: offset to desired singleton pointer
}