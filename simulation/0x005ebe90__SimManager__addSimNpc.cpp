// FUNC_NAME: SimManager::addSimNpc
#include <cstdint>

// SimManager class (partial)
// Offsets:
// +0x580: m_pRootSceneNode (pointer to scene graph root)
// +0x5a0: m_npcSlots[NPC_SLOT_COUNT] (array of SimNpcSlot, each 0xf8 bytes)
struct SimNpcSlot {
    uint8_t pad0[0xa4];
    uint32_t m_someId; // +0xa4
    uint8_t pad1[0x8];
    float m_transform[2]; // +0xb0 (8 bytes, likely position or quaternion)
    uint8_t m_active; // +0xb8 flag
    // rest 0xf8-0xb9 = 0x3f bytes padding
};

__declspec(naked) void* __fastcall allocateNpc() // placeholder for FUN_005e9d10
{
    __asm {
        // This function allocates a new NPC object, returns pointer in eax
        jmp FUN_005e9d10;
    }
}

__declspec(naked) void __fastcall setSceneTransform(uint32_t sceneNode, uint32_t transformOffset, int zero, void* transformStruct) // placeholder for FUN_00c9cbe0
{
    __asm {
        jmp FUN_00c9cbe0;
    }
}

__declspec(naked) void __fastcall beginSceneUpdate() // placeholder for FUN_00c9eac0
{
    __asm {
        jmp FUN_00c9eac0;
    }
}

__declspec(naked) void __fastcall addToScene(int zero, void* transformStruct) // placeholder for FUN_00c9cd40
{
    __asm {
        jmp FUN_00c9cd40;
    }
}

__declspec(naked) void __fastcall endSceneUpdate() // placeholder for FUN_00c9eae0
{
    __asm {
        jmp FUN_00c9eae0;
    }
}

uint32_t SimManager::addSimNpc(uint16_t slotIndex)
{
    // Calculate pointer to the slot in the array
    SimNpcSlot* slot = reinterpret_cast<SimNpcSlot*>(reinterpret_cast<uint8_t*>(this) + 0x5a0 + slotIndex * 0xf8);

    // Only activate if slot is not already active
    if (slot->m_active == 0)
    {
        void* newNpc = allocateNpc();
        if (newNpc != nullptr)
        {
            // Local struct for scene transform (size 20 bytes: 8 + 4 + 4 + 4)
            struct SceneTransformStruct {
                uint64_t field0_0;   // +0
                uint32_t field8;     // +8
                uint32_t fieldC;     // +C
                uint32_t field10;    // +10
            } transformData;

            setSceneTransform(
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x580), // m_pRootSceneNode
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(newNpc) + 0x10), // offset into NPC object
                0,
                &transformData
            );

            transformData.field0_0 = 0;
            transformData.field8 = slot->m_someId;
            transformData.fieldC = 0;
            transformData.field10 = 0;

            beginSceneUpdate();
            addToScene(0, &transformData);
            endSceneUpdate();

            // Copy scene node's transform into the slot
            uint32_t sceneNode = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x580);
            uint64_t* srcTransform = reinterpret_cast<uint64_t*>(sceneNode + 8);
            uint64_t* dstTransform = reinterpret_cast<uint64_t*>(&slot->m_transform);
            *dstTransform = *srcTransform;

            // Mark slot as active
            slot->m_active = 1;

            // Return combined success flag and upper bits of sceneNode pointer
            return (sceneNode & 0xFFFFFF00) | 1;
        }
    }
    return 0;
}