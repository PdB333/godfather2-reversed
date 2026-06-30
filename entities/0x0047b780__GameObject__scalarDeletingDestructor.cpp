// FUNC_NAME: GameObject::scalarDeletingDestructor
// Function address: 0x0047b780
// Role: Scalar deleting destructor (calls actual destructor, then optional global deallocation)

// This pattern is common in MSVC-compiled code: a destructor with a byte parameter
// indicating whether to free memory after destruction. When param_2 & 1 is set,
// it calls a deallocation function pointer obtained from a global singleton.

class GameObject;

// Forward declaration of the internal destructor body (at 0x0047b7e0)
void __thiscall GameObject::destructorBody(void);

// Global data reference (offset into a global singleton, likely an allocator/manager)
extern uintptr_t DAT_01223410;  // +0x2d4

uint32_t __thiscall GameObject::scalarDeletingDestructor(GameObject *this, byte param_2)
{
    // Call the actual destructor body
    this->destructorBody();

    // If the "delete" flag is set, invoke the global deallocator
    if ((param_2 & 1) != 0) {
        // Obtain function pointer from global table:
        //   at DAT_01223410 + 0x2d4: pointer to a vtable? (int**)
        //   dereference that to get a pointer to function pointers
        //   add 4 to get the second entry (likely operator delete or equivalent)
        void (__thiscall *deallocator)(GameObject *, int) =
            (void (__thiscall*)(GameObject *, int))
            (**(int **)(*(int *)DAT_01223410 + 0x2d4) + 4);
        deallocator(this, 0);
    }
    return (uint32_t)this;
}