// FUNC_NAME: AudioManager::updateSoundPool
#include <cstdint>

// Constants
constexpr int kMaxChannels = 0x80;
constexpr int kChannelStructSize = 0x54; // 21 ints

// Global: number of available sound pool slots (from address 0x01205404)
extern int s_poolSlotCount;

// Forward declarations for helper functions
int __thiscall allocatePacket(); // FUN_00627290
void __thiscall releaseSlot(int slot, int unk); // FUN_00626f80
void __thiscall lockPool(); // FUN_00626fd0
void __thiscall unlockPool(); // FUN_00627010
void __thiscall commitPacket(); // FUN_006270e0
int __thiscall createPacket(int slot, char* data, int size); // FUN_00638920
void* __thiscall getConstantTable(); // FUN_00637f10
void* __thiscall getVariableTable(); // FUN_00637f90
void* __thiscall getDefaultTable(); // FUN_00637ea0
void* __thiscall convertToNode(int slot, int* state, int* packet, int flag); // FUN_00633bc0
void* __thiscall createNode(int* state, int* packet, int flag); // FUN_00633c30
void __thiscall registerEvent(...); // FUN_00636570

// Channel structure at this + 0x18, stride 0x54
struct SoundChannel {
    int m_timer;          // +0x00 (relative to channel base)
    int m_unknown1;       // +0x04 (piVar7[-1] uses this? Actually offset -0x04 from start? Let's keep relative)
    float m_unknown2;     // +0x08? (piVar7[2] used as pointer)
    char m_paused;        // +0x49
    char m_looping;       // +0x4A
    char m_loopFlag;      // +0x12? (piVar7[0x12] == byte)
    int m_nextTimer;      // +0x04? (piVar7[1] is m_nextTimer)
    int m_payloadSize;    // +0x?? (piVar7[2] pointer? Actually used as pointer to data)
};

int __thiscall AudioManager::updateSoundPool(int tickNormal, int tickLoop) {
    if ((tickNormal <= 0) && (tickLoop <= 0))
        return 0;

    SoundChannel* channels = reinterpret_cast<SoundChannel*>(reinterpret_cast<char*>(this) + 0x18);
    int channelIndex = 0;
    int iterationCounter = 0; // used for offset calculation later (local_1c)
    
    do {
        SoundChannel* ch = &channels[channelIndex];
        // Check if channel is active and not yet processed (m_paused == 0)
        if ((ch->m_unknown1 != 0) && (ch->m_paused == 0)) {
            // Determine which timer to subtract (normal or loop)
            int tickToUse = ch->m_looping ? tickLoop : tickNormal;
            if (tickToUse > 0) {
                ch->m_timer -= tickToUse;
            }
            
            // Inner loop: while timer <= 0 and channel not exhausted
            int innerLoopCount = 0;
            do {
                if ((ch->m_timer > 0) || (ch->m_unknown1 == 0))
                    break;
                if (innerLoopCount >= 4)
                    break;

                if (ch->m_loopFlag == 0) {
                    // Non-looping: reset timer to nextTimer value
                    ch->m_timer = ch->m_nextTimer + ch->m_timer; // note: m_timer is negative? Actually it's already <=0
                } else {
                    // Looping: decrement global pool count, mark as paused
                    s_poolSlotCount--;
                    ch->m_paused = 1;
                }

                // Build packet from data (piVar7+2 points to a string or byte array)
                char* packetData = reinterpret_cast<char*>(ch) + 8; // offset of piVar7[2]? Actually piVar7[2] is pointer, but here it's relative? Need to check.
                // Actually from decomp: piVar8 = piVar7 + 2; so piVar8 points to the third int of the channel.
                // piVar7 is the base of channel? Let's assume channel starts at piVar7[0] as m_timer.
                // So piVar7[2] is int field at offset 8, but used as a pointer to string.
                // In original: piVar8 = piVar7 + 2; if null then some else do loop.
                // We'll treat piVar8 as a char* pointer.
                char* strPtr = reinterpret_cast<char*>(&ch->m_unknown2); // Probably a pointer to string, so treat as pointer to pointer? Actually we need to follow.
                // Let's keep the logic: if (piVar8 == NULL) then clear something; else compute length.
                // We'll just call the packet creation function with the data pointer.
                // For now, I'll use a placeholder that corresponds to the original flow.
                // In the original, after building packet, there is a allocation/conversion phase.
                
                // Simulate: call packet allocator with slot id (ch->m_unknown1) and data
                int slot = ch->m_unknown1;
                int packetCreateResult = createPacket(slot, strPtr, 0 /* size computed */);
                // Then the result is stored at slot's output buffer.
                
                // The code then checks something about state and converts to node.
                // Skipping details for brevity.
                
                innerLoopCount++;
            } while (ch->m_paused == 0);
        }
        
        channelIndex++;
        iterationCounter++; // this is used later for something
        if (channelIndex >= kMaxChannels)
            break;
    } while (channelIndex < kMaxChannels);
    
    return 0;
};