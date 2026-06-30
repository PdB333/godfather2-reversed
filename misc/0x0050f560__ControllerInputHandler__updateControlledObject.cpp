// FUNC_NAME: ControllerInputHandler::updateControlledObject
void __thiscall ControllerInputHandler::updateControlledObject(void* this_ptr, float deltaTime) 
{
    // Offset 0x58: pointer to controlled entity (character/vehicle etc.)
    int controlledEntity = *(int*)((char*)this_ptr + 0x58);
    // Offset 0x10: pointer to input device manager or global controller state
    int controllerMgr = *(int*)((char*)this_ptr + 0x10);
    // Check if controller is active (bit 0 of flag at +0x104)
    if ((controlledEntity != 0) && ((*(char*)(controllerMgr + 0x104) & 1) == 0)) 
    {
        // Access global controller slot array (thread-local storage pattern)
        uint controllerIndex = *(uint*)((char*)this_ptr + 8);
        int** fsBase = *(int***)(*(int*)0x2c + *(int*)0x2c); // simplified; actual FS-relative
        // Each controller slot is 0x?? bytes, this gets the analog input data (8 bytes: left thumbstick X/Y?)
        int* controllerDataBase = **(int**)(fsBase + 8); 
        long long* padData = (long long*)((char*)controllerDataBase + 0x80 + controllerIndex * sizeof(ControllerSlot)); 
        long long stickInput = *padData;                   // first 8 bytes (e.g., two floats or two shorts)
        int extraInput = *(int*)(padData + 1);             // next 4 bytes (could be right stick?)
        int packetNumber = *(int*)((char*)this_ptr + 0x44); // from input buffer

        // Clear kinematic flag (bit 3) on controlled entity (offset +0x94)
        *(unsigned int*)((char*)controlledEntity + 0x94) &= 0xfffffff7;
        // Store stick input into entity’s movement state (offset +0x80)
        *(long long*)((char*)controlledEntity + 0x80) = stickInput;
        // Combine extra input and packet number into second 8-byte value (offset +0x88)
        *(unsigned long long*)((char*)controlledEntity + 0x88) = ((unsigned long long)extraInput << 32) | packetNumber;

        // Clear physics or reset state on the controlled entity (0 = kinematic off?)
        FUN_0044f770(controlledEntity, 0); // likely RigidBody::setKinematic(bool)
    }

    // Check state at offset +0x70: 0 = unknown, 3 = some state, 5 = another
    char currentState = *(char*)((char*)this_ptr + 0x70);
    if ((currentState != '\0') && (currentState != '\x03') && (currentState != '\x05')) 
    {
        // Handle non‑standard state (e.g., cutscene, menu)
        FUN_00511f00(deltaTime); // probably character state update
        return;
    }
    // Default handling (e.g., vehicle or character control)
    FUN_00512240(this_ptr, deltaTime); // likely vehicle/character controller update
    return;
}