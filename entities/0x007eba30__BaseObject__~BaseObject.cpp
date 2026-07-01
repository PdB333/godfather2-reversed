// FUNC_NAME: BaseObject::~BaseObject
// Function at 0x007eba30: Destructor with optional heap deallocation flag.
// param_2 (byte): bit 0 set to free memory (operator delete) after base destruction.

class BaseObject {
public:
    // __thiscall - destructor returning this for chaining
    void* __thiscall ~BaseObject(byte freeFlag) {
        // Call base class destructor (or cleanup)
        FUN_007eb2f0(); // Base destructor

        // If flag indicates heap allocation, deallocate
        if (freeFlag & 1) {
            FUN_00624da0(this); // operator delete or free
        }

        return this;
    }
};