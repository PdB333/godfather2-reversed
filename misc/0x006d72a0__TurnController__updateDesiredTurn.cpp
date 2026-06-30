// FUNC_NAME: TurnController::updateDesiredTurn

// Constants (likely defined elsewhere)
extern const float TURN_SCALE_FACTOR; // DAT_00e445c8 – turn rate scaling
extern const float TWO_PI;            // DAT_00d5f4b4 – 2*PI (6.283185)

// Forward declaration of helper function (probably computes angle difference)
float getAngleDifference(void* input); // FUN_006d7210

struct TurnController {
    // +0x000: vtable pointer
    // ...
    uint32_t turnState1;   // +0x224 – 0 = idle, 1 = turning left, 2 = turning right
    uint32_t turnState2;   // +0x228 – 0 = inactive, 1 = active
    float someAngle;       // +0x234 – current heading or target angle?
    float turnAmount;      // +0x24c – computed turn magnitude
    // ...
};

void __thiscall TurnController::updateDesiredTurn(TurnController* this, void* input) {
    // Only start a turn if we're not already turning
    if (this->turnState1 == 0 && this->turnState2 == 0) {
        float rawAngle = getAngleDifference(input);
        float processedAngle = rawAngle;

        // Normalize angle to [0, TWO_PI) if needed
        if (rawAngle < 0.0f) {
            processedAngle = rawAngle + TWO_PI; // clamp to positive range
        }
        // Scale the turn amount by the turn rate factor
        this->turnAmount = processedAngle * TURN_SCALE_FACTOR;

        // Compare scaled angle with stored angle to decide direction
        float storedAngle = this->someAngle;
        if (storedAngle < 0.0f) {
            storedAngle += TWO_PI;
        }

        // Determine turn direction based on whether computed turn is less than stored turn
        if (processedAngle * TURN_SCALE_FACTOR < storedAngle * TURN_SCALE_FACTOR) {
            // Turn right (direction 2)
            this->turnState1 = 2;
            this->turnState2 = 1;
        } else {
            // Turn left (direction 1)
            this->turnState1 = 1;
            this->turnState2 = 1;
        }
    }
}