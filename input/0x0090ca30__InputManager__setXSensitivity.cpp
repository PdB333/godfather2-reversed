// FUNC_NAME: InputManager::setXSensitivity
// Reconstructed from 0x0090ca30
// Sets the X-axis sensitivity for controller input, clamping to bounds and persisting to config.

#pragma once

// Global sensitivity bounds (from .rdata)
extern const float gMinXSensitivity;  // 0x00d5ef88
extern const float gMaxXSensitivity;  // 0x00d5eee4
// Shared sensitivity value (0x00e50fb8)
extern float gXSensitivity;

class InputManager {
public:
    // Sets the X sensitivity, applies clamping, stores locally, and writes to config.
    // +0x20: float m_xSensitivity
    void setXSensitivity(float sensitivity) {
        // Clamp within allowed range [gMinXSensitivity, gMaxXSensitivity]
        if (sensitivity < gMinXSensitivity || sensitivity > gMaxXSensitivity) {
            sensitivity = (sensitivity < gMinXSensitivity) ? gMinXSensitivity : gMaxXSensitivity;
        }

        // Update global and instance values
        gXSensitivity = sensitivity;
        m_xSensitivity = sensitivity;

        // Persist to config system (FUN_0069c010)
        writeConfigFloat("Controls.XSensitivity", sensitivity);
    }

private:
    float m_xSensitivity; // +0x20

    // Stub for config write (actual implementation at 0x0069c010)
    void writeConfigFloat(const char* key, float value);
};