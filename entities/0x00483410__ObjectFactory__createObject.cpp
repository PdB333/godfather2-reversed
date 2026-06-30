// FUNC_NAME: ObjectFactory::createObject
int* ObjectFactory::createObject(void* classTypeId, int configData) {
    // Static pool initialization flag (bit 0)
    static int s_poolInitialized = 0;
    static int s_poolBase = 0;       // DAT_012239bc - base of object pool entries
    static int s_poolCount = 0;      // DAT_012239c0
    static int s_poolCapacity = 0;   // DAT_012239c4

    if ((s_poolInitialized & 1) == 0) {
        s_poolInitialized |= 1;
        s_poolBase = 0;
        s_poolCount = 0;
        s_poolCapacity = 0;
        atexit(poolCleanupFunction); // LAB_00d50740
    }

    int classIndex = resolveClassIndex(&classTypeId); // FUN_004838c0
    int config = configData;

    if (classIndex < 0)
        return nullptr;

    // Each pool entry is 0x10 bytes; entry offset = classIndex * 0x10 + 4??
    // Actually: iVar4*0x10 + 4 + s_poolBase => entry starts at poolBase + classIndex*16 + 4
    // The +4 might skip a header? We'll assume entry pointer is puVar1
    int* entryPtr = (int*)(classIndex * 0x10 + 4 + s_poolBase);
    if (entryPtr == nullptr)
        return nullptr;

    // Check optional config data format (bit 0 of byte at config+0x1c indicates inline config)
    byte* configBytes = (byte*)(config + 0x1c);
    if (*(byte*)(config + 0x1c) & 1) {
        configBytes = (byte*)(config + 0x1c); // already points to inline data?
    } else {
        // Unused: FUN_0043aff0(config, 0x48848ddb) — likely hash check
        char local_64;  // uninitialized!
        int local_58, local_54;
        int local_50[18];
        int* local_8;

        // The following block is essentially dead code due to uninitialized locals
        // but we preserve the structure for completeness
        FUN_0043aff0(config, 0x48848ddb); // some validation
        if (local_64 == '\0') {
            configBytes = (byte*)(*local_8 == 0) ? 0 : (byte*)(local_8 + 3);
        } else {
            if (local_58 == local_54) {
                configBytes = (byte*)(local_8 + 3);
            } else {
                configBytes = nullptr;
            }
        }
    }

    // If configBytes is valid and has bit8 set, parse embedded configuration
    if (configBytes && (*configBytes & 8)) {
        int skipSize = *(int*)(configBytes + 4);
        configBytes = configBytes + skipSize + 4; // skip header
    }

    int parsedData = 0;
    if (configBytes) {
        parsedData = parseConfigObject(configBytes); // FUN_00482680
    }

    // Call virtual constructor through entry's vtable (first method)
    int* newObject = (*(int*(*)(int, int))entryPtr[0])(config, parsedData); // iVar3 = config, uVar6 = parsedData
    int objectSize = entryPtr[2]; // size or offset to next field?

    if (parsedData) {
        // Setup additional fields: objectSize is used as offset from object start
        setupObjectFields(parsedData, newObject, (int)newObject + objectSize); // FUN_004828c0
        newObject[0xe] = (int)newObject + objectSize; // some boundary pointer
        newObject[0xd] = parsedData; // store parsed data reference
    }

    // Call post-construct virtual (second method) on the new object
    (*(void(*)(int))newObject[0])(config); // offset 4 from vtable? Actually *newObject is vtable, so +4 is second method

    if (parsedData) {
        attachObjectToScene(newObject, config); // FUN_0043b7c0
    }

    return newObject;
}