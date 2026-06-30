// FUNC_NAME: CrewLeaderComponent::updateFollow
// Function at 0x594890: Updates follower state based on leader's position and flags.
// __thiscall: this in ESI, leader in EDI

class Entity; // forward declaration
class SimManager; // global manager type (DAT_012055a8)
extern SimManager* gSimManager; // global pointer

class CrewLeaderComponent {
public:
    // vtable offsets:
    // +0x10: void getPosition(float& x, float& y) // returns 2D position (x in ST(0), y on stack)
    // +0x5c: void setTransform(int param1, byte param2, int param3, int param4, int param5, int param6) // from leader's fields

    // layout (offsets in bytes):
    uint32_t flags;                     // +0x7c (this[0x1f])
    void* animPtr;                      // +0x20 (this[0x08])? Actually this[5] is at +0x14? Need to check: unaff_ESI[5] = this[5] => offset 0x14 (5*4=20). So at this+0x14.
    float m_targetPosX;                 // +0x90 (this[0x24])
    float m_targetPosY;                 // +0x98 (this[0x26])
    float m_squaredDistThreshold;       // +0xb0 (this[0x2c])
    int m_someInt1;                     // +0xb4 (this[0x2d])
    int m_someInt2;                     // +0xb8 (this[0x2e])

    void updateFollow(Entity* leader) {
        // Update flags based on leader's state bytes
        uint32_t uVar1;
        flags ^= ((uint32_t)(*(char*)(leader + 0x36) != 0) << 4 ^ flags) & 0x10;
        uVar1 = ((uint32_t)(*(char*)(leader + 0x37) != 0) << 7 ^ flags) & 0x80 ^ flags;
        flags = uVar1;
        flags = ((uint32_t)(*(char*)(leader + 0x35) != 0) << 12 ^ uVar1) & 0x1000 ^ uVar1;

        // Set threshold and other data from leader
        m_squaredDistThreshold = *(float*)(leader + 0x2c) * *(float*)(leader + 0x2c);
        m_someInt1 = *(int*)(leader + 0x30);
        m_someInt2 = *(int*)(leader + 0x28);

        // Check animation pointer and call appropriate manager function
        if (animPtr != nullptr && (*(byte*)animPtr & 4) != 0) {
            // animation has bit 2 set -> call vtable+0x18
            (*(void(**)(void))(*(int*)gSimManager + 0x18))();
        } else {
            (*(void(**)(void))(*(int*)gSimManager + 0x10))();
        }

        // Get current position
        float currentX;
        float currentY;
        // Use a buffer on stack; virtual function fills X in ST(0) and Y on stack
        // Using a 8-byte buffer to match decompilation
        struct { float x; float y; } position;
        (*(void(**)(void*))(*(int*)this + 0x10))(&position);
        currentX = position.x;  // unaff_EBX
        currentY = position.y;  // fStack_28

        // Compute squared distance to target position
        float dx = currentX - m_targetPosX;
        float dy = currentY - m_targetPosY;
        float distSq = dx*dx + dy*dy;

        // If distance exceeds threshold (and not exactly equal), teleport follower to leader
        if (m_squaredDistThreshold <= distSq && distSq != m_squaredDistThreshold) {
            (*(void(**)(int, int, int, int, int, int))(*(int*)this + 0x5c))(
                *(int*)(leader + 0x10),
                *(byte*)(leader + 0x34),
                *(int*)(leader + 0x18),
                *(int*)(leader + 0x1c),
                *(int*)(leader + 0x20),
                *(int*)(leader + 0x24)
            );
        }

        // Set flag bit 5 (0x20)
        flags |= 0x20;
    }
};