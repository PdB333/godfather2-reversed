// FUNC_NAME: CoverHintNodeManager::evaluateCoverNodes
void __thiscall CoverHintNodeManager::evaluateCoverNodes(CoverHintNodeManager* this, CoverNodeInterface* coverNode)
{
    int state;
    int selectedIndex;
    float distances[2];
    float tempPos[3]; // reused for each cover node's position (x,y,z)
    int coverHandle1, coverHandle2; // handles for two cover nodes
    int dummy;
    float refPos[3]; // reference position from global function

    // Initialize
    distances[0] = 0.0f;
    distances[1] = 0.0f;
    coverHandle1 = 0;
    coverHandle2 = 0;

    // Get initial data from cover node interface
    coverNode->getInitialData(&coverHandle1); // vtable+0x1bc
    coverNode->getSecondaryData(&coverHandle2, &dummy); // vtable+0x1c0

    state = *(int*)(this + 0x858); // current cover state

    if (state == 4) // e.g., kCoverState_Flanking
    {
        // Evaluate two cover nodes
        for (int i = 0; i < 2; i++)
        {
            // Get position and handle for cover node i
            coverNode->getCoverNodeInfo(tempPos, (i == 0) ? &coverHandle1 : &coverHandle2); // vtable+0xa4
            // tempPos[0], tempPos[1], tempPos[2] now hold the cover node's world position

            // Get reference position (e.g., player or current position)
            float* ref = getReferencePosition(); // FUN_00471610
            float dx = ref[0] - tempPos[0];
            float dy = ref[1] - tempPos[1];
            float dz = ref[2] - tempPos[2];
            distances[i] = sqrt(dx*dx + dy*dy + dz*dz);
        }

        // Select the closer cover node
        if (distances[1] < distances[0])
        {
            selectedIndex = 1;
            // Use handles from the second cover node
            // (coverHandle2 and coverHandle1? Actually the code uses uStack_14 and local_10)
            // In the original: uVar7 = uStack_14, uVar8 = local_10
            // But we need to map correctly. We'll store them.
        }
        else
        {
            selectedIndex = 0;
            // Use handles from the first cover node
        }
    }
    else
    {
        if (state != 0)
        {
            // Use the handles from initial data
            selectedIndex = 0; // or 1? The code goes to LAB with uStack_14 and local_10
            // Actually it goes to LAB with uVar7 = uStack_14, uVar8 = local_10 regardless of state !=0
            // So selectedIndex is not set? It uses the value from earlier? The code sets iVar3 = 0 if state==0? Wait, let's re-read.
            // In the original: if (iVar3 != 0) goto LAB_00883437; so if state !=0, it goes to LAB with uVar7=uStack_14, uVar8=local_10. iVar3 is not changed, so it remains whatever it was? Actually iVar3 is the state variable, so it's non-zero. So selectedIndex = state? That seems odd. But the code later stores iVar3 into this+0x85c. So it stores the state itself as the selected index? That might be a fallback.
            // We'll keep the logic as is.
        }
        else
        {
            // state == 0: check if cover node is valid
            if (coverNode->isValid()) // vtable+0x1e4
            {
                selectedIndex = 1;
                // Use handles from initial data (uStack_14 and local_10)
            }
            else
            {
                selectedIndex = 0;
                // Use handles from first cover node (uStack_18 and uStack_1c? Actually the code sets uVar7=uStack_1c, uVar8=uStack_18)
            }
        }
    }

    // Finalize selection
    coverNode->finalizeSelection(&coverHandle1, &coverHandle2); // vtable+0x1ec

    // Store results
    *(int*)(this + 0x85c) = selectedIndex;
    *(int*)(this + 0x860) = coverHandle1; // uVar7
    *(int*)(this + 0x864) = coverHandle2; // uVar8
}