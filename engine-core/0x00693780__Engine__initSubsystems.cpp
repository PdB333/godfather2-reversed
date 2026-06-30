// FUNC_NAME: Engine::initSubsystems
void Engine::initSubsystems(void) {
    int *pPrimaryObject;   // iVar1 - first allocation (size 0x1C)
    int *pSecondaryObject; // iVar2 - second allocation (size 0x28)

    // Allocate 28-byte primary object
    pPrimaryObject = (int *)allocateMemory(0x1C);
    if (pPrimaryObject != nullptr) {
        pPrimaryObject = (int *)initPrimaryObject(pPrimaryObject);
    }

    // Allocate 40-byte secondary object (used as prerequisite)
    pSecondaryObject = (int *)allocateMemory(0x28);
    if (pSecondaryObject == nullptr) {
        g_thirdObject = 0;
    } else if (pPrimaryObject == nullptr) {
        g_thirdObject = createThirdObject(0);
    } else {
        g_thirdObject = createThirdObject(pPrimaryObject + 1); // offset +4 (offset 0x04)
    }

    // Initialize two additional subsystems
    initSystemA();
    initSystemB();

    if (pPrimaryObject != nullptr) {
        *(int *)(g_gameContext + 0x570) = (int)(pPrimaryObject + 1);
        return;
    }
    *(int *)(g_gameContext + 0x570) = 0;
}