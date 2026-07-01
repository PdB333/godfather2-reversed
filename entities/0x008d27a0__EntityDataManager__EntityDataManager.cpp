// FUNC_NAME: EntityDataManager::EntityDataManager
class EntityDataManager {
public:
    // VTable pointer at +0x00
    void* vfptr;
    // Field at +0x04
    int unk04;
    // Field at +0x18 (0x18 / 4 = 6)
    int unk18;
    // Field at +0x20 (0x20 / 4 = 8)
    int unk20;
    // Field at +0x24 (0x24 / 4 = 9)
    int unk24;
    // Capacity or count at +0x2C (0x2C / 4 = 0xB)
    int capacityA;
    // Field at +0x30 (0x30 / 4 = 0xC)
    int unk30;
    // Field at +0x34 (0x34 / 4 = 0xD)
    int unk34;
    // Field at +0x38 (0x38 / 4 = 0xE)
    int unk38;
    // Field at +0x3C (0x3C / 4 = 0xF)
    int unk3C;
    // Capacity or count at +0x40 (0x40 / 4 = 0x10)
    int capacityB;
    // Field at +0x44 (0x44 / 4 = 0x11)
    int unk44;
    // Field at +0x1C (0x1C / 4 = 7)
    int unk1C;

    EntityDataManager() {
        vfptr = (void*)0x00d7d3d8;  // VTable set to global pointer
        unk04 = 0;
        unk18 = 0;
        unk20 = 0;
        unk24 = 0;
        unk30 = 0;
        unk1C = 0;
        unk34 = 0;
        unk38 = 0;
        unk3C = 0;
        unk44 = 0;

        capacityA = 0;
        if (capacityA < 30) {
            FUN_008d2380(30);  // Allocate or initialize internal storage for capacityA
        } else if (capacityA < 31) {
            goto LAB_008d27e0;
        }
        capacityA = 30;

LAB_008d27e0:
        unk3C = 0;
        unk34 = 0;  // Note: decompiler shows param_1[0x10] reset, but we already set it later
        unk44 = 0;
        unk34 = 0;  // param_1[0xd] set again
        unk38 = 0;  // param_1[0xe] set again

        capacityB = 0;
        if (capacityB < 30) {
            FUN_008be050(30);  // Allocate or initialize internal storage for capacityB
            capacityB = 30;
            unk1C = 0;
            return;
        }
        if (capacityB > 30) {
            capacityB = 30;
        }
        unk1C = 0;
    }
};