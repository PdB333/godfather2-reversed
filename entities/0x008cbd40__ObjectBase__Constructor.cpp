// FUNC_NAME: ObjectBase::Constructor

class ObjectBase
{
public:
    // Vtable pointer at offset 0x00; set to 0x00d7c2e8 in constructor
    void** vftable;

    // Static global data referenced by base initializer
    static int g_someGlobal; // DAT_012069d4

    // Constructor: must be called with allocFlag indicating dynamic allocation
    __thiscall ObjectBase* Constructor(byte allocFlag)
    {
        // Assign virtual function table
        this->vftable = reinterpret_cast<void**>(0x00d7c2e8);

        // Base class / subsystem initialization
        // - Increments a reference count or acquires a lock on g_someGlobal
        sub_4086d0(&g_someGlobal);

        // - Performs static engine initialization (e.g., register object types)
        sub_4083d0();

        // If the object was allocated with 'new', perform additional cleanup/registration
        if ((allocFlag & 1) != 0)
        {
            sub_9c8eb0(this); // Possibly releases temporary resources or registers with manager
        }

        return this;
    }
};

// Helper definitions for the called functions (addresses known from binary)
void sub_4086d0(int* globalData); // Initialization of global count/lock
void sub_4083d0();                 // Static engine setup
void sub_9c8eb0(ObjectBase* obj);  // Conditional destructor/cleanup (called only on dynamically allocated objects)