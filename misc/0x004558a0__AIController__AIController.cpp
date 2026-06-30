// FUNC_NAME: AIController::AIController
// Address: 0x004558a0
// Constructor for AIController, initializes vtable, stores global singleton, and calls init on behavior object
AIController* __thiscall AIController::AIController(AIController* this, BehaviorBase* behavior)
{
    // +0x04: some flag/state initialized to 0
    this->field_4 = 0;                              
    // +0x08: secondary vtable pointer (first assignment)
    this->vtable2 = &PTR_LAB_00e31980;                

    // Store this as global singleton (DAT_01223450)
    gAIController = this;

    // +0x00: primary vtable
    this->vtable = &PTR_FUN_00e31970;                
    // +0x08: override secondary vtable (second assignment)
    this->vtable2 = &PTR_LAB_00e3197c;                
    // +0x0C: store behavior object pointer
    this->behavior = behavior;                        

    // Call virtual function at offset 8 (index 2) on behavior object: behavior->init()
    (*(void (__thiscall**)(BehaviorBase*))(*(uint32_t*)behavior + 8))(behavior);

    // Additional initialization (likely registers the AIController or sets up some engine integration)
    FUN_0049c6e0(&PTR_LAB_00e3196c, 1);               

    return this;
}