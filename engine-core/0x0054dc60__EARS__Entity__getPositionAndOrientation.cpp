// FUNC_NAME: EARS::Entity::getPositionAndOrientation
void __thiscall EARS::Entity::getPositionAndOrientation(void *this, struct OutputStruct1 *outStruct1, struct OutputStruct2 *outStruct2) {
    // Local variables used for intermediate storage, likely filled by virtual function call
    void *local0; // corresponds to local_30, but used as pointer and value
    unsigned int local1; // uStack_2c
    unsigned int local2; // uStack_24
    unsigned int local3; // uStack_20
    unsigned int local4; // uStack_1c

    // Call virtual function at vtable offset 0x18 from pointer at this+0x18
    // This function likely returns a struct (e.g., a quaternion + position) stored in the locals
    (**(code **)(**(int **)((char *)this + 0x18) + 0x18))();

    // Interpret outStruct1 as a struct with 3 fields:
    // field0: pointer (set to address of local0)
    // field1: value of local0
    // field2: value of local1
    *(void ***)&outStruct1->field0 = &local0;
    *(unsigned int *)((char *)outStruct1 + 4) = (unsigned int)local0;
    *(unsigned int *)((char *)outStruct1 + 8) = local1;

    // outStruct2 is an array of 3 unsigned ints
    outStruct2[0] = local2;
    outStruct2[1] = local3;
    outStruct2[2] = local4;
}