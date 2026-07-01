// FUN_NAME: BlendNode::accumulateWeight
// Function address: 0x008d8010
// Role: Accumulates a delta into a stored counter and applies a scaled version of that delta to a blending operation.
// Struct layout (pointed to by getData(0)):
//   +0x00: int accumulatedValue (added delta)
//   +0x10: int scaleFactor (cast to float for multiplication with delta, used in applyBlend)

class BlendNode {
public:
    // Assumed internal helper: returns a pointer to a sub-struct containing blend state
    int* getData(int index);
    // Assumed internal helper: applies a scaled blend value to some target
    void applyBlend(int someObject, float scaledDelta);
};

void __thiscall BlendNode::accumulateWeight(int someObject, int delta) {
    int* data = this->getData(0);      // Retrieve base struct pointer
    *data += delta;                    // Accumulate delta (e.g., elapsed time or weight)
    this->applyBlend(someObject, 
                     static_cast<float>(delta) * static_cast<float>(data[4])); // Scale delta by stored factor and pass to blending
}