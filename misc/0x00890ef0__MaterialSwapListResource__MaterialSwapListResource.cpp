// FUNC_NAME: MaterialSwapListResource::MaterialSwapListResource
// Address: 0x00890ef0
// Constructor for MaterialSwapListResource, registers the resource type.

undefined4* __fastcall MaterialSwapListResource::MaterialSwapListResource(undefined4* this)
{
    // Call base class constructor (likely a generic resource base)
    // Base constructor address 0x0049c610
    FUN_0049c610(); // base class constructor call (no parameters?)

    // Set pointer at +0x08 to a data table (likely RTTI or static data)
    // +0x08: base vtable/data pointer? Overwritten later.
    this[2] = &PTR_LAB_00d77718;

    // Store this instance in a global singleton pointer
    // Global at 0x01129998 (likely g_currentMaterialSwapListResource)
    DAT_01129998 = this;

    // Set the primary vtable pointer at +0x00
    // vtable at 0x00d77720
    *this = &PTR_FUN_00d77720;

    // Overwrite +0x08 with a different pointer (derived class vtable/data)
    // +0x08: now points to derived class data table at 0x00d7771c
    this[2] = &PTR_LAB_00d7771c;

    // Initialize field at +0x0C to 0
    this[3] = 0;

    // Register this resource type with the resource system
    // FUN_0049c6e0 is likely ResourceManager::registerResourceType(const char*, int)
    FUN_0049c6e0("MaterialSwapListResource", 1); // type ID? 1 might be a resource type index

    return this;
}