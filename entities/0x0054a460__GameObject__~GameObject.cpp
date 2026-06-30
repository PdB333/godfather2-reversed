// FUNC_NAME: GameObject::~GameObject
// Function address: 0x0054a460
// Destructor for a base game object. Cleans up child components and releases a reference-counted shared pointer.
void __thiscall GameObject::~GameObject() {
    // Switch vtable to base class (to prevent virtual calls during destruction)
    *reinterpret_cast<void***>(this) = &g_vtable_GameObject_Base; // PTR_FUN_00e39c38

    // Destroy child list (dynamic array of function pointers to call with argument 0)
    // ChildrenList structure: +0x8 = pointer to array of destructors, +0xC = count
    ChildrenList* childrenList = reinterpret_cast<ChildrenList*>(this->field_0x8); // param_1[2]
    if (childrenList != nullptr && childrenList->count > 0) {
        for (int i = 0; i < childrenList->count; ++i) {
            void (*destructor)(int) = reinterpret_cast<void (*)(int)>(childrenList->array[i]);
            if (destructor) {
                destructor(0);
            }
        }
    }

    // Release shared pointer: decrement weak reference, delete if zero
    // RefControl structure: +0x0 = deleter function, +0x4 = strongRef (short), +0x6 = weakRef (short)
    RefControl* refCtrl = reinterpret_cast<RefControl*>(this->field_0x4); // param_1[1]
    if (refCtrl != nullptr && refCtrl->strongRef != 0) {
        refCtrl->weakRef -= 1;
        if (refCtrl->weakRef == 0) {
            void (*deleter)(int) = reinterpret_cast<void (*)(int)>(refCtrl->deleter);
            if (deleter) {
                deleter(1);
            }
        }
    }

    // Set vtable to final base class
    *reinterpret_cast<void***>(this) = &g_vtable_GameObject_Default; // PTR_LAB_00e39c34
}