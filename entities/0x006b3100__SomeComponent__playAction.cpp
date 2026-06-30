// FUNC_NAME: SomeComponent::playAction
// Address: 0x006b3100
// Role: Dispatches between two action types based on a flag at +0xc4, retrieving a manager via FUN_0084b430/0084b400 and calling FUN_006b30c0 with a sub-object at offset +0x18 or +0x1c.

void __thiscall SomeComponent::playAction(SomeComponent* this) {
    int actionType = *(int*)((char*)this + 0xc4); // +0xc4: action type flag (0 or 1)

    if (actionType == 0) {
        // Type 0: retrieve manager via FUN_0084b430 using handle at +0x38
        void* manager = (void*)FUN_0084b430(*(int*)((char*)this + 0x38)); // +0x38: handle/ID
        if (manager != 0) {
            // Call action with sub-object at manager+0x18
            FUN_006b30c0(*(int*)((char*)manager + 0x18));
        }
    }
    else if (actionType == 1) {
        // Type 1: retrieve manager via FUN_0084b400 using handle at +0x38
        void* manager = (void*)FUN_0084b400(*(int*)((char*)this + 0x38));
        if (manager != 0) {
            // Call action with sub-object at manager+0x1c
            FUN_006b30c0(*(int*)((char*)manager + 0x1c));
        }
    }
}