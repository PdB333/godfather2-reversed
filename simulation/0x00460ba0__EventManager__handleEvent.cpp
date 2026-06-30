// FUNC_NAME: EventManager::handleEvent

void __thiscall EventManager::handleEvent(int* thisPtr, int* event)
{
    int* stack_event_backup; // ebp? actually piStack_4
    int typeId;
    int objectHandle;
    int* convertedEvent; // local param_2 reused

    // Call virtual pre-handle function at vtable+0x128
    (*(void (__thiscall**)(int*))(*thisPtr + 0x128))(thisPtr);

    if (event == 0)
        return;

    // event+0x18 is a pointer to class info structure, +8 is type ID
    typeId = *(int*)(*(int*)(event + 0x18) + 8);

    if (typeId == 0x1961bed) 
    {
        // Direct event: object handle at event+0x14
        objectHandle = *(int*)(event + 0x14);
    }
    else 
    {
        if (typeId != -0xc0deffc) // 0xF3F21004
            goto cleanup;

        // Indirect event: resolve handle via conversion
        int* unresolvedHandle = (int*)(event + 0x14);
        int temp_param2 = 0;
        int* temp_ptr = 0;
        FUN_00460b00(*unresolvedHandle, &temp_param2, &temp_ptr, &DAT_00e2f044);
        objectHandle = temp_param2;
        if (temp_param2 == 0)
            goto cleanup;
    }

    // Process the resolved object handle
    FUN_004608c0(objectHandle);

cleanup:
    // Release the original event
    FUN_0046ee30(event);
    return;
}