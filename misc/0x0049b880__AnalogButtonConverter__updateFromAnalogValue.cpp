// FUNC_NAME: AnalogButtonConverter::updateFromAnalogValue

#include <cstdint>

// Forward declarations for external functions
int getRawAnalogInput(int axis);  // FUN_00b93230
void sendInputEvent(bool isPressed); // FUN_0049b940

class AnalogButtonConverter {
public:
    void updateFromAnalogValue();

private:
    // member offsets (relative to this)
    // +0x114: flag for positive direction (threshold crossed from center)
    bool m_bPositiveFlag;
    // +0x115: flag for negative direction
    bool m_bNegativeFlag;
    // +0x118: previous raw analog value (used for edge detection)
    int m_nPreviousRawValue;
};

void AnalogButtonConverter::updateFromAnalogValue() {
    // Clear old press flags if they were set, and send release events
    if (m_bPositiveFlag) {
        sendInputEvent(false); // release
        m_bPositiveFlag = false;
    }
    if (m_bNegativeFlag) {
        sendInputEvent(false); // release
        m_bNegativeFlag = false;
    }

    // Get current raw analog value (axis index 4, e.g., right stick X or left trigger)
    int newRawValue = getRawAnalogInput(4);

    // Detect positive edge: new value exceeds previous and is above a threshold (> -1)
    if (m_nPreviousRawValue < newRawValue && newRawValue > -1) {
        sendInputEvent(true); // press
        m_bPositiveFlag = true;
    } else {
        // Detect negative edge: new value is less than previous and below a threshold (<= -2)
        if (m_nPreviousRawValue > newRawValue && newRawValue <= -2) {
            sendInputEvent(true); // press
            m_bNegativeFlag = true;
        }
    }

    // Store current raw value for next frame
    m_nPreviousRawValue = newRawValue;

    // If raw value is exactly -1 (center dead zone), force previous to -1 as well
    if (newRawValue == -1) {
        m_nPreviousRawValue = -1;
    }
}