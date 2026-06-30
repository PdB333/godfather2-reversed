// FUNC_NAME: GameObject::getScaledValue

extern int* GetGlobalSettings(); // address: 0x007079c0, returns pointer to global game settings structure
extern const float kRoundBias;   // from DAT_00e44578, used for negative rounding (likely 0.5f or -0.5f)

class GameObject {
public:
    int m_value; // +0x330: integer field to be scaled (e.g., health, speed, score)

    // Applies a global multiplier from the game settings to the member value
    // and returns the rounded result.
    int getScaledValue() {
        int original = m_value;
        int* settings = GetGlobalSettings();
        if (settings != nullptr) {
            float fVal = static_cast<float>(original);
            if (original < 0) {
                fVal += kRoundBias;
            }
            // +0x1de8: float multiplier in the global settings structure
            float multiplier = *reinterpret_cast<float*>(reinterpret_cast<char*>(settings) + 0x1de8);
            // Round to nearest integer (approximating the original ROUND macro)
            int result = static_cast<int>(fVal * multiplier + 0.5f);
            return result;
        }
        return original;
    }
};