// FUNC_NAME: CharacterState::setState
// Address: 0x007222b0
// Sets the state and marks a dirty flag if the state actually changes.

struct CharacterState {
    char state;         // +0x04
    // ... other members between +0x05 and +0x27
    uint8_t dirtyFlag;  // +0x28
};

void __thiscall CharacterState::setState(char newState)
{
    if (newState != this->state) {
        this->dirtyFlag = 1;
        this->state = newState;
    }
}