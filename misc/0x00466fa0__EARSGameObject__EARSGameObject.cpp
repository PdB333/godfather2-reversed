// FUNC_NAME: EARSGameObject::EARSGameObject
// Address: 0x00466fa0
// Role: Constructor for a derived EARS game object class (likely with multiple inheritance based on vtable pointer placements)
// This function sets up virtual table pointers, calls a base constructor, initializes a global flag, and invokes an engine-wide init routine

void __fastcall EARSGameObject::EARSGameObject(EARSGameObject* this)  // __thiscall: ecx = this
{
    // Initialize vtable pointers for this object
    // The object layout appears to have multiple vtable slots at offsets 0x00, 0x04, 0x10
    // +0x00: primary vtable (base class or primary interface)
    this->vtbl0 = reinterpret_cast<PVOID>(0x00e31ef8);
    // +0x04: possibly a secondary base class vtable (interface)
    this->vtbl4 = reinterpret_cast<PVOID>(0x00e31f04);
    // +0x10: another vtable slot (often used for derived class adjustments or additional interfaces)
    this->vtbl16 = reinterpret_cast<PVOID>(0x00e31f14);

    // Call base class constructor (via function pointer at 0x0043e380)
    // This typically performs base class initialization and may set its own vtable
    BaseEARSObject_Constructor(this);  // FUN_0043e380

    // After base construction, update the vtable at offset 0x10 to a different table
    // This is typical when the derived class has its own overrides or when multiple inheritance
    // requires adjusting vtable pointers after base construction
    this->vtbl16 = reinterpret_cast<PVOID>(0x00e31f18);

    // Reset a global flag (likely a singleton or module-level initialization state)
    // DAT_0122346c might be a boolean or counter indicating whether the engine subsystem is ready
    g_EngineInitFlag = 0;  // DAT_0122346c

    // Perform global one-time engine initialization (e.g., register types, allocate shared pools)
    // This call is not related to this specific object but is included in this constructor
    // (possibly for convenience or due to initialization ordering)
    GlobalEngineInit();  // FUN_004083d0

    // Finally, set the primary vtable pointer to the final derived class vtable
    // This ensures that after construction, the object uses the correct virtual dispatch
    this->vtbl0 = reinterpret_cast<PVOID>(0x00e30ea0);
}