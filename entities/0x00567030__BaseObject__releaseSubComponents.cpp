// FUNC_NAME: BaseObject::releaseSubComponents
// Address: 0x00567030
// Role: Releases sub-components and notifies a global manager before marking the object as disposed.
// Fields:
//   this+0x58: function pointer for release callback (e.g., OnRelease)
//   this+0x0C: pointer to a child sub-object (vtable at *child+0x00, release function at vtable+0x04)
//   this+0x14: byte flag indicating whether the object has been released (1 = released)
//
// Global: DAT_012234e0 = pointer to singleton manager (vtable at *manager+0x00, releaseNotify at vtable+0x0C)

void __fastcall BaseObject::releaseSubComponents(BaseObject* this) {
    // If a release callback exists, invoke it (passing 0 as context)
    if (this->field_0x58 != nullptr) {
        this->field_0x58(0);
    }

    // Notify global manager of destruction
    if (DAT_012234e0 != nullptr) {
        (*(void (**)())(*(uint32_t*)DAT_012234e0 + 0x0C))();
    }

    // Release child sub-object if it exists
    if (this->child != nullptr) {
        // Call child's release function (vtable offset 0x04)
        (*(void (**)(BaseObject*))(*(uint32_t*)this->child + 0x04))(this);
        this->child = nullptr;
    }

    // Mark this object as released
    this->released = 1;
}