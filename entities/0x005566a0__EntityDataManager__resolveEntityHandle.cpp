// FUNC_NAME: EntityDataManager::resolveEntityHandle
int EntityDataManager::resolveEntityHandle(int param_2)
{
    uint handle = *(uint*)((int)this + 0x1C); // +0x1C: handle field
    int* rootObject = *(int**)((int)this + 0x00); // +0x00: pointer to root object

    int resolved = 0;

    // Handle type: top 2 bits
    if ((handle & 0xC0000000) == 0x80000000)
    {
        // Direct index (pointer to entity)
        resolved = handle * 4;
    }
    else if ((handle & 0xC0000000) == 0xC0000000)
    {
        // Indirect: fetch from global table at offset 0x60
        resolved = *(int*)(handle * 4 + 0x60);
    }

    if (resolved != 0)
        return resolved;

    // Fallback based on param_2
    if (param_2 == -1)
    {
        // Use default pointer from root object
        resolved = *(int*)((int)rootObject + 8); // +0x08: default object pointer
    }
    else
    {
        int entityType = *(int*)((int)rootObject + 0x0C); // +0x0C: type field (enum)
        char stackBuffer[528]; // used for one call path

        if (entityType == 0xB) // 11: e.g. kTypeVehicle
        {
            if (*(int*)((int)rootObject + 0x34) == 0) // +0x34: optional component ptr
            {
                // Virtual call via global function table at offset 0x10
                (**(code (**)(int))0x10)(param_2);
            }
            else
            {
                // Virtual call via component's vtable+0x10
                (**(code (**)(int))(*(int*)(*(int*)((int)rootObject + 0x34) + 0x10) + 0x10))(param_2);
            }
            return FUN_005413c0(); // returns status/error code
        }

        if (entityType == 0xA || entityType == 0x1E) // 10: kTypePlayer, 30: kTypeCrew
        {
            // Virtual call via root object's component vtable+0x10
            (**(code (**)(int))(*(int*)(*(int*)((int)rootObject + 0x10) + 0x10) + 0x10))(param_2);
            int status = FUN_005413c0();
            if (status == 0)
            {
                // Then call vtable+0x14 to get object pointer
                int* obj = (int*)((*(code (**)(int, char*))(*(int*)(*(int*)((int)rootObject + 0x10) + 0x10) + 0x14))(param_2, stackBuffer));
                if (*(int*)((int)obj + 0x0C) == 0x1C) // type matches e.g. kTypeItem
                {
                    obj = (int*)(*(int*)((int)obj + 0x14)); // dereference component offset
                }
                return *(int*)((int)obj + 8); // +0x08: object pointer
            }
            else
            {
                return status;
            }
        }
        // else: fall through to return 0
    }
    return resolved;
}