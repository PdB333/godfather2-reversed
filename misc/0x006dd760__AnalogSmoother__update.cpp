// FUNC_NAME: AnalogSmoother::update

class AnalogSmoother {
public:
    void __thiscall update();

    // Fields (offsets relative to this):
    // +0x2b4: float m_inputMagnitude;
    // +0x2d0: SomeEntity* m_pOwner; // pointer to object with flag at +0x8e3
    // +0x11c: float m_minClamp;
    // +0x13c: float m_maxClamp;
    // +0x210: float m_overrideValue;
    // +0xe8: float m_smoothingFactor; // alpha (0-1)
    // +0x60: float m_speed; // rate/divisor
    // +0x240: float m_accumulatedValue;
    // +0x284: float m_currentOutput;
    // +0xf0: float m_decayFactor; // friction (0-1)
    // +0x23c: float m_currentVelocity;
    // +0x244: float m_currentAcceleration;
};

// Global symbols from game
extern float _DAT_00d5780c; // likely 1.0f (or 0.0f)
extern float DAT_00e44598; // some threshold (e.g., 0.001f)

// Global helper: gets time manager
extern void* __fastcall FUN_00471610(); // returns pointer to TimeManager

// Interpolation helper: float smoothInterpolation(float current, float target, float alpha)
extern float __fastcall FUN_006c89b0(float current, float target, float alpha);

void __thiscall AnalogSmoother::update()
{
    float baseInput = this->m_inputMagnitude;
    void* timeMgr = FUN_00471610();
    
    // timeMgr structure:
    // +0x30: float timeDelta (low part) -- actually two floats stored as 8 bytes
    // +0x34: float timeHigh? (high part) -- used as additive term
    // +0x38: float something (another time or velocity)
    float timeDeltaLow = *(float*)((int)timeMgr + 0x30);
    float timeDeltaHigh = *(float*)((int)timeMgr + 0x34); // high 32 bits unpacked
    float additionalValue = *(float*)((int)timeMgr + 0x38);
    
    bool flagIsSet = (*(byte*)(this->m_pOwner + 0x8e3) & 1) != 0;
    
    if (!flagIsSet) {
        // Interpolate between bounds
        baseInput = (this->m_minClamp - this->m_maxClamp) * baseInput + this->m_maxClamp;
    } else {
        // Override with direct value
        baseInput = this->m_overrideValue;
    }
    
    float blendFactor = this->m_smoothingFactor;
    if (flagIsSet) {
        blendFactor = _DAT_00d5780c; // likely 0.0 or 1.0 (disable smoothing)
    }
    
    // Compute velocity to target
    float velocity = 0.0f;
    if (DAT_00e44598 < this->m_speed) {
        float target = baseInput + timeDeltaHigh;
        velocity = (target - this->m_accumulatedValue) / this->m_speed;
    }
    
    // Spring interpolation on current output
    float newOutput = FUN_006c89b0(this->m_currentOutput, velocity, blendFactor);
    this->m_currentOutput = (float)newOutput;
    
    // Apply decay if within range
    float decay = this->m_decayFactor;
    float decayAmount = 0.0f;
    if (decay > 0.0f && decay < _DAT_00d5780c) {
        decayAmount = decay;
    }
    this->m_currentOutput = this->m_currentOutput - this->m_currentOutput * decayAmount;
    
    // Smooth velocity towards timeDeltaLow
    float newVelocity = FUN_006c89b0(this->m_currentVelocity, timeDeltaLow, 1.0f);
    this->m_currentVelocity = (float)newVelocity;
    
    // Update accumulated value based on smoothed output and speed
    this->m_accumulatedValue = this->m_currentOutput * this->m_speed + this->m_accumulatedValue;
    
    // Smooth acceleration towards additionalValue
    float newAcceleration = FUN_006c89b0(this->m_currentAcceleration, additionalValue, 1.0f);
    this->m_currentAcceleration = (float)newAcceleration;
}