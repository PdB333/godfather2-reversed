// FUNC_NAME: Manager::extractAndCall
// Address: 0x004b0cf0
// Role: Wrapper function that extracts fields from two objects and calls a function.

void __thiscall Manager::extractAndCall(Manager* param_1, Manager* param_2)
{
    // param_1 and param_2 are pointers to other objects.
    // The 'this' pointer is the current object.
    // Fields: field0 (offset 0x00), field1 (offset 0x04)
    // Callee: FUN_004b0d40 - likely performs an update or transformation.
    FUN_004b0d40(
        this->field0,
        param_2->field0,
        this->field1,
        param_1->field0,
        param_2->field0, // duplicate
        param_1->field1
    );
}