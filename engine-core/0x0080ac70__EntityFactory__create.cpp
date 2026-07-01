// FUNC_NAME: EntityFactory::create
void __fastcall EntityFactory::create(EntityFactory* this)
{
    bool bGameRunning;
    void* pNewObject;
    void* pInitialized;

    bGameRunning = isGameRunning();
    if (bGameRunning) {
        pNewObject = allocateMemory(0x80);  // allocate 128 bytes for new entity
        if (pNewObject == NULL) {
            pInitialized = NULL;
        } else {
            pInitialized = initializeEntity(this, pNewObject);  // construct object at address
        }
        pushAllocationRecord(&stack0x00000004);  // track allocation for cleanup
        registerEntity(pInitialized);
    }
    return;
}