// FUNC_NAME: ObjectStateMachine::updateAndSendState
void ObjectStateMachine::updateAndSendState(void)
{
    int *pConfigTable; // piVar2 - pointer to configuration table at this+0x1c
    int configData; // iVar4
    int eventParam; // iVar5
    int extraECX; // extraout_ECX
    int stateIndex; // local_10 - index derived from some state
    int stateFlags; // local_14 - flags from a previous call
    uint *pFlagsArray; // puVar1

    pConfigTable = *(int **)(this + 0x1c); // Get pointer to config table from object at offset 0x1c
    *(int *)(this + 8) = *(int *)(this + 4); // Save previous state? (this+4 -> this+8)
    if (*(int *)(this + 0x14) == 0x11f) { // Check if current state is a specific high-value (0x11f = 287)
        // Call some function with this+0x10, store result in this+0xc
        *(int *)(this + 0xc) = FUN_00639c70(this + 0x10);
    } else {
        // Shift state history: current -> prev, new -> current
        *(int *)(this + 0xc) = *(int *)(this + 0x14);
        *(int *)(this + 0x10) = *(int *)(this + 0x18);
        *(int *)(this + 0x14) = 0x11f; // Set new state to 0x11f
    }

    configData = FUN_0063fc10(); // Check server/authority state? Returns 0 if server?
    if ((configData == 0) && (extraECX != 0x3b)) { // extraECX likely captured from ECX after the call (maybe this->someMember?)
        eventParam = FUN_0063f220(); // Get some event parameter
        if (stateFlags == 0xc) { // stateFlags might be from the previous call's ECX or global
            pFlagsArray = (uint *)(*(int *)(*pConfigTable + 0xc) + stateIndex * 4);
            *pFlagsArray &= 0xffff803f; // Clear bits 6-14 (clear animation flags)
            if (eventParam == 1) {
                *pFlagsArray = (*pFlagsArray & 0xffffffda) | 0x1a; // Set specific bits (1,3,4)
            }
            configData = pConfigTable[0xd]; // Some config value at offset 0x34
            eventParam = -1;
        } else if (eventParam == 1) {
            configData = FUN_00642f30(); // Handle specific case
        } else {
            FUN_00642ec0(); // Default handling
            configData = pConfigTable[0xd];
        }
    } else {
        eventParam = 0;
        configData = 0;
    }

    // Build and send a network event packet
    // Packet format: (eventParam+1)*0x8000 | (configData<<24) | 0x1b
    FUN_006438e0(
        ((eventParam + 1) * 0x8000) | (configData << 0x18) | 0x1b,
        *(undefined4 *)(*(pConfigTable + 3) + 8) // Some context handle at pConfigTable[3]+8
    );
}