// FUNC_NAME: AICarBehavior::getSteeringInput
uint __thiscall AICarBehavior::getSteeringInput(uint *outDirection, byte *outFlag)
{
    byte localFlag;
    byte *pFlag = outFlag;
    *outFlag = 0;

    // Map input direction from a base enum to a vehicle-relative direction
    // baseDirection: 0=neutral, 1=forward, 2=backward, 3=left, 4=right
    uint baseDirection = getBaseInputDirection();
    switch (baseDirection)
    {
    case 0:
        *outDirection = 0; // neutral
        break;
    case 1:
        *outDirection = 3; // left? (rotation)
        break;
    case 2:
        *outDirection = 4; // right?
        break;
    case 3:
        *outDirection = 1; // forward?
        break;
    case 4:
        *outDirection = 2; // backward?
        break;
    }

    // Get pointer to vehicle object (offset +0x188)
    uint vehiclePtr = *(uint *)(this + 0x188);
    if (vehiclePtr != 0)
    {
        uint vehicleBase = vehiclePtr - 0x48; // adjust to base of HavokWheeledVehicle/BaseVehicle
        if (vehicleBase != 0)
        {
            uint valid = isValid(vehicleBase);
            if (valid)
            {
                // Check if AI override flag is set (+0x90 bit 0)
                if ((*(byte *)(this + 0x90) & 1) != 0)
                {
                    // Read hardcoded flag from vehicle (offset +0x1B44)
                    if (vehiclePtr != 0)
                        *pFlag = *(byte *)(vehiclePtr + 0x1B44);
                    else
                        *pFlag = *(byte *)(0x00001B8C); // global? unlikely, but as in decompiled
                    return *outDirection;
                }

                // Virtual function call: vtable[4] (offset 0x10) with hash 0xA7039C8
                // Returns boolean, and also sets outFlag pointer if successful
                int *vtable = *(int **)(vehicleBase);
                int (*func)(int, byte **) = (int (*)(int, byte **))vtable[4];
                byte *tempFlagPtr = 0;
                int result = func(0xA7039C8, &tempFlagPtr);
                if (result != 0 && tempFlagPtr != 0)
                {
                    // Get two transform pointers (likely player and vehicle)
                    float *playerTransform = (float *)getPlayerTransform();
                    float *vehicleTransform = (float *)getPlayerTransform();
                    // Compute a signed angle difference??
                    // offset 0x34: z coordinate? or y?
                    // tempFlagPtr + 0x288: some scalar
                    float diff = (playerTransform[0x0D] - vehicleTransform[0x0D]) + *(float *)(tempFlagPtr + 0x288);
                    if (diff <= g_maxSteeringAngle || *outDirection != 0)
                    {
                        if (*outDirection == 1 || *outDirection == 2)
                        {
                            *pFlag = 0;
                            return *outDirection;
                        }
                    }
                }
                *pFlag = 1;
            }
        }
    }
    return 0;
}