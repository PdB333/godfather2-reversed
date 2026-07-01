// FUNC_NAME: Destructible::~Destructible
class Destructible;

// Forward declare base class destructor (likely from Entity or similar)
void __fastcall Entity::~Entity(Destructible* this);  // FUN_008b1cf0

// Global post-destruction hook (likely memory manager)
void __cdecl afterDestruct(); // FUN_00481520

// Destructor for a pointer member at +0x10 (e.g., a sub-object)
void __fastcall subObjectDtor(void* ptr); // FUN_009c8f10

void __thiscall Destructible::~Destructible(Destructible* this) {
    // Set vtable to base class vtable (destruction order)
    this->vtable = (void**)&PTR_FUN_00d7ab88;

    // Call base class destructor (handles base members)
    Entity::~Entity(this); // FUN_008b1cf0

    // Delete owned sub-object at +0x10
    if (this->m_subObject != nullptr) { // offset +0x10
        subObjectDtor(this->m_subObject); // presumably delete or destruct
    }

    // Post-destruction cleanup (e.g., memory pool release)
    afterDestruct(); // FUN_00481520
}