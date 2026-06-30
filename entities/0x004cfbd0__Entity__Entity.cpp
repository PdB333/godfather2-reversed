// FUNC_NAME: Entity::Entity
// Address: 0x004cfbd0
// Constructor for base Entity class. Calls base initialization (FUN_004cfbf0) and optionally calls a cleanup/destructor helper (FUN_009c8eb0) if param_2 & 1 is set.
// The byte parameter likely indicates whether the object is dynamically allocated (e.g., from pool) and needs special handling.

__thiscall Entity::Entity(byte isDynamic)
{
    this->initialize();      // FUN_004cfbf0 - base object init
    if (isDynamic & 1) {
        this->deinitialize(); // FUN_009c8eb0 - cleanup (e.g., free internal resources)
    }
    return this;
}