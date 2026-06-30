// FUNC_NAME: Player::onObjectInteraction

void __thiscall Player::onObjectInteraction(Player* this, void* pEventObject)
{
    char bCanActivate;
    int pGlobalManager;
    int effectHandle;
    int dummyParam;

    validateObject(pEventObject);
    if (pEventObject != (void*)0x0 && *(int*)((int)pEventObject + 0x1ed4) == 0x637b907) {
        pGlobalManager = getGlobalState();
        if (((*(uint*)(pGlobalManager + 0x5c) >> 0x1b & 1) == 0) &&
            (this->component != (void*)0x0 && *(int*)((int)this->component + 0x40) == 0x637b907)) {
            bCanActivate = canPerformAction();
            if (bCanActivate != '\0') {
                dummyParam = 0;
                effectHandle = createEffectParams(0, 0);
                playEffect(0x431128ef, 0x10, effectHandle, dummyParam);
                cleanupEffect();
            }
        }
    }
    return;
}