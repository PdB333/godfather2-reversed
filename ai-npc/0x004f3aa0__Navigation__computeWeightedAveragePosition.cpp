// FUNC_NAME: Navigation::computeWeightedAveragePosition
void Navigation::computeWeightedAveragePosition(int unused, NodeProcessor* processor, Vector3& out)
{
    // this+0x08: pointer to head of node linked list
    int nodePtr = *(int*)(this + 0x08);
    // local accumulation of weighted sum (x, y, z)
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumZ = 0.0f;
    // iterate through linked list, each node has next at +0x34
    while (nodePtr != 0) {
        // extract vector from node and accumulate weighted sum using processor
        FUN_004f3480(processor, m_weightPtr, &Vector3(sumX, sumY, sumZ));
        nodePtr = *(int*)(nodePtr + 0x34); // next node
    }
    // global constant (e.g., 1.0f or scale factor) divided by total weight
    float invWeight = DAT_00e2b1a4 / (*m_weightPtr);
    out.x = invWeight * sumX;
    out.y = invWeight * sumY;
    out.z = invWeight * sumZ;
    // w component set to 0
    out.w = 0.0f;
}