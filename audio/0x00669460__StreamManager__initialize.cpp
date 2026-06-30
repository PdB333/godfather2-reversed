// FUNC_NAME: StreamManager::initialize
int StreamManager::initialize(int* outResult)
{
    *outResult = 0;
    // Check if not already initialized and if there are active references
    if (this->field8 != 1 && (this->field0 > 1 || *(uint*)&this->field12 > 1))
    {
        // Allocate 4 elements of 0x40 bytes each (total 0x100 bytes)
        void* allocatedMemory = calloc(4, 0x40);
        if (allocatedMemory == nullptr)
            return -2;

        int result = initPrimary();
        if (result == 0)
        {
            if (this->field8 == 0)
            {
                result = initSecondary();
                if (result == 0)
                    *outResult = 1;
            }
            result = 0;
        }
        cleanupInit();
        return result;
    }
    return -3;
}