// FUNC_NAME: Entity::Entity
// Reconstructed C++ for constructor at 0x008af640
// Class: Entity (size 0x188 = 392 bytes)
// This constructor calls a base initialization and optionally sets up pool allocation.

class Entity {
public:
    __thiscall Entity(byte flags) {
        // Base initialization (likely base class constructor or static setup)
        baseInitialize();

        // If the lowest bit of 'flags' is set, perform custom memory management
        if (flags & 1) {
            // Sets up pool allocation for the object (size = 0x188)
            setupPoolAllocation(this, 0x188);
        }
    }

private:
    // Forward declarations for called functions
    void baseInitialize();
    void setupPoolAllocation(void* obj, unsigned int size);
};