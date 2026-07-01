// FUNC_NAME: Entity::Entity
// Address: 0x008f0b90
// Role: Constructor for Entity with optional sub‑object initialization.
// param_2: flag byte – if bit 0 set, also constructs a sub‑object (e.g., a component).

Entity::Entity(bool initSubObject) {
    // Call base class constructor (common initialization)
    Entity::baseConstructor(); // formerly FUN_008efe80

    if (initSubObject) {
        // Initialize the optional sub‑object
        Entity::initSubObject(this); // formerly FUN_009c8eb0
    }

    // Constructor implicitly returns 'this'
}