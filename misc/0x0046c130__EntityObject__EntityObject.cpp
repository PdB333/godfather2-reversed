// FUNC_NAME: EntityObject::EntityObject

class EntityObject {
public:
    EntityObject();
    void* vtable; // offset +0x00
};

// Constructor for derived entity object
EntityObject::EntityObject(void) {
    // Set vtable pointer (class-specific function table)
    this->vtable = (void*)&PTR_FUN_00e327e4;
    // Call base class initializer (likely EARSObject or similar)
    FUN_0043e2e0(this);
}