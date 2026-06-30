// FUNC_NAME: GameObject::GameObject
class GameObject {
public:
    // offset 0x00: vtable pointer (void*)
    // offset 0x2D0 (0xB4 * 4): objectIndex (int)
    int objectIndex; // +0x2D0
};

// External forward declaration for base constructor
void __fastcall initializeBase(void);

// Global vtable address (from data ref PTR_LAB_00e34ed0)
extern void* g_pVtable_GameObject;

// __fastcall: this pointer in ECX, no explicit parameter in signature
GameObject* __fastcall GameObjectConstructor(GameObject* thisPtr)
{
    // Call base class constructor
    initializeBase();

    // Compute this object's index within a global array.
    // Array element size is 0x410 bytes, base address fixed at 0x4846A4.
    thisPtr->objectIndex = (int)((char*)thisPtr - (char*)0x4846A4) / 0x410;

    // Set vtable pointer to the class-specific virtual table
    thisPtr->vtablePtr = &g_pVtable_GameObject;

    return thisPtr;
}