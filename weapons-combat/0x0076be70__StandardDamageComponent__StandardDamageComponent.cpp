// FUNC_NAME: StandardDamageComponent::StandardDamageComponent
StandardDamageComponent * __thiscall StandardDamageComponent::StandardDamageComponent(StandardDamageComponent *this, undefined4 param_2, undefined4 param_3) {
    int iVar1;
    float fVar2;
    float10 fVar3;

    Component::Component(param_2, param_3);                                     // base class constructor
    iVar1 = this->manager;                                                     // +0x5C: pointer to GodfatherGameManager or similar
    this->vtable = (void *)&PTR_LAB_00d66044;                                  // set vtable pointer
    fVar3 = (float10)Time::getCurrentTime();                                   // current game time
    this->creationTime = (float)fVar3;                                         // +0x74: store creation timestamp
    fVar2 = (float)*(int *)(iVar1 + 0x24bc);                                    // read health/damage value from manager (e.g., playerVehicleHealth)
    if (*(int *)(iVar1 + 0x24bc) < 0) {                                        // clamp negative values
        fVar2 = fVar2 + DAT_00e44578;                                          // add 1.0 or similar bias
    }
    this->healthScale = fVar2 * DAT_00d5efb8;                                  // +0x70: store scaled health multiplier
    return this;
}