// FUNC_NAME: NPCCrewComponent::activate
// Address: 0x00564e50
// Role: Activates the NPC crew component, performing base initialization and virtual activation sequence

class NPCCrewComponent {
public:
    // Virtual table pointer at +0x20
    // Offset 0x238: activation flag (byte)

    bool activate() {
        // Base initialization (likely common component init)
        this->initializeComponent();

        // Check if vtable is valid
        if (this->vtable_0x20 != nullptr) {
            // Virtual function at vtable+8: canActivate() -> bool
            if (!this->vtable_0x20->canActivate()) {
                return false;
            }
        }

        // Virtual function at vtable+4: doActivate(int playerIndex)
        // Passing 0 suggests default player index
        this->vtable_0x20->doActivate(0);

        // Mark component as active
        this->activationFlag_0x238 = 1;
        return true;
    }

private:
    // Offset 0x00: base class members (unknown)
    int* vtable_0x20;           // +0x20: pointer to virtual function table
    // ... other members ...
    char activationFlag_0x238;  // +0x238: flag indicating active state (0/1)

    void initializeComponent(); // calls FUN_00565280
};