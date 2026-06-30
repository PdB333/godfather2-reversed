// FUNC_NAME: CollisionGrid::evaluateInteractions
int CollisionGrid::evaluateInteractions(void)
{
    // Global arrays: g_outerCellIds[4] at 0x00e2ac50, g_innerCellIds[6] at 0x00e2ac28
    // Each iteration processes a pair (outerCellId, innerCellId)
    int bestPriority = 4; // starting priority threshold
    uint outerByteOffset = 0;

    do {
        uint outerCellId = *(uint *)((int)&g_outerCellIds + outerByteOffset);
        uint innerByteOffset = 0;

        do {
            uint innerCellId = *(uint *)((int)&g_innerCellIds + innerByteOffset);
            InteractionRecord rec; // 20-byte struct: outerId, innerId, data1, data2, data3
            rec.outerId = outerCellId;
            rec.innerId = innerCellId;
            rec.data1 = 0;
            rec.data2 = 0;
            rec.data3 = 0;

            int interactionResult = this->checkInteraction(&rec); // FUN_0060ed60
            if (interactionResult == 9) {
                // Special interaction code 9 -> max priority interaction
                if ((*(char *)((int)this + 0x0c) == '\0') && (rec.data2 == 0)) {
                    // Object inactive and no secondary data -> set priority to 5 if higher
                    if (bestPriority < 6) {
                        bestPriority = 5;
                    }
                } else {
                    int subResult = this->getBestInteractionCode(); // FUN_0060ecb0
                    if (subResult == 9) {
                        // Highest sub-priority; need to allocate a new interaction record
                        int currentCount = this->interactionCount; // this+0x144
                        int maxCount = this->interactionCapacity;  // this+0x148
                        if (currentCount == maxCount) {
                            if (maxCount == 0) {
                                maxCount = 1;
                            } else {
                                maxCount *= 2;
                            }
                            this->resizeInteractionArray(&this->interactionList, maxCount); // FUN_0060fcb0
                        }
                        // Calculate address of next free slot (each record 20 bytes)
                        InteractionRecord *newSlot = (InteractionRecord *)(this->interactionList + this->interactionCount * sizeof(InteractionRecord));
                        this->interactionCount++;
                        if (newSlot != nullptr) {
                            newSlot->outerId = rec.outerId;
                            newSlot->innerId = rec.innerId;
                            this->initInteractionRecord(&rec); // FUN_006099f0
                        }
                        if (bestPriority < 10) {
                            bestPriority = 9;
                        }
                    } else if (bestPriority <= subResult) {
                        bestPriority = subResult;
                    }
                }
            } else if (bestPriority <= interactionResult) {
                bestPriority = interactionResult;
            }

            // Clean up temporary record if needed (used in initInteractionRecord)
            if (rec.data1 != 0) {
                this->destroyInteractionRecord(rec.data1); // FUN_009c8f10
            }

            innerByteOffset += 4;
        } while (innerByteOffset < 0x18); // 6 inner cell IDs (0x18/4 = 6)
        outerByteOffset += 4;
    } while (outerByteOffset < 0x10); // 4 outer cell IDs (0x10/4 = 4)

    return bestPriority;
}