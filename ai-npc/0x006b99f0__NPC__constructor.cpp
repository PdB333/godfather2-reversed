// FUNC_NAME: NPC::constructor
void __fastcall NPC::constructor(undefined4 *obj)
{
    // Set vtable pointer (typically for NPC or derived class)
    *obj = &PTR_FUN_00d5e668; // vtable at offset 0x0

    // Set function pointers at offsets +0x3C and +0x48 (likely event/callback handlers)
    obj[0xf] = &PTR_LAB_00d5e658;  // +0x3C: pointer to some global function
    obj[0x12] = &PTR_LAB_00d5e654; // +0x48: pointer to another global function

    // Initialize subobject at offset +0x98 (0x26 * 4)
    // This subobject is likely a container or component (e.g., vector, list, or state machine)
    FUN_004086d0(obj + 0x26); // First stage construction (e.g., default init)
    FUN_00408310(obj + 0x26); // Second stage initialization (e.g., setup allocator)

    // Global initialization (e.g., register NPC manager or allocate shared resources)
    FUN_006bcd70();
}