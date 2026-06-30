// FUNC_NAME: StreamManager::initialize
void StreamManager::initialize(int param_1, int param_2)
{
    int *iVar1;
    int iVar2;
    int local_10[3]; // stack buffer for creation parameters

    // Set vtable pointer at offset 0
    this->vtable = &PTR_FUN_00e36c60; // vtable for StreamManager
    this->field_4 = 1;                // +0x04
    this->field_8 = 0;                // +0x08

    local_10[0] = 0;
    local_10[1] = 0;
    local_10[2] = 0;

    // Get singleton manager (e.g., resource manager)
    iVar1 = (int *)FUN_009c8f80(); // getResourceManager()

    // Call virtual function at index 2 (e.g., lock or begin)
    (**(code **)(*iVar1 + 8))(); // ResourceManager::lock()

    // Create a sub-object via the manager
    iVar2 = FUN_004265d0(local_10, iVar1); // createStreamSubObject

    // Initialize sub-object at offset +0x0C (this->subObject)
    FUN_004ceb40(&this->subObject); // initSubObject

    if (iVar2 != 0) {
        // If creation succeeded, call virtual function at index 1 (e.g., attach)
        (**(code **)(*iVar1 + 4))(iVar2, 0); // ResourceManager::attach(iVar2, 0)
    }

    // Call virtual function at index 3 (e.g., unlock)
    (**(code **)(*iVar1 + 0xc))(); // ResourceManager::unlock()

    // Store the initialization parameters
    this->param1 = param_1; // +0x2C
    this->param2 = param_2; // +0x30
}