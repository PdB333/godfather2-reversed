// FUNC_NAME: VehicleControl::computeSteeringOrSpeed
void VehicleControl::computeSteeringOrSpeed(float* outValue)
{
    // 'this' pointer is the VehicleControl object (via ECX)
    // At offset 0x100, there is a pointer to an engine attribute system object (e.g., AttributeManager)
    AttributeManager* attrMgr = *(AttributeManager**)((char*)this + 0x100);

    // Vtable call at index 4 (offset 0x10) - likely getAttribute(hash, void** outPtr)
    float* attrPtr = nullptr;
    bool hasAttr = attrMgr->vtbl->getAttribute(0x383225a1, &attrPtr);  // hash likely corresponds to a steering or speed attribute

    if (hasAttr && (globalGameManager != nullptr)) // unaff_ESI likely globalGameManager
    {
        // Compute a value using a helper function
        // DAT_00e44564 - (globalGameManager->field_0x2890) is passed as the third argument
        float computedValue = FUN_006e3f90(
            this,
            __return_addr__,                     // unaff_retaddr is likely the return address passed as a parameter
            DAT_00e44564 - *(float*)(globalGameManager + 0x2890),
            DAT_00d5fa88,
            DAT_00d5ccf8
        );
        *outValue = computedValue;
    }
    else
    {
        *outValue = 0.0f;
    }
}