// FUNC_NAME: TimeManager::incrementTick
class TimeManager {
public:
    // Increments the tick counter (short at offset +0x16) by one.
    // Called each frame or tick cycle.
    void __fastcall incrementTick() {
        // Offset +0x16: tickCount (short)
        short& tickCount = *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x16);
        tickCount = tickCount + 1;
    }
};