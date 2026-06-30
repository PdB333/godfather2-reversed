// FUNC_NAME: PlayerCrewLeaderComponent::constructor

undefined4* __thiscall PlayerCrewLeaderComponent::constructor(PlayerCrewLeaderComponent* this, byte allocFlag)
{
    // Set primary vtable at offset 0x00
    this->vtablePrimary = &PTR_FUN_00d5e618;
    // Set secondary vtable for first base class at offset 0x3C (0x0F * 4)
    this->vtableBase1 = &PTR_LAB_00d5e608;
    // Set secondary vtable for second base class at offset 0x48 (0x12 * 4)
    this->vtableBase2 = &PTR_LAB_00d5e604;

    // Initialize subobject at offset 0x64 (0x19 * 4)
    // This is likely an embedded component (e.g., a TNL::Object or state machine)
    EARS::Framework::SubObjectType* subObj = reinterpret_cast<EARS::Framework::SubObjectType*>(&this->subObject);
    FUN_004086d0(subObj);  // subobject constructor (e.g., EARS::Framework::RefCounted::constructor)
    FUN_00408310(subObj);  // subobject initialization (e.g., set default vtable or reference counting)

    // Global engine initialization (e.g., register this class in a factory)
    FUN_0046c640();

    // If the object was allocated with 'new' (allocFlag & 1), free the memory
    // (This pattern is typical for EA EARS constructors: if allocFlag indicates heap allocation,
    //  and if construction fails later, the constructor will delete itself. Here it's done unconditionally?)
    if (allocFlag & 1)
    {
        FUN_0043b960(this, 0x74);  // operator delete with size 0x74 (sizeof PlayerCrewLeaderComponent)
    }

    return this;
}