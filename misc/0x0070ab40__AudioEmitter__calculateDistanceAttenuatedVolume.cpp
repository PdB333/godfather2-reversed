// FUNC_NAME: AudioEmitter::calculateDistanceAttenuatedVolume

//
// Function: 0x0070ab40
// Role: Calculates the distance-based volume gain for an audio emitter.
// The emitter stores:
//   +0x2e4: minDist (distance below which volume is full)
//   +0x2e8: maxDist (distance at which volume reaches zero)
//   +0x2ec: baseVolume (multiplier applied after attenuation)
//   +0x338, +0x33c, +0x340: emitter position (x, y, z)
// Listener position is obtained from a global manager (FUN_00471610 -> AudioManager::getInstance())
//   manager+0x30: packed 64-bit float2 (listener x, y) – low = x, high = y
//   manager+0x38: listener z
//
// Attenuation curve uses two global constants:
//   g_maxAttenuationT   (_DAT_00d5780c)  – maximum t value (likely 1.0f)
//   g_attenuationCurve  (DAT_00d5eee4)   – curve parameter (probably 2.0f)
//

// Forward declarations (assumed)
class AudioManager;
AudioManager* __fastcall GetAudioManager();  // FUN_00471610

// Global constants (from data)
extern float g_maxAttenuationT;   // _DAT_00d5780c
extern float g_attenuationCurve;  // DAT_00d5eee4

class AudioEmitter
{
public:
    float minDist;          // +0x2e4
    float maxDist;          // +0x2e8
    float baseVolume;       // +0x2ec
    // ... other fields ...
    // Position stored as three consecutive floats at +0x338 (x), +0x33c (y), +0x340 (z)
    float& x() { return *reinterpret_cast<float*>(this + 0x338); }
    float& y() { return *reinterpret_cast<float*>(this + 0x33c); }
    float& z() { return *reinterpret_cast<float*>(this + 0x340); }

    // __thiscall
    float calculateVolume()
    {
        // Get listener position
        AudioManager* mgr = GetAudioManager();
        // Packed listener x,y from 64-bit value
        uint64_t packedListenerXY = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(mgr) + 0x30);
        float listenerX = reinterpret_cast<float*>(&packedListenerXY)[0]; // low word
        float listenerY = reinterpret_cast<float*>(&packedListenerXY)[1]; // high word
        float listenerZ = *reinterpret_cast<float*>(reinterpret_cast<char*>(mgr) + 0x38);

        // Delta vector
        float dx = listenerX - x();
        float dy = listenerY - y();
        float dz = listenerZ - z();

        float distance = sqrtf(dx*dx + dy*dy + dz*dz);

        float volume = baseVolume;
        if (distance > minDist)
        {
            float range = maxDist - minDist;
            float t = (distance - minDist) / range;
            // Clamp t to [0, g_maxAttenuationT]
            if (t < 0.0f)
                t = 0.0f;
            else if (t > g_maxAttenuationT)
                t = g_maxAttenuationT;

            // Quadratic attenuation: (1-t)*curve - (1-t)^2
            float oneMinusT = g_maxAttenuationT - t;
            volume = oneMinusT * g_attenuationCurve - oneMinusT * oneMinusT;
            volume *= baseVolume;
        }

        return volume;
    }
};