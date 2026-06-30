// FUNC_NAME: PacketQueueNode::popNext
int __thiscall PacketQueueNode::popNext(PacketQueueNode*& outNext, int& outData) {
    // struct PacketQueueNode {
    //     PacketQueueNode* next; // +0x00
    //     int unknown;           // +0x04 (not used here)
    //     int data;              // +0x08
    // };
    outNext = this->next; // param_2 = param_1[0]
    if (outNext != nullptr) {
        outData = this->data; // param_3 = param_1[2]
        // Return the data with its low byte forced to 1 (indicating success)
        return (outData & 0xFFFFFF00) | 1; // CONCAT31((int3)(data>>8), 1)
    } else {
        outData = 0;
        return 0;
    }
}