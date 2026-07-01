// FUNC_NAME: GameTime::add
// Function address: 0x00835bf0
// Role: Adds two GameTime objects (representing time of day with hours, minutes, seconds, modulo 24h).
// Structure field offsets are based on the decompiled arithmetic.
class GameTime {
public:
    int unknown0;  // +0x00
    int unknown1;  // +0x04
    int unknown2;  // +0x08
    int hours;     // +0x0c
    int minutes;   // +0x10
    int seconds;   // +0x14
};

GameTime* GameTime::add(GameTime* out, const GameTime* a, const GameTime* b) {
    int totalSeconds = a->seconds + b->seconds;
    int totalMinutes = a->minutes + b->minutes + totalSeconds / 60;
    int totalHours = a->hours + b->hours + totalMinutes / 60;

    out->unknown0 = 0;
    out->unknown1 = 0;
    out->unknown2 = 0;
    out->seconds = totalSeconds % 60;
    out->minutes = totalMinutes % 60;
    out->hours = totalHours % 24;
    return out;
}