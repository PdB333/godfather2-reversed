// FUNC_NAME: GameObject::GameObject
void __fastcall GameObject::GameObject(void* thisPtr)
{
    // Set vtable to base class (likely SimObject or NetObject)
    *(void**)thisPtr = &PTR_FUN_00e327c0;  // Base vtable at 0x00e327c0

    // Call base class constructor
    SimObject::SimObject(thisPtr);  // FUN_0043e380

    // Set vtable to this derived class (GameObject)
    *(void**)thisPtr = &PTR_LAB_00e30ea0;  // Derived vtable at 0x00e30ea0
}