// FUNC_NAME: Player::isTargetInRange
// Function address: 0x007f47c0
// This function checks if the distance to the target (obtained from the perception component)
// is within a maximum range stored in the Player object.

class PerceptionObject {
public:
    virtual float getDistance() = 0; // vtable index 12 (0x30/4)
};

class Player {
private:
    // +0x000: ... (other members)
    char pad_0x5F4[0x5F4];
    PerceptionObject* m_pPerception; // +0x5F4
    // +0x5F8: ... (other members)
    char pad_0x1D84[0x1D84 - 0x5F8];
    float m_fMaxRange; // +0x1D84
    // +0x1D88: ...

public:
    bool isTargetInRange();
};

bool Player::isTargetInRange()
{
    float distance = m_pPerception->getDistance();
    return distance <= m_fMaxRange;
}