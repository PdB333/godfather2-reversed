// FUNC_NAME: NPCCrewComponent::NPCCrewComponent
// Address: 0x0089c380
// Constructor for NPCCrewComponent. Initializes the component with a type flag (param2).
// param2: 0 = no leader handle, non-zero = obtain a leader handle via getLeaderHandle().

NPCCrewComponent* NPCCrewComponent::NPCCrewComponent(int param2)
{
    int handle;  // from getLeaderHandle() or 0

    if (param2 == 0) {
        handle = 0;
    } else {
        handle = getLeaderHandle();  // FUN_00481610
    }

    // Initialize base component with flags (1,1) — likely active/visible
    Component::initialize(1, 1);  // FUN_0064d390

    // Set base vtable and zero out initial fields
    this->m_vtable = &PTR_LAB_00e317dc;
    this->field_0x18 = 0;
    Component::setup(handle);          // FUN_00454a10
    this->field_0x24 = 2;              // Component type identifier (member)

    // Replace vtable with derived class vtable
    this->m_vtable = &PTR_LAB_00d7858c;
    this->m_subComponentVtable = &PTR_LAB_00d77e18;  // sub‑object vtable at offset +0x28
    this->m_funcPtr = &LAB_0089a1e0;   // function pointer at offset +0x30
    this->field_0x34 = 0;              // flag/field

    // Linked list pointer to the sub‑component (at offset +0x28)
    this->m_listNode = &(this->m_subComponentVtable);  // offset +0x14

    return this;
}