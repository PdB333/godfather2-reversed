// FUNC_NAME: SceneNode::scaleSelfAndChildren
// Address: 0x0049eb50
// Role: Recursively scales the node's scale vector and all children's scale vectors by a factor.
// For children with type 2 (0x02), also scales an array of vectors (3 components only, preserving the fourth component).
// Structure layout:
//   SceneNode: +0x10 float m_scale[4]; +0x34 int m_childCount; +0x50 ChildNode* m_children;
//   ChildNode: +0x04 char m_type; +0x10 float m_scale[4]; +0x20 float* m_extraData; (size 0xB0)

void __thiscall SceneNode::scaleSelfAndChildren(float factor)
{
    int childCount;
    ChildNode* childArray;
    ChildNode* childEnd;
    ChildNode* child;
    float* pData;
    float* pDataEnd;
    float savedW;

    if (this != nullptr)
    {
        // Scale this node's own scale vector
        this->m_scale[0] *= factor;
        this->m_scale[1] *= factor;
        this->m_scale[2] *= factor;
        this->m_scale[3] *= factor;

        childArray = this->m_children;                   // +0x50
        childCount = this->m_childCount;                 // +0x34
        childEnd = childArray + childCount * (0xB0 / sizeof(ChildNode)); // stride 0xB0

        for (child = childArray; child != childEnd; child = (ChildNode*)((uint8_t*)child + 0xB0))
        {
            // Scale child's scale vector
            child->m_scale[0] *= factor;
            child->m_scale[1] *= factor;
            child->m_scale[2] *= factor;
            child->m_scale[3] *= factor;

            if (child->m_type == 0x02)
            {
                // Scale an array of 3-component vectors (4 floats each), preserving the fourth component (W)
                // The array is pointed to by +0x20, and contains 8 floats (two 4-float vectors)
                pData = child->m_extraData;               // +0x20
                pDataEnd = pData + 0x20 / sizeof(float);  // 8 floats

                for (; pData != pDataEnd; pData += 4)
                {
                    savedW = pData[3];
                    pData[0] *= factor;
                    pData[1] *= factor;
                    pData[2] *= factor;
                    pData[3] *= factor;
                    pData[3] = savedW;  // restore original W
                }
            }
        }
    }
}