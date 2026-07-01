// FUNC_NAME: ControllerManager::applyVibration
// Address: 0x00829bd0
// Wrapper function that calls the first virtual method on ControllerManager singleton,
// passing a controller object and a vibration data struct (motor=2, duration=0x10, strength=0).
void ApplyVibration(void* controller) {
    // Get singleton instance via FUN_009c8f80 (likely ControllerManager::getInstance())
    void* manager = reinterpret_cast<void*>(FUN_009c8f80());

    // Vibration parameters struct (12 bytes)
    struct VibrationData {
        int motor;     // +0x00
        int duration;  // +0x04
        int strength;  // +0x08
    };
    VibrationData data;
    data.motor = 2;
    data.duration = 0x10;
    data.strength = 0;

    // Call the first virtual method on the manager (index 0 of vtable)
    // The vtable pointer is at offset 0 of the manager object.
    typedef void (*VibrationFunc)(void*, VibrationData*);
    VibrationFunc func = reinterpret_cast<VibrationFunc>(*reinterpret_cast<void**>(manager));
    func(controller, &data);
}