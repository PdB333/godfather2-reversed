// FUNC_NAME: AudioFadeManager::stopFade

// Function at 0x005262b0: This function stops any active audio crossfade prematurely.
// It snaps the current fade factors to the target volume (s_finalVolume) and resets all fade state.
// Called when a fade is interrupted or completed artificially.

// Static data members (offsets in .data section)
static float s_finalVolume = 1.0f; // constant from 0x00e2b1a4, likely 1.0f = full volume

// Global state for the fade manager (from .bss or .data)
static float s_fadeStartTime;       // _DAT_011251f4
static float s_fadeEndTime;         // _DAT_011251f8
static uint32_t s_fadeFlags;        // _DAT_011251f0 (bit flags)
static float s_currentVolumes[4];   // _DAT_01125200,01125204,01125208,0112520c
static float s_masterVolume;        // _DAT_0112521c
static float s_fadeDuration;        // _DAT_01125220
static int32_t s_padding1;          // _DAT_01125210
static int32_t s_padding2;          // _DAT_01125214
static int32_t s_padding3;          // _DAT_01125218

// Forward declaration of helper that actually sends the final fade command to the mixer
void applyFinalFade(float fromVolume, float toVolume, int32_t userParameter);

void AudioFadeManager::stopFade()
{
    if ((s_fadeDuration != 0.0f) && (0.0f < s_fadeStartTime) && (s_fadeEndTime != 0.0f))
    {
        // Compute the ratio to snap current fade factors to final volume
        float ratio = s_finalVolume / s_fadeDuration;

        // Scale each channel's current fade factor by the ratio
        s_currentVolumes[0] = ratio * s_currentVolumes[0];
        s_currentVolumes[1] = ratio * s_currentVolumes[1];
        s_currentVolumes[2] = ratio * s_currentVolumes[2];
        s_currentVolumes[3] = ratio * s_currentVolumes[3];

        // If the fade hasn't been flagged as already processed (bit 28 = 0x10000000),
        // apply the final fade with the saved start/end times and user param 0
        if ((s_fadeFlags & 0x10000000) == 0)
        {
            applyFinalFade(s_fadeStartTime, s_fadeEndTime, 0);
        }

        // Reset all fade state
        s_fadeStartTime = 0.0f;
        s_fadeEndTime = 0.0f;
        s_fadeFlags = 0;
        s_currentVolumes[3] = 0.0f;   // reset last channel to 0
        s_padding1 = 0;
        s_padding2 = 0;
        s_padding3 = 0;
        s_fadeDuration = 0.0f;

        // Set all volumes back to final (full) volume
        s_currentVolumes[0] = s_finalVolume;
        s_currentVolumes[1] = s_finalVolume;
        s_currentVolumes[2] = s_finalVolume;
        s_masterVolume = s_finalVolume;
    }
}