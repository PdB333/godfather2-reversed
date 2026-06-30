// FUN_00458740: InputControllerManager::setVibration
void __thiscall InputControllerManager::setVibration(float value)
{
    // EAX holds the controller slot index on entry (0–7)
    uint slotIndex = __eax;

    if (s_controllersEnabled != 0 && slotIndex < 8)
    {
        // Each slot structure is at offset 0x20 + slotIndex * 0x10 from 'this'.
        // Each slot's first member (+0x0) is a pointer to a per-controller state object.
        // That state object has a field at +0xc which must be non‑null to allow vibration.
        void* slotPtr = *(void**)((int)this + (slotIndex + 2) * 0x10);
        if (*(int*)((int)slotPtr + 0xc) != 0)
        {
            beginVibrationUpdate();                     // FUN_00c9eac0
            float clamped = value;
            if (value <= s_vibrationMin)
            {
                clamped = s_vibrationMin;
            }
            else
            {
                if (s_vibrationMax <= value)
                {
                    clamped = s_vibrationMax;
                }
            }
            setVibrationMotor(0, clamped);              // FUN_00ca4e90, motor index 0 (left/right?)
            endVibrationUpdate();                       // FUN_00c9eae0
        }
    }
}