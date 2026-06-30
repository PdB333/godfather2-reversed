// FUNC_NAME: HavokPhysics::createPhysicsFromContainer
undefined4* __thiscall HavokPhysics::createPhysicsFromContainer(int* serializedData, uint context, int typeFlag)
{
    // Magic markers for Havok serialized data
    // The serialized data header should have these two DWORDs at the start
    int magic1 = 0x57E0E057;
    int magic2 = 0x10C0C010;

    // Local buffer (possibly for temporary data, zeros out)
    undefined localBuffer[0x40];
    _memset(localBuffer, -1, 0x40);
    *(uint*)&localBuffer[0] = 0x57E0E057;
    *(uint*)&localBuffer[4] = 0x10C0C010;
    localBuffer[0x20] = 0;  // +0x20 byte marker

    // Validate input serialized data magic values
    if (serializedData[0] == 0x57E0E057 && serializedData[1] == 0x10C0C010) {
        // Initialize Havok data loader
        HavokDataLoader::init();  // FUN_00bd3250
        HavokDataLoader::setup(serializedData, context);  // FUN_00bd3bc0

        if (typeFlag == 0) {
            // Load physics data from runtime manager
            uint managerHandle = HavokDataManager::getManager();  // FUN_00ab06a0
            int* physicsData = HavokDataManager::findPhysicsData(managerHandle);  // FUN_00bd57c0

            // Virtual call: get something from the context object
            // The context object has a vtable at offset +0x2c
            int someValue = (*(int(**)(void))(*(int*)context + 0x2c))();

            // Copy material IDs from source array to destination array
            int sourceArray = *(int*)(*(int*)(physicsData + 8) + i * 4);
            for (int i = 0; i < *(int*)(physicsData + 0xc); i++) {
                uint materialID = HavokDataManager::convertToNetworkOrder(*(uint*)(*(int*)(*(int*)(physicsData + 8) + i * 4) + 0x70));
                *(uint*)(*(int*)(physicsData + 0x44) + i * 4) = materialID;
            }

            // Allocate 12-byte Havok wrapper object
            HavokWrapper* wrapper = (HavokWrapper*)EAAlloc(0xc, 0);  // FUN_009c8e50
            if (wrapper != 0) {
                wrapper->vtable = &HavokWrapperVTable;  // PTR_FUN_00e39c30
                wrapper->someValue = someValue;
                wrapper->physicsData = physicsData;

                // Reference count increment?
                if (*(short*)(someValue + 4) != 0) {
                    *(short*)(someValue + 6) += 1;
                    HavokDataLoader::cleanup();  // FUN_00bd32d0
                    return wrapper;
                }
            }
            else {
                HavokDataLoader::cleanup();  // FUN_00bd32d0
                return 0;
            }
        }
        else if (typeFlag == 1) {
            // Load physics data from Havok container serialization
            int* rootContainer = (int*)HavokDataLoader::findSerializedData("hkRootLevelContainer");  // FUN_00bd57c0
            int* physicsData = HavokDataLoader::findDataByName(rootContainer, "hkpPhysicsData", 0);  // FUN_00bd5640

            if (physicsData != 0 && *(int*)(physicsData + 0x10) > 0) {
                int* materialArray = (int*)HavokDataLoader::findDataByName(physicsData, "EAMaterialArray", 0);  // FUN_00bd5640

                // Virtual call on context (same offset)
                int someValue = (*(int(**)(void))(*(int*)context + 0x2c))();

                // Allocate 16-byte Havok wrapper object
                int* rawMem = (int*)EAAlloc(0x10, 0);
                if (rawMem != 0) {
                    HavokWrapper* wrapper = HavokWrapperConstructor(rawMem, materialArray);  // FUN_0054a2f0
                    HavokDataLoader::cleanup();  // FUN_00bd32d0
                    return wrapper;
                }
            }
        }
        HavokDataLoader::cleanup();  // FUN_00bd32d0
    }
    return 0;
}