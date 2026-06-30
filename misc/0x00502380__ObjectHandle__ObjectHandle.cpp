// FUNC_NAME: ObjectHandle::ObjectHandle
void __thiscall ObjectHandle::ObjectHandle(void *this, undefined4 param_2, undefined8 param_3, undefined8 param_4, undefined4 param_5, undefined8 param_6, undefined4 param_7) {
    // this is a pointer to an ObjectHandle structure.
    // The first field (+0x00) is a pointer to the actual object.
    unsigned int objPtr = *(unsigned int *)this; // dereference handle to get object pointer
    // At offset +0x14 in the object, there is a vtable pointer (or similar function table pointer).
    // Set it to a new vtable address (PTR_FUN_01124f94) and then adjust it by 4.
    **(undefined4 **)(objPtr + 0x14) = &PTR_FUN_01124f94;
    int *vtableSlot = (int *)(objPtr + 0x14);
    *vtableSlot = *vtableSlot + 4; // increment vtable pointer by 4 (skip first entry)
    // Call base constructor or initializer with the remaining parameters.
    FUN_00503410(param_2, param_3, param_4, param_5, param_6, param_7);
    return;
}