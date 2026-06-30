// FUNC_NAME: EARSLight::loadProperties
void __thiscall EARSLight::loadProperties(void) {
    undefined4 *pResult;
    undefined4 propManager;
    undefined4 radiusProp;
    undefined4 centerProp;
    undefined4 rotationProp; // Or colorProp

    // Virtual call to get some base pointer (e.g., getSceneNode? getConfig?)
    pResult = (undefined4 *)(*(code (__thiscall **)(EARSLight *))this->vtable)(); // Decompiled as **(code **)*this
    this->field_0x14 = *pResult;

    propManager = FUN_0060a380(); // Likely GetPropertyManager()
    this->field_0x15 = propManager;

    radiusProp = FUN_0060a580(propManager, "radius");
    this->field_0x12 = radiusProp; // radius property

    centerProp = FUN_0060a580(propManager, "center");
    this->field_0x11 = centerProp; // center property

    rotationProp = FUN_0060a580(propManager, &DAT_00e3ee08); // e.g., "rotation"
    this->field_0x13 = rotationProp; // rotation property

    *(byte *)(this + 0x4) = 0; // Zero out a flag byte
    return;
}