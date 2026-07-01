// FUNC_NAME: RandomEventTrigger::updateTimedCheck
uint __fastcall RandomEventTrigger::updateTimedCheck(RandomEventTrigger* this) {
    float* thresholdPtr;
    uint randomValue;
    int randomInt;
    float lerpedValue;
    float minThreshold;
    float newThreshold;
    PropertyStructure propertyStruct;
    float* valuePtr;
    byte flagsByte;

    randomValue = _rand();
    // Check if enough time has passed since last event (cooldown)
    if (g_currentTime - this->lastEventTime < (float)(int)randomValue * g_randScale) {
        this->flags |= 1;  // Bit 0: event triggered
        activateEffect1();  // FUN_00837020
        activateEffect2();  // FUN_008370e0
        randomInt = _rand();
        lerpedValue = (float)randomInt * g_randScale;
        this->timerState = 0;
        minThreshold = this->thresholdBase * g_thresholdMultiplier;
        thresholdPtr = &this->thresholdBase;
        lerpedValue = (this->maxRange - this->minRange) * lerpedValue + this->minRange;
        this->targetValue = lerpedValue;
        if (lerpedValue < minThreshold) {
            *thresholdPtr = lerpedValue * g_adjustmentFactor;
        }
        newThreshold = *thresholdPtr;
        valuePtr = &newThreshold;
        propertyStruct = g_propertyTemplate1;  // DAT_0112dbe0
        flagsByte = 0;
        setProperty(&propertyStruct, 0);  // FUN_00408a00(&local_c,0)
        this->flags |= 4;  // Bit 2: property set
        propertyStruct = g_propertyTemplate2;  // DAT_0112dbd8
        flagsByte = 0;
        valuePtr = thresholdPtr;
        randomValue = setProperty(&propertyStruct, 0);  // FUN_00408a00(&local_c,0)
    }
    return randomValue & 0xffffff00;  // Return upper 24 bits of last random value
}