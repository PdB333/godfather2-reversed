// FUNC_NAME: GameObject::GameObject
// Address: 0x004761b0
// This is a constructor for a game object. It first calls the base class constructor,
// then optionally invokes an initialization function via a vtable entry if the flag is set.

class GameObject
{
public:
    // Constructor.
    // @param initFlag: If bit 0 set, also call the virtual Initialize function.
    explicit GameObject(byte initFlag)
    {
        // Call base class constructor (likely BaseObject).
        BaseObject_constructor();

        // Check if full initialization is requested.
        if (initFlag & 1)
        {
            // The vtable or class descriptor is accessed via global pointer + offset.
            // DAT_01223410 is a global base pointer (maybe to a class registry or kernel).
            // At offset +0x2D4 is a pointer to a vtable or class structure.
            // Then offset +0x04 is the function pointer for Initialize().
            // Call it with 'this' and 0 as argument.
            typedef void (__thiscall *InitFunc)(void*, int);
            int* pClassDesc = *(int**)(*(int*)(g_pGlobalBase + 0x2D4) + 4);
            InitFunc pInit = *(InitFunc*)(pClassDesc);
            pInit(this, 0);
        }
    }

private:
    // Placeholder for the base constructor called at 0x004761f0.
    void BaseObject_constructor();
};

// Assume the global base pointer exists.
extern int* g_pGlobalBase; // DAT_01223410