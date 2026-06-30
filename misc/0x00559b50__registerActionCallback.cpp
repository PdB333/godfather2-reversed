// FUNC_NAME: registerActionCallback
void registerActionCallback(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
    // Local struct used for registration data
    struct {
        undefined** globalPtrPtr; // +0x00: pointer to a global pointer (likely vtable or function table)
        uint8_t flag;             // +0x04: some flag, initialized to 0
        int32_t extraData;        // +0x05: store param_4 (unused?)
    } registrationData;

    // Pre-registration preparation (e.g., lock, validate)
    FUN_00557e20();

    // Setup registration data
    registrationData.extraData = param_4; // Possibly user data or context
    registrationData.flag = 0;
    registrationData.globalPtrPtr = &PTR_LAB_00dcf98c; // Points to a static global pointer table

    // Register the callback: (param_2, param_1, param_3, &registrationData)
    FUN_00c0a110(param_2, param_1, param_3, &registrationData);
}