// FUNC_NAME: WanderState::computeTargetPosition

void __thiscall WanderState::computeTargetPosition(WanderState *this, float *outX, float *outY)
{
    // Structure offsets:
    // +0x00: int state
    // +0x04: char counter1 (first byte of second int)
    // +0x05: char counter2
    // +0x28 (10 int): int unknown (always cleared to 0)
    
    // Global constants (addresses from .data):
    // DAT_00d5f520 = kBaseX1
    // DAT_00d5c454 = kBaseX2
    // DAT_00d5eee4 = kDefaultX
    // DAT_00e445fc = kDefaultY
    // DAT_00e44590 = kScale1 (random multiplier)
    // DAT_00d58cbc = kScale2 (for state 2 X)
    // DAT_00d5779c = kScale3 (for state 2 Y)
    // _DAT_00d5efe4 = kBaseY
    // DAT_00d5f414 = kScale4 (for state 3 X)

    int randomResult;
    float randFloat;

    switch (this->state) {
    case 0: // Init: move to base position and go to state 5
        this->unknown = 0;
        *outX = kBaseX1;
        *outY = 0.0f;
        this->state = 5;
        return;

    case 2: // Random wander (first variant)
        this->unknown = 0;
        randomResult = randomCheck(3);
        this->state = (randomResult != 0) + 2; // state becomes 2 or 3
        // Compute random target position
        randFloat = (float)rand() * kScale1 * kScale2 + kBaseX2;
        *outX = randFloat;
        randFloat = (float)rand() * kScale1 * kScale3 + kBaseY;
        *outY = randFloat;
        break;

    case 3: // Random wander (second variant) – uses different X scale
        this->unknown = 0;
        randomResult = randomCheck(3);
        this->state = (randomResult != 0) + 2; // same transition as above
        randFloat = (float)rand() * kScale1 * kScale4 + kBaseX2;
        *outX = randFloat;
        randFloat = (float)rand() * kScale1 * kScale3 + kBaseY;
        *outY = randFloat;
        break;

    case 4: // Set up a new wander cycle: choose direction and counter
        this->counter1 = (char)randomCheck(4) + 1; // random countdown
        this->unknown = 0;
        randomResult = randomCheck(2);
        this->state = 3 - (uint)(randomResult != 0); // 2 or 3
        *outX = 0.0f;
        *outY = 0.0f;
        return;

    case 5: // Begin a hold or pause phase
        this->counter1 = 0;
        this->counter2 = (char)randomCheck(6) + 3; // random pause duration
        this->unknown = 0;
        this->state = 4;
        *outX = 0.0f;
        *outY = 0.0f;
        return;

    case 6: // End of pause: either continue to state 7 or loop back to 4
        this->unknown = 0;
        *outX = kBaseX2;
        *outY = 0.0f;
        this->counter2--;
        this->state = (this->counter2 != 0) ? 4 : 7; // if counter not zero, go to 4 else 7
        return;

    case 7: // Return to base after pause
        this->unknown = 0;
        *outX = kBaseX1;
        *outY = 0.0f;
        this->state = 5;
        return;

    default: // Fallback target (used when state is not handled)
        *outX = kDefaultX;
        *outY = kDefaultY;
        return;
    }

    // Common decrement and state transition for cases 2 and 3
    this->counter1--;
    if (this->counter1 == 0) {
        this->state = 6;
    }
    return;
}