// FUN_NAME: GameObject::getXCoordinate
float GameObject::getXCoordinate(int identifier)
{
    // Check if a custom flag is set at offset 0xE4
    if (*(char *)(this + 0xE4) != '\0')
    {
        // Return directly stored X coordinate from offset 0x148, scaled by a global factor and offset
        return (*(float *)(this + 0x148) * *(float *)0x00e445c8) + *(float *)0x00e2e6f4;
    }

    // Obtain index from the provided identifier via helper function
    int index = FUN_00424c90(identifier); // Returns an index into an array of structures

    // Base pointer to an array of structures (each 0x1D0 bytes) is stored at this+0x10
    int *arrayBase = *(int **)(this + 0x10);

    // Retrieve the X coordinate from the indexed structure at offset 0x30, then add global offset
    return *(float *)(arrayBase + index * 0x1D0 + 0x30) + *(float *)0x00e2e6f4;
}