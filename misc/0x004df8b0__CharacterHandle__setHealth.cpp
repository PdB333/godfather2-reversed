// FUNC_NAME: CharacterHandle::setHealth
// Function address: 0x004df8b0
// Sets the health field (offset +0x84) of the character pointed to by the handle, with null check.

struct Character {
    // ... other fields ...
    int health; // offset 0x84
};

class CharacterHandle {
public:
    Character* m_character; // offset 0x00, pointer to the actual character object

    void __thiscall setHealth(int value) {
        if (m_character != nullptr) {
            m_character->health = value;
        }
    }
};