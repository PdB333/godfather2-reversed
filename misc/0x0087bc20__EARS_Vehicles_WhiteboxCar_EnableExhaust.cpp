// Xbox PDB: EARS_Vehicles_WhiteboxCar_EnableExhaust
//FUNC_NAME: Vehicle::updateExhaustEffects
// Address: 0x0087bc20
// Manages left and right exhaust particle effects based on vehicle state and bone availability.

void __thiscall Vehicle::updateExhaustEffects(bool enable)
{
    int tempPtr[4]; // local_14, used for bone lookup result
    tempPtr[0] = (int)this;

    if (!enable)
    {
        // Disable: stop existing exhaust effects
        if (*(int*)(this + 0xa04) != 0) // leftExhaustEffect
        {
            stopEffect(*(int*)(this + 0xa04)); // FUN_004df590
        }
        if (*(int*)(this + 0xa08) != 0) // rightExhaustEffect
        {
            stopEffect(*(int*)(this + 0xa08)); // FUN_004df590
        }
    }
    else
    {
        // Enable: check if any exhaust bone is present
        bool hasExhaustBone = (*(int*)(this + 0x9d0) != 0) ||  // exhaustBone0
                              (*(int*)(this + 0x9d4) != 0) ||  // exhaustBone1
                              (*(int*)(this + 0x9d8) != 0) ||  // exhaustBone2
                              (*(int*)(this + 0x9dc) != 0);    // exhaustBone3
        if (hasExhaustBone)
        {
            setupExhaustSystem(); // FUN_00471610

            int state = *(int*)(this + 0xa00); // exhaustState: 0=left, 1=right, 2=both
            if (state == 0 || state == 2)
            {
                // Left exhaust
                if (*(int*)(this + 0xa04) == 0) // leftExhaustEffect not yet created
                {
                    int effect = findBoneByName(tempPtr, (int*)(this + 0x9d0), "BP_exhaust_L"); // FUN_0087bac0
                    attachEffect(effect); // FUN_00414db0
                    if (tempPtr[0] != 0)
                    {
                        *(int*)(tempPtr[0] + 8) = 0; // clear some flag
                    }
                }
                else
                {
                    updateEffect(*(int*)(this + 0xa04)); // FUN_004df5c0
                }
            }
            if (state == 1 || state == 2)
            {
                // Right exhaust
                if (*(int*)(this + 0xa08) != 0) // rightExhaustEffect already exists
                {
                    updateEffect(*(int*)(this + 0xa08)); // FUN_004df5c0
                    return;
                }
                int effect = findBoneByName(tempPtr, (int*)(this + 0x9d0), "BP_exhaust_R"); // FUN_0087bac0
                attachEffect(effect); // FUN_00414db0
                if (tempPtr[0] != 0)
                {
                    *(int*)(tempPtr[0] + 8) = 0; // clear some flag
                    return;
                }
            }
        }
    }
}