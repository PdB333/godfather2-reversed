// FUNC_NAME: BaseGameObject::~BaseGameObject
// Address: 0x0054dbc0
// Role: Deleting destructor for BaseGameObject. Calls base class destructor (0x0054eed0),
//       then conditionally calls operator delete (0x009c8eb0) if flag bit 0 is set.
// Returns 'this' pointer to allow chaining with memory deallocation.

void* __thiscall BaseGameObject::destroy(byte flag) {
    // Call base class destructor (likely a core EARS base)
    this->baseDestructor(); // FUN_0054eed0

    // If the 'deleting' flag is set, free the object's memory
    if (flag & 1) {
        this->operatorDelete(this); // FUN_009c8eb0 - equivalent to ::operator delete
    }

    return this;
}