// FUNC_NAME: Time::copyFrom
void __thiscall Time::copyFrom(uint32_t *this, Time *other) {
    uint32_t tempBuffer[6]; // 24 bytes
    uint32_t *dest = (uint32_t *)((uint8_t *)this + 0x34);
    uint32_t *src = (uint32_t *)FUN_00835c80(tempBuffer, dest, other); // unknown helper, returns pointer to source data
    if (dest != src) {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3]; // hours
        dest[4] = src[4]; // minutes
        dest[5] = src[5]; // seconds
    }
    // Compute total seconds as float: (hours * 60 + minutes) * 60 + seconds
    int hours   = (int)dest[3]; // +0x40
    int minutes = (int)dest[4]; // +0x44
    int seconds = (int)dest[5]; // +0x48
    int totalSec = seconds + (minutes + hours * 60) * 60;
    float totalFloat = (float)totalSec;
    if (totalSec < 0) {
        totalFloat += DAT_00e44578; // likely a rounding adjustment constant
    }
    *(float *)((uint8_t *)this + 0x54) = totalFloat;
}