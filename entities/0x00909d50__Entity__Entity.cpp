// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(Entity *this) {
    // Set vtable pointers for multiple inheritance bases
    // Base class vtable at offset 0
    *(void**)this = &g_vtable_Entity_primary; // PTR_FUN_00d831f0
    // Second base vtable at offset 0x3C
    *(void**)((uint8_t*)this + 0x3C) = &g_vtable_Entity_base2; // PTR_LAB_00d831e0
    // Third base vtable at offset 0x48
    *(void**)((uint8_t*)this + 0x48) = &g_vtable_Entity_base3; // PTR_LAB_00d831dc
    // Fourth base vtable at offset 0x50
    *(void**)((uint8_t*)this + 0x50) = &g_vtable_Entity_base4; // PTR_LAB_00d831d8

    // Conditional initialization (global check)
    if (g_someGlobalFlag != 0) { // DAT_011298e4
        FUN_00909b90(this); // Possibly additional constructor work
    }

    // Initialize two sub-objects (e.g., transforms, matrices)
    // Sub-object at offset 0xCC (0x33*4)
    void *subObj1 = (uint8_t*)this + 0xCC;
    FUN_004086d0(subObj1); // Initialize subObject1 (likely a constructor of some kind)
    FUN_00408310(subObj1); // Additional initialization (e.g., set identity)

    // Sub-object at offset 0xC4 (0x31*4)
    void *subObj2 = (uint8_t*)this + 0xC4;
    FUN_00408310(subObj2); // Initialize subObject2

    // Override the fourth vtable pointer (offset 0x50) with a new vtable
    *(void**)((uint8_t*)this + 0x50) = &g_vtable_Entity_base4_override; // PTR_LAB_00e32854

    // Post-construction static/system hook
    FUN_0046c640(); // Possibly register with some manager
}