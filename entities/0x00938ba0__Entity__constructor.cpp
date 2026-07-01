// FUNC_NAME: Entity::constructor
void __fastcall Entity::constructor(Entity *this)
{
    // Set up initial vtable pointer (base class?)
    this->vtable0 = &g_EntityVTable0; // PTR_FUN_00d8a52c
    // Set secondary vtable or base pointer
    this->vtable1 = &g_EntityVTable1; // PTR_LAB_00d8a528

    // Call base class constructor (0 indicates no options? LAB_00938af0 is a function pointer)
    FUN_00607d50(0, &g_EntityBaseInit); // LAB_00938af0

    // Update secondary vtable again (derived class)
    this->vtable1 = &g_EntityVTable2; // PTR_LAB_00d8a524

    // Reset global initialization flag (static member or singleton state)
    g_EntityInitCount = 0; // DAT_011305b8

    // Finalize primary vtable to the actual class vtable
    this->vtable0 = &g_EntityClassVTable; // PTR_LAB_00e3e74c

    return;
}