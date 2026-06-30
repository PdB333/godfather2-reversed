// FUNC_NAME: SomeManager::callRegisteredHandlers
void SomeManager::callRegisteredHandlers(undefined4 arg1, undefined4 arg2)
{
    uint count = *(uint *)(this + 0x173c); // m_handlerCount
    if (count != 0)
    {
        uint i = 0;
        do
        {
            // Each handler entry is 8 bytes: function pointer at offset 0, user data at offset 4
            int handlerArray = *(int *)(this + 0x1738); // m_handlerArray pointer
            int handlerFunc = *(int *)(handlerArray + i * 8);
            int userData = *(int *)(handlerArray + 4 + i * 8);
            (*(code *)handlerFunc)(arg1, arg2, userData);
            i++;
        } while (i < count);
    }
}