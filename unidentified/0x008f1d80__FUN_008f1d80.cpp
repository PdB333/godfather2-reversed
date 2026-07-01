// FUNC_NAME: SomeComponent::attachToManager
void SomeComponent::attachToManager(int param_2) {
    extern SomeManager gSomeManager; // global manager instance at 0x0112fe28
    gSomeManager.initialize(); // initialize the manager (FUN_00408680)
    this->someId = param_2; // store the ID/handle at offset +0x1c
    gSomeManager.registerComponent(param_2, 0); // register this component with the manager (FUN_004c0b90)
}