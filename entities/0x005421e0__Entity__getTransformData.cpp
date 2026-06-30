// FUNC_NAME: Entity::getTransformData
void __thiscall Entity::getTransformData(Entity *this, TransformOutput *out1, TransformOutput *out2)
{
    // +0x260: pointer to some sub-object (e.g., renderable or model instance)
    void *subObject = *(void **)((char *)this + 0x260);
    
    if (subObject != nullptr) {
        // Virtual call at vtable offset 0x1c (index 7) on the sub-object's internal structure at +0x10
        // Likely updates or computes the transform
        void *inner = *(void **)((char *)subObject + 0x10);
        void **vtable = *(void ***)inner;
        void (*updateFunc)(void) = (void (*)(void))vtable[7];
        updateFunc();
        
        // Fill output1: constant pointer (maybe identity quaternion or axis), zero, and a stack buffer
        // The stack buffer (local_30) is uninitialized; the virtual call may write to it via side effects
        out1->field0 = (undefined4 *)&DAT_011397d0; // Constant data (e.g., quaternion identity or axis)
        out1->field1 = 0;                            // Typically zero
        out1->field2 = (char *)&local_30;           // Pointer to temporary buffer (floats, likely position)
        
        // Fill output2 with uninitialized stack values (possibly from the same buffer)
        out2->field0 = uStack_2c;
        out2->field1 = uStack_28;
        out2->field2 = uStack_24;
        return;
    }
    
    // No sub-object, zero out outputs
    out1->field0 = nullptr;
    out1->field1 = nullptr;
    out1->field2 = nullptr;
    out2->field0 = 0;
    out2->field1 = 0;
    out2->field2 = 0;
}