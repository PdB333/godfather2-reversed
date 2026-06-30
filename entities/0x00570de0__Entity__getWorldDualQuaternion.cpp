// FUNC_NAME: Entity::getWorldDualQuaternion
void __thiscall Entity::getWorldDualQuaternion(Entity *this, int unusedParam, float *outDualQuat) {
    // Stack layout for the virtual function call at vtable+0x10
    struct {
        Entity **ppThis;       // +0x00: address of temporary this pointer (allows relocation)
        int param2;            // +0x04: unused parameter
        float someFloat;       // +0x08: this->field_0x24 (offset: param_1[9] = *(int*)(this+0x24))
        float dq0;             // +0x0C: dual quaternion component 0
        float dq1;             // +0x10: dual quaternion component 1
        float dq2;             // +0x14: dual quaternion component 2
        float dq3;             // +0x18: dual quaternion component 3
        float dq4;             // +0x1C: dual quaternion component 4 (initialized to 0)
        float dq5;             // +0x20: dual quaternion component 5 (initialized to 0)
        float dq6;             // +0x24: dual quaternion component 6 (initialized to 0)
        float dq7;             // +0x28: dual quaternion component 7 (initialized to 0)
    } stack;

    // Setup temporary this pointer
    Entity *tempThis = this;
    stack.ppThis = &tempThis;
    stack.param2 = unusedParam;
    // this->field_0x24 (offset 0x24) minus global zero constant
    stack.someFloat = (float)this->field_0x24 - 0.0f;

    // Zero initializations as in the decompiled code
    stack.dq1 = stack.dq2 = stack.dq3 = 0.0f;
    stack.dq4 = 0.0f;
    stack.dq5 = stack.dq6 = stack.dq7 = 0.0f;
    // dq0 is left uninitialized (will be filled by the virtual call)

    // Call virtual function at vtable+0x10
    (*(void (__thiscall **)(void *))(*(int *)this + 0x10))(&stack);

    // Copy the dual quaternion to output
    outDualQuat[0] = stack.dq0;
    outDualQuat[1] = stack.dq1;
    outDualQuat[2] = stack.dq2;
    outDualQuat[3] = stack.dq3;
    outDualQuat[4] = stack.dq4;
    outDualQuat[5] = stack.dq5;
    outDualQuat[6] = stack.dq6;
    outDualQuat[7] = stack.dq7;
}