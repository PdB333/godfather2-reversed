// FUNC_NAME: Entity::evaluateRangeTrigger
bool __fastcall Entity::evaluateRangeTrigger(int thisPtr) // thisPtr offset unknown, but used as base for +0x50, +0x54, +0x5c
{
    // unaff_EBX and unaff_ESI are likely float parameters passed in registers (nonstandard __fastcall extension)
    float localX, localY; // local_14[0], local_14[1]
    float* posPtr = (float*)(thisPtr + 0x5c); // pointer to a 3D position (or maybe offset of a component)
    char checkResult = FUN_008754e0(); // likely some global state check (e.g., isMissionActive)

    if (checkResult != 0) {
        localX = 0.0f;
        localY = 0.0f;

        // Dereference owner pointer at +0x54, subtract 0x48 to get base of the owner object
        int* ownerBase;
        if (*(int*)(thisPtr + 0x54) == 0) {
            ownerBase = nullptr;
        } else {
            ownerBase = (int*)(*(int*)(thisPtr + 0x54) - 0x48);
        }

        // First virtual call on owner: likely SetPosition or SetTarget relative to this object
        // vtable entry at 0x1c8 (index 114)
        (**(code**)(*ownerBase + 0x1c8))((float*)(thisPtr + 0x5c)); 

        // Second virtual call on owner: probably ComputeTransform or ProjectToGround
        (**(code**)(*ownerBase + 0xa4))(&localX, &stackTemp); // stackTemp is undeclared, likely a temporary

        // Get global player position (singleton from 0x00471610)
        int playerData = FUN_00471610(); // returns pointer to player state
        float dx = *(float*)(playerData + 0x30) - unaff_ESI; // player X
        float dy = *(float*)(playerData + 0x34) - unaff_EBX; // player Y
        float dz = *(float*)(playerData + 0x38) - localX;    // player Z

        // Check squared distance against the constant DAT_00d5f540
        if (dx*dx + dy*dy + dz*dz < DAT_00d5f540) {
            int ownerID;
            if (*(int*)(thisPtr + 0x54) == 0) {
                ownerID = 0;
            } else {
                ownerID = *(int*)(thisPtr + 0x54) - 0x48;
            }
            // Call trigger function (FUN_00883670) with parameters: pointer to float (posPtr?), triggerID at +0x50, and ownerID
            char triggerResult = FUN_00883670(&posPtr, *(undefined4*)(thisPtr + 0x50), ownerID);
            if (triggerResult == 0) {
                return true; // trigger activated
            }
        }
    }
    return false;
}