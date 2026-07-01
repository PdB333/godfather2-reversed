// FUNC_NAME: SomeClass::initializeFromData

// This function initializes parameters from a data template (likely damage/behavior data)
// parameters:
//   this: pointer to the object (ecx)
// returns: true if data was found and initialized, false otherwise

bool SomeClass::initializeFromData()
{
    // Check if the current state/type is valid (type 3 indicates a specific configuration)
    if (*(int *)(this + 0x50) == 3)
    {
        // Look up a data template using the identifier at offset 0x54
        int dataPtr = FUN_0084b3d0(*(int *)(this + 0x54));
        *(int *)(this + 0x1d0) = dataPtr; // Store pointer to data (or null)

        if (dataPtr != 0)
        {
            // Copy parameter from data +0x50 to this +0x144
            *(int *)(this + 0x144) = *(int *)(dataPtr + 0x50);

            // Special case: if the identifier matches a specific hash (0x637b907 = "player"?)
            if (*(int *)(this + 0x54) == 0x637b907)
            {
                // Use a global default value
                *(int *)(this + 0x1b4) = _DAT_00d5780c;
            }
            else
            {
                // Otherwise copy the value from data+0x4c
                *(int *)(this + 0x1b4) = *(int *)(dataPtr + 0x4c);
            }

            // Scale the same data+0x4c value by three different global constants
            // These likely represent different scale factors (e.g., damage, force, radius)
            *(float *)(this + 0x1bc) = *(float *)(dataPtr + 0x4c) * DAT_00d5779c;
            *(float *)(this + 0x1c0) = *(float *)(dataPtr + 0x4c) * DAT_00d5d7b8;
            *(float *)(this + 0x1c4) = *(float *)(dataPtr + 0x4c) * DAT_00e44620;

            // Copy a 3-component vector from data (+0x44, +0x40, +0x48) to this (+0x148, +0x14c, +0x150)
            // Possibly a position offset or direction
            *(int *)(this + 0x148) = *(int *)(dataPtr + 0x44);
            *(int *)(this + 0x14c) = *(int *)(dataPtr + 0x40);
            *(int *)(this + 0x150) = *(int *)(dataPtr + 0x48);

            return true;
        }
    }
    else
    {
        // Type mismatch: clear the stored data pointer
        *(int *)(this + 0x1d0) = 0;
    }
    return *(int *)(this + 0x1d0) != 0;
}