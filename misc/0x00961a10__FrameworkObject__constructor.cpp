// FUNC_NAME: FrameworkObject::constructor
// Address: 0x00961a10
void __fastcall FrameworkObject::constructor(FrameworkObject* this)
{
    // Run global initialization (likely EARS engine bootstrap)
    engineBootstrap(); // FUN_00932ce0

    // Call virtual initialize method (vtable offset 0x2c, likely onRegister or postConstruct)
    this->vtable[0x2c](this);

    // Build registration data structure
    struct ObjectRegistration {
        int globalId;   // +0x00: Unique ID from global constant
        int reserved;   // +0x04: Always 0
        int flags;      // +0x08: Always 0
    } regData;

    regData.globalId = DAT_01130310; // EARS global identifier (e.g., object type GUID)
    regData.reserved = 0;           // Unused field
    regData.flags = 0;              // No special flags

    // Register this object in the global manager (e.g., SimManager, EntityManager)
    registerObjectInManager(&regData, 0); // FUN_00408a00(&regData, 0)
}