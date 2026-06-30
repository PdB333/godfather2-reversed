// FUNC_NAME: SubComponentOwner::initSubComponent
// Address: 0x00620f70
// Initializes an embedded sub-object at offset 0x4 from the owning object.
// This is likely called during construction to set up a component (e.g., a physics or controller sub-component).
void __fastcall SubComponentOwner::initSubComponent() {
    // Access the sub-object at this+0x4 and call its initializer (0x0066f3f0).
    // The actual type of the sub-object is unknown but it's a fixed-size embedded member.
    SubComponent* subComponent = reinterpret_cast<SubComponent*>(reinterpret_cast<char*>(this) + 4);
    subComponent->init(); // Calls FUN_0066f3f0 (SubComponent::init)
}