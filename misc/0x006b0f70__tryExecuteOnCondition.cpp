// FUNC_NAME: tryExecuteOnCondition
void __cdecl tryExecuteOnCondition(void* context, void* actionData) {
    int result = FUN_006b0ee0(context);  // Check condition on context
    if (result != 0) {
        FUN_006b25c0(actionData);       // Execute action if condition true
    }
}