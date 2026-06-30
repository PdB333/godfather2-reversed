// FUNC_NAME: Entity::constructor
// Address: 0x006d60a0
// Role: Constructor for the base Entity class (EARS engine). Sets up primary vtable, two interface vtable pointers, then constructs and initializes a subcomponent at offset +0x50 (likely a networking or reflection component). Finally calls a global singleton init function (possibly NetSession::init or similar).

void __fastcall Entity::constructor(Entity *this) {
    // Set main vtable at offset 0x00
    this->vtable = (EntityVTable *)&PTR_FUN_00d5f45c;
    // Interface vtable pointers at offsets +0x3C and +0x48
    this->networkInterface = (void *)&PTR_LAB_00d5f44c;  // +0x3C
    this->reflectInterface = (void *)&PTR_LAB_00d5f448;  // +0x48
    // Subcomponent at offset +0x50 (e.g., NetReflectable or SimObject)
    Component::constructor((Component *)((char *)this + 0x50)); // FUN_004086d0
    Component::init((Component *)((char *)this + 0x50));        // FUN_00408310
    // Global singleton/resource initialization
    FUN_0046c640(); // e.g., NetSession::initializeSingleton()
}