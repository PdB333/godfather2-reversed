// FUNC_NAME: EARSBaseObject::EARSBaseObject
// Function address: 0x006aaa00
// Role: Constructor for EARSBaseObject (base class with flag-controlled cleanup)

namespace EARS {
    class EARSBaseObject {
    public:
        // Constructor: initializes base and optionally calls cleanup if flag indicates heap allocation
        __thiscall EARSBaseObject(byte allocFlag) {
            // Call base class constructor or internal initialization
            this->baseConstructor();

            // If the low bit is set, schedule a cleanup (e.g., delete via memory manager)
            if ((allocFlag & 1) != 0) {
                this->deallocate();
            }

            // Return the constructed object pointer (this)
            return this;
        }

    private:
        // Internal: base initialization at 0x006aa570
        void baseConstructor();

        // Internal: cleanup/destruction helper at 0x009c8eb0
        void deallocate();
    };
}