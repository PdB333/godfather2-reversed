// FUNC_NAME: SimNpc::SimNpc
// Address: 0x006f3860, Role: Constructor for SimNpc (inferred from double vtable pattern and four component inits)
__thiscall void SimNpc::SimNpc(SimNpc* this)
{
    // +0x00: vtable pointer - set to base subobject vtable (likely SimNpcBase or ComponentContainer)
    this->vtable = (void**)&PTR_FUN_00d60690;

    // Four identical initialization calls – probably initialise each of the four component slots (e.g., NPCBackUpComponent, NPCCrewComponent, etc.)
    this->initComponent(); // FUN_006f7b80
    this->initComponent(); // FUN_006f7b80
    this->initComponent(); // FUN_006f7b80
    this->initComponent(); // FUN_006f7b80

    // +0x00: vtable pointer - override to most derived class vtable (SimNpc final)
    this->vtable = (void**)&PTR_FUN_00d587e0;

    // Final constructor step (e.g., register with SimManager, set up scripting hooks)
    this->finalizeConstruction(); // FUN_004083d0
}