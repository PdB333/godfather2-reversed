// FUNC_NAME: EARS::Framework::Entity::Entity
void __thiscall EARS::Framework::Entity::Entity(Entity *this) {
    // Set vtable to base class (EARS::Framework::Object)
    // PTR_LAB_00d6f648 is vtable for base Object
    this->vtable = reinterpret_cast<void**>(0x00d6f648);
    
    // Call base class constructor with a constant flag/size (0x25)
    // 0x25 (37) may be an ID, object size, or subtype identifier
    FUN_007f6420(0x25);  // BaseObject constructor or initializer
    
    // Update vtable to derived class (Entity)
    // PTR_LAB_00d6b95c is vtable for this Entity class
    this->vtable = reinterpret_cast<void**>(0x00d6b95c);
    
    // Call final initialization for derived class
    // Likely sets up additional fields or calls another init method
    FUN_0080ea60();
}