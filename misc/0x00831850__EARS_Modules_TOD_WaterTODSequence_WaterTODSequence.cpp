// Xbox PDB: EARS_Modules_TOD_WaterTODSequence_WaterTODSequence
// FUNC_NAME: WaterTODSequence::WaterTODSequence
// Address: 0x00831850
// Constructor for WaterTODSequence, a time-of-day sequence for water bodies.
// Inherits from a base TOD sequence class.

__thiscall WaterTODSequence* WaterTODSequence::WaterTODSequence(WaterTODSequence* this)
{
    // Call base class constructor (assumed TODSequence or EnvironmentSequence)
    TODSequence::TODSequence(this);

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d73a74;

    // Initialize flag at +0x24 (offset 0x24 = 9 * 4)
    this->field_0x24 = 1;   // likely "isActive" or "isLoaded"

    // Debug log class name for registration
    FUN_004d3bc0("WaterTODSequence");

    // Setup SEH/exception handling block (typical MSVC pattern)
    int exceptionFrame[3];
    void* handler;
    FUN_004d3e20(exceptionFrame);   // initializes exception frame

    // Get resource name pointer at +0x10, default to "DAT_0120546e" (probably empty or default string)
    char* resourceName = (char*)this->field_0x10;
    if (resourceName == NULL)
    {
        resourceName = (char*)&DAT_0120546e;
    }

    // Load or hash the resource and store result at +0x0C
    this->field_0x0C = FUN_004dafd0(resourceName);

    // Execute exception handler if present (standard SEH epilogue)
    if (exceptionFrame[0] != 0)
    {
        ((void (*)(int))handler)(exceptionFrame[0]);
    }

    return this;
}