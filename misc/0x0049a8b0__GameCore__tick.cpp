// FUNC_NAME: GameCore::tick
// Function at 0x0049a8b0: Delegates to updateSystems() for per-frame subsystem updates
class GameCore {
public:
    // __thiscall - iterates subsystems each frame
    void tick() {
        updateSystems();
    }

private:
    void updateSystems(); // 0x0049a8d0 - actual update logic
};