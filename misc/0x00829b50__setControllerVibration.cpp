// FUNC_NAME: setControllerVibration
struct VibrationCommand {
    int motorType;   // 2 = left motor?
    int duration;    // 0x10 = 16 ms?
    int flags;       // 0 = default
};

class InputDeviceManager {
public:
    virtual void __thiscall sendControllerCommand(int controllerIndex, VibrationCommand* cmd) = 0;
};

InputDeviceManager* __cdecl GetInputDeviceManager();

void __cdecl setControllerVibration(int controllerIndex) {
    InputDeviceManager* mgr = GetInputDeviceManager();
    VibrationCommand cmd;
    cmd.motorType = 2;
    cmd.duration = 0x10;
    cmd.flags = 0;
    mgr->sendControllerCommand(controllerIndex, &cmd);
}