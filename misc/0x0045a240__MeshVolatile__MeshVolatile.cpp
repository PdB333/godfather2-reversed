// FUNC_NAME: MeshVolatile::MeshVolatile
void __thiscall MeshVolatile::MeshVolatile(void)
{
    // Set vtable pointer (primary)
    *(void**)this = &PTR_FUN_00e31b00;
    // Set secondary vtable pointer (e.g., for base class or interface)
    *(void**)((char*)this + 8) = &PTR_LAB_00e31b0c;

    // Register global resource block
    FUN_0049c7f0(&DAT_00e31ae4);
    // Register string-based resource type "MeshVolatile"
    FUN_0049c7f0("MeshVolatile");

    // Update secondary vtable pointer to another one (possibly after registration)
    *(void**)((char*)this + 8) = &PTR_LAB_00e31b10;

    // Clear global count/flag
    DAT_01223458 = 0;

    // Post-construction cleanup or initialization
    FUN_0049c640();
}