// FUNC_NAME: Sentient::handleRagdollActivation
class Sentient {
public:
    uint32_t flags;           // +0x34
    void* target;             // +0xd4
    int32_t currentState;     // +0x16c

    // External functions called
    void callDispatcher(void* frame);
    void startRagdollFall(int32_t param1, int32_t param2); // FUN_006b4e30
};

void __fastcall Sentient::handleRagdollActivation(Sentient* this) {
    // Bit 11 must be clear (e.g., not already in ragdoll)
    if ((this->flags >> 0xb) & 1) {
        return;
    }

    // Mark that raqdoll processing has started
    this->flags |= 0x2000000;

    // If there is no current action state, decide between two paths
    if (this->currentState == 0) {
        if (this->target != nullptr) {
            // Set bit 18 – likely entering a targeted ragdoll state
            this->flags |= 0x40000;

            // Build a call frame for the dispatcher
            struct {
                void** pTable;       // +0x00: PTR_LAB_00d5dbb0
                int32_t data;        // +0x04: DAT_0112a650
                char padding;        // +0x08: 0
                Sentient* self;      // +0x0c: this
            } frame;

            frame.pTable = (void**)0x00d5dbb0;
            frame.data   = 0x0112a650;
            frame.padding = 0;
            frame.self    = this;

            this->callDispatcher(&frame);
            return;
        }
        // No target: set bit 19 and start falling ragdoll
        this->flags |= 0x80000;
        this->startRagdollFall(1, 0);
    }
}