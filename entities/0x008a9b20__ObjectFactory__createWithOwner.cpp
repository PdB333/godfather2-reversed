// FUNC_NAME: ObjectFactory::createWithOwner

void __thiscall ObjectFactory::createWithOwner(uint param_1, uint param_2)
{
    char isReady;
    int newObject;
    
    // Check if the system is initialized (FUN_00481640)
    isReady = isSystemReady();
    if (isReady != '\0') {
        // Allocate 64 bytes (FUN_009c8e50) - likely operator new(0x40)
        newObject = operatorNew(0x40);
        if (newObject != 0) {
            // Call constructor or initializer on param_1 (FUN_008a99d0)
            newObject = objectConstructor(param_1);
            // Store param_2 at offset 0x38 (e.g. m_pOwner or m_pParent)
            *(int *)(newObject + 0x38) = param_2;
            // Register the newly created object (FUN_00481690)
            registerObject(newObject);
            return;
        }
        // If allocation failed, store param_2 in a global variable
        // and register a null pointer
        g_pFallbackOwner = param_2;
        registerObject(0);
    }
    return;
}