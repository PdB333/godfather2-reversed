// FUNC_NAME: applyDataFromArray
void __cdecl applyDataFromArray(int* object, int* dataArray, bool forceUpdate)
{
    int handleData;
    int* handlePtr;
    bool propertyExists;

    // Get the data manager singleton from global
    if (object != nullptr) {
        handleData = DataManager::getInstance(g_pDataManager); // DAT_01131018
    } else {
        handleData = 0;
    }

    // Process first resource handle at object +0x54
    int firstData = dataArray[0];
    handlePtr = (int*)(handleData + 0x54);
    if (firstData != 0 || forceUpdate) {
        if (*handlePtr != 0) {
            ResourceManager::releaseHandle(handlePtr);
        }
        ResourceManager::setHandle(handlePtr, firstData);
    }

    // Process second resource handle at object +0x6c
    int secondData = dataArray[1];
    handlePtr = (int*)(handleData + 0x6c);
    if (secondData != 0 || forceUpdate) {
        if (*handlePtr != 0) {
            ResourceManager::releaseHandle(handlePtr);
        }
        ResourceManager::setHandle(handlePtr, secondData);
    }

    // Check if object supports property 0x3fb43b57 (e.g., a property ID)
    int outValue = 0;
    propertyExists = (**(code**)(*object + 0x10))(0x3fb43b57, &outValue);
    if (propertyExists && object != nullptr) {
        // Copy property values from dataArray[2..6] into object offsets 0x290..0x2a0
        object[0xa4] = dataArray[2];
        object[0xa5] = dataArray[3];
        object[0xa6] = dataArray[4];
        object[0xa7] = dataArray[5];
        object[0xa8] = dataArray[6];
    }
}