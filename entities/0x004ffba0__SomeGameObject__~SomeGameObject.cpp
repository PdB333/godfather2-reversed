// FUNC_NAME: SomeGameObject::~SomeGameObject

// 0x004ffba0: Destructor for SomeGameObject (EA EARS engine).
// Calls base destructor, then optionally deallocates memory if the delete flag is set.
SomeGameObject::~SomeGameObject(int deleteFlag)
{
    // Call base class destructor (e.g., ~EARSObject or ~SimObject)
    this->~BaseObject(); // FUN_004ff3d0

    // If bit 0 of deleteFlag is set, free the memory via operator delete
    if ((deleteFlag & 1) != 0) {
        operator delete(this); // FUN_009c8eb0
    }
}