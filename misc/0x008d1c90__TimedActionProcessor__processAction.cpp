// FUNC_NAME: TimedActionProcessor::processAction
void __thiscall TimedActionProcessor::processAction(TimedActionProcessor* this)
{
    // Compare global current time with the action's duration (offset +0x14)
    if (gCurrentTime < *(float*)((uintptr_t)this + 0x14)) {
        // Perform four repeated sub-actions (e.g., update four channels or slots)
        doSubAction();
        doSubAction();
        doSubAction();
        doSubAction();
        // Set a scaled value: global constant divided by the duration
        setScaledValue(gSomeConstant / *(float*)((uintptr_t)this + 0x14));
    }
}