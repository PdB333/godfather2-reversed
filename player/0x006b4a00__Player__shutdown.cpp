// FUNC_NAME: Player::shutdown
void __thiscall Player::shutdown()
{
    char cVar1;

    // Release managed object at +0x19c (e.g., audio interface)
    if (m_pAudioInterface != nullptr) {
        releaseAudioInterface(m_pAudioInterface);
        m_pAudioInterface = nullptr;
    }

    // Release object at +0x174 (e.g., network component), passing this as context
    if (m_pNetworkComponent != nullptr) {
        releaseNetworkComponent(m_pNetworkComponent, this);
    }

    // Release singleton at +0xfc (e.g., global input system listener)
    if (m_pGlobalListener != nullptr) {
        releaseGlobalListener();
    }

    // Release object at +0xc0 (e.g., animation controller)
    if (m_pAnimationController != nullptr) {
        releaseAnimationController(this);
        m_pAnimationController = nullptr;
    }

    // Check controller manager at +0x40
    cVar1 = controllerManagerIsValid(m_pControllerManager);
    if (cVar1 != '\0') {
        releaseControllerManager(m_pControllerManager, this);
    }

    // Base class cleanup (e.g., Sentient::shutdown)
    baseShutdown();

    // Check another manager at +0x48 (e.g., dialog system)
    cVar1 = dialogManagerIsValid(m_pDialogManager);
    if (cVar1 != '\0') {
        releaseDialogManager(m_pDialogManager, this);
    }

    // Final shutdown routine (e.g., destroy components)
    finalShutdown(this);
}