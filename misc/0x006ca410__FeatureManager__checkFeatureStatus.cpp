// FUNC_NAME: FeatureManager::checkFeatureStatus
void __thiscall FeatureManager::checkFeatureStatus(FeatureProvider* provider) {
    // Call virtual function at vtable+0x10 (index 4) with a hash key (feature identifier)
    uint featureKey = 0x55859efa;
    bool enabled = provider->vtable[0x10 / sizeof(void*)](provider, featureKey); // returns char, treat as bool

    // The second condition is a compiler artifact (restarted for deadcode elimination), effectively always true
    if (enabled) {
        this->featureEnabled = true; // byte at +0x7c
    } else {
        this->featureEnabled = false;
    }

    if (this->featureEnabled) {
        this->featureValue = _DAT_00d5780c; // int at +0x80, global feature value (likely a pointer or flag)
    } else {
        this->featureValue = 0;
    }
}