// FUNC_NAME: Animated::updateAnimationLayers

#include <cstdint>

// Animation slot (used for each animation layer)
struct AnimSlot {
    uint16_t unknown0;      // +0x00
    uint16_t activeFlag;    // +0x04 (if non-zero, frameCounter is incremented)
    uint16_t frameCounter;  // +0x06 (incremented every frame when active)
    uint8_t pad[24];        // padding up to +0x20
    uint8_t blendCount;     // +0x20 (number of blend entries in the parent's array)
};

// Another structure used for time delta calculation
struct TimeSource {
    float valueA;           // +0x00 (unused here)
    float valueB;           // +0x04 (unused here)
    float currentTime;      // +0x08
    // ... gap ...
    float baseTime;         // +0x68
};

// Main object (likely Animated or similar)
void __fastcall Animated::updateAnimationLayers(void)
{
    // Retrieve pointers to each animation layer slot
    AnimSlot* slot1 = *(AnimSlot**)(this + 0x1C);
    AnimSlot* slot2 = *(AnimSlot**)(this + 0x20);
    AnimSlot* slot3 = *(AnimSlot**)(this + 0x24);
    AnimSlot* slot4 = *(AnimSlot**)(this + 0x28);
    AnimSlot* slot5 = *(AnimSlot**)(this + 0x2C);
    AnimSlot* slot6 = *(AnimSlot**)(this + 0x30);
    AnimSlot* slot7 = *(AnimSlot**)(this + 0x34);
    AnimSlot* slot8 = *(AnimSlot**)(this + 0x38);
    AnimSlot* slot9 = *(AnimSlot**)(this + 0x3C);
    AnimSlot* slotA = *(AnimSlot**)(this + 0x44);
    AnimSlot* slotB = *(AnimSlot**)(this + 0x9C);

    // Increment frame counters for all active layers
    if (slot1->activeFlag != 0) slot1->frameCounter++;
    if (slot2->activeFlag != 0) slot2->frameCounter++;
    if (slot3->activeFlag != 0) slot3->frameCounter++;
    if (slot4->activeFlag != 0) slot4->frameCounter++;
    if (slot5->activeFlag != 0) slot5->frameCounter++;
    if (slot6->activeFlag != 0) slot6->frameCounter++;
    if (slot7->activeFlag != 0) slot7->frameCounter++;
    if (slot8->activeFlag != 0) slot8->frameCounter++;
    if (slotA->activeFlag != 0) slotA->frameCounter++;
    if (slotB->activeFlag != 0) slotB->frameCounter++;
    if (slot9->activeFlag != 0) slot9->frameCounter++;

    // Call another update method (e.g., updateBlendWeights)
    FUN_00bf0eb0();

    // Compute delta time from a time source
    TimeSource* timeSrc = *(TimeSource**)(*(int*)(this + 0x34) + 8);
    *(float*)(this + 0x108) = timeSrc->currentTime - timeSrc->baseTime;

    // Clear blend/weight data array for each layer
    uint8_t count = slot1->blendCount;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            *(uint64_t*)(this + 0x150 + i * 8) = 0; // zero 8-byte entry
        }
    }
}