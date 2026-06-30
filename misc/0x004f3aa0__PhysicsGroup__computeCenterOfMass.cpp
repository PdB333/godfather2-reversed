// FUNC_NAME: PhysicsGroup::computeCenterOfMass

struct PhysicsNode {
    float nodeData;        // +0x00 (possibly position/weight)
    char pad[0x30];        // +0x04 to +0x33
    PhysicsNode* next;     // +0x34
};

class PhysicsGroup {
public:
    float totalWeight;             // +0x00
    char pad[4];                   // +0x04
    PhysicsNode* headNode;         // +0x08
    char pad2[0x2C];              // +0x0C to +0x37

    void accumulateVector(int context, float* outVec); // FUN_004f3480

    void computeCenterOfMass(int context, float* outVec) {
        float accum[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        PhysicsNode* node = this->headNode;

        while (node != nullptr) {
            accumulateVector(context, accum);
            node = node->next;
        }

        float scale = g_scaleFactor / this->totalWeight;
        outVec[0] = scale * accum[0];
        outVec[1] = scale * accum[1];
        outVec[2] = scale * accum[2];
        outVec[3] = scale * 0.0f; // always zero
    }
};

extern float g_scaleFactor; // DAT_00e2b1a4