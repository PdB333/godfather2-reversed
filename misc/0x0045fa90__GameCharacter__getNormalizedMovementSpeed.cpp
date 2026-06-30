// FUNC_NAME: GameCharacter::getNormalizedMovementSpeed
// Address: 0x0045fa90
// Role: Computes normalized movement speed (0.0 to 1.0) from physics component.
//        Returns 0.0 if physics component is missing.
// Offsets:
//   this+0x218 : m_pPhysics (CharacterPhysicsComponent*)
//   m_pPhysics+0x24 : m_currentSpeed (float)
//   m_pPhysics+0x130 : m_maxSpeed (float)
// Global: gMovementSpeedScale (float) at 0x011260b0

extern float gMovementSpeedScale;  // _DAT_011260b0

struct CharacterPhysicsComponent {
    float m_currentSpeed;   // +0x24
    float m_maxSpeed;       // +0x130
    // ... other members ...
};

class GameCharacter {
public:
    CharacterPhysicsComponent* m_pPhysics;  // +0x218

    __thiscall float getNormalizedMovementSpeed() {
        if (m_pPhysics != nullptr) {
            return m_pPhysics->m_currentSpeed / (m_pPhysics->m_maxSpeed * gMovementSpeedScale);
        }
        return 0.0f;
    }
};