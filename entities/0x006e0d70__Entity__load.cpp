// FUNC_NAME: Entity::load
undefined4 __fastcall Entity::load(int thisObj)
{
    ResourceManager* pManager;                    // from getResourceManager singleton
    int allocSuccess;                             // result of internal memory allocation
    undefined4 returnVal;                         // return value
    ComponentData* pComponentData;                // pointer to component at offset +0x58
    undefined4 notificationData;                  // data for state notification
    undefined4 allocFlags[3];                     // flags for allocation: 2, 0x10, 0

    pManager = (ResourceManager*)getResourceManager(); // FUN_009c8f80: singleton getter
    allocFlags[0] = 2;                            // e.g., pool or alignment flag
    allocFlags[1] = 0x10;                         // alignment
    allocFlags[2] = 0;
    // Allocate internal buffer of 0x200 bytes via vtable call on manager
    allocSuccess = (**(code**)*pManager)(0x200, &allocFlags);
    if (allocSuccess == 0) {
        returnVal = 0;                            // allocation failed
    } else {
        returnVal = initObject(thisObj);          // FUN_006e0620: initialise object fields
    }

    // Check state at +0x68: 0 = unloaded, 0x48 = loaded? 
    if ((*(int*)(thisObj + 0x68) == 0) || (*(int*)(thisObj + 0x68) == 0x48)) {
        // Get component at +0x58 (maybe a type hash or index)
        pComponentData = (ComponentData*)getComponentByType(thisObj + 0x58, 0); // FUN_00446100
        if (pComponentData != (ComponentData*)0x0) {
            // Call virtual function at offset 0x10 on component with message 0x383225a1 and stack flags
            (**(code**)(*pComponentData + 0x10))(0x383225a1, &allocFlags);
            notifyState(0);                       // FUN_006d68e0: maybe notify with code 0
        }
        allocSuccess = *(int*)(thisObj + 0x68);
        if ((allocSuccess == 0) || (allocSuccess == 0x48)) {
            // Get global value (e.g., current time) from another singleton
            notificationData = (**(code**)(*(int*)**(undefined4**)(DAT_012233a0 + 4) + 0xc))();
            notifyState(notificationData);        // FUN_006d68e0: notify with that value
        }
    }

    // Process or transition state machine at +0x68
    processState((int*)(thisObj + 0x68));         // FUN_006e03b0

    return returnVal;
}