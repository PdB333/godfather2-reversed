// FUNC_NAME: EARS::Framework::Object::createOrDestroy
// Function at 0x00564b60
// Constructor-like initialization with optional destruction based on a flag (used for memory pool management)

class EARS::Framework::Object {
public:
    // @param deleteFlag: when bit 0 is set, calls destructor after base construction (placement delete pattern)
    void* createOrDestroy(uint8_t deleteFlag) {
        // Base class constructor (FUN_00564b90)
        baseConstructor();

        // If delete flag is set, call the destructor (FUN_009c8eb0)
        if (deleteFlag & 1) {
            destroy(this);
        }

        return this;
    }

private:
    void baseConstructor() {
        // Base class initialization (original at 0x00564b90)
        // Typically initializes fields, vtable, etc.
    }

    void destroy(void* ptr) {
        // Destructor or operator delete (original at 0x009c8eb0)
        // Frees resources or returns object to pool
    }
};