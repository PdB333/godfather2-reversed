// FUNC_NAME: Transform::operatorAssign
// Function at 0x00820980: Copy assignment for Transform class (world/local matrices, linked list node, double arrays)
// This performs deep copy of a transform node, including intrusive list node pointer adjustment.

class Transform {
public:
    // Offsets (relative to this):
    // +0x4C: 5 doubles (likely position/orientation? e.g., m_position[3] + m_quaternion[4]? but 5 doubles is unusual)
    double m_doublesA[5]; // 0x4C (40 bytes)
    // +0x80: 3x4 affine matrix (12 floats) - world matrix?
    float m_worldMatrix[3][4]; // 0x80
    // +0xB0: Intrusive linked list node pointer (next pointer in a singly/doubly linked list)
    Transform* m_next; // 0xB0
    int m_refCount; // 0xB4? Actually at +0xB4 there is a pointer stored from source's node
    // +0xC0: 4x4 matrix (16 floats) - local matrix?
    float m_localMatrix[4][4]; // 0xC0
    // +0x100: 4 doubles
    double m_doublesB[4]; // 0x100 (32 bytes)
    // +0x120: byte (maybe a flag)
    char m_flag; // 0x120

    // Copy assignment operator (this is the function at 0x00820980)
    void operatorAssign(const Transform& source) {
        // Copy world matrix (12 floats at 0x80-0xAB)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                m_worldMatrix[i][j] = source.m_worldMatrix[i][j];
            }
        }

        // Handle intrusive list node at 0xB0.
        // If this node is part of a linked list, we need to remove it from its current list
        // and reattach to the source's list node.
        // The code checks if the next pointers differ.
        if (m_next != source.m_next) {
            // If current m_next is non-null, detach from current list (call FUN_004daf90 which likely detaches)
            if (m_next) {
                FUN_004daf90(this); // Detach this node from its current list
            }
            m_next = source.m_next;
            if (m_next) {
                // Set m_next's previous pointer (stored at +4 of the node) to point back to this.
                // This is typical for doubly linked list: each node has a pointer to its owner.
                *reinterpret_cast<Transform**>(reinterpret_cast<char*>(m_next) + 4) = this;
            }
        }

        // Copy 5 doubles at 0x4C-0x6C
        m_doublesA[0] = source.m_doublesA[0];
        m_doublesA[1] = source.m_doublesA[1];
        m_doublesA[2] = source.m_doublesA[2];
        m_doublesA[3] = source.m_doublesA[3];
        m_doublesA[4] = source.m_doublesA[4];

        // Copy local matrix (16 floats at 0xC0-0xFF)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_localMatrix[i][j] = source.m_localMatrix[i][j];
            }
        }

        // Copy 4 doubles at 0x100-0x118
        m_doublesB[0] = source.m_doublesB[0];
        m_doublesB[1] = source.m_doublesB[1];
        m_doublesB[2] = source.m_doublesB[2];
        m_doublesB[3] = source.m_doublesB[3];

        // Copy flag byte at 0x120
        m_flag = source.m_flag;
    }

private:
    // FUN_004daf90: Detach node from list (likely a static function or member of list manager)
    void FUN_004daf90(void* node); // Placeholder
};

// Note: The actual class may have additional padding/members, but this captures the essential layout.