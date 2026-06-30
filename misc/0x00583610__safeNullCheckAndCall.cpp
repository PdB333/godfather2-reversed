// FUNC_NAME: safeNullCheckAndCall
int __fastcall safeNullCheckAndCall(void* pObject, void* pContext)
{
    // Check both pointers for validity before proceeding
    if (pObject != nullptr && pContext != nullptr)
    {
        // Delegate to underlying function that performs actual operation
        return FUN_00585a60(pObject);
    }
    return 0;
}