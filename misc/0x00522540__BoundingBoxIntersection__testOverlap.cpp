// FUNC_NAME: BoundingBoxIntersection::testOverlap
undefined4 __thiscall BoundingBoxIntersection::testOverlap(BoundingBoxIntersection *this, BoundingBox *box1, BoundingBox *box2)
{
    undefined4 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    undefined4 uVar9;

    // Load components of this bounding box (likely min/max x,y)
    uVar1 = this->field_1;   // +0x04
    uVar2 = this->field_0;   // +0x00

    // Load components of box1 (min/max?)
    uVar3 = box1->field_1;   // +0x04
    uVar4 = box1->field_0;   // +0x00

    // Load components of box2 (min/max?)
    uVar5 = box2->field_1;   // +0x04
    uVar6 = box2->field_0;   // +0x00

    // Load another component from global/storage (offset 4 from ESI)
    uVar7 = *(undefined4 *)(esi + 4); // +0x04 of some base

    // Check combination: (this, box1, box2) order
    char cVar10 = FUN_00522330(uVar7, uVar6, uVar5, uVar4, uVar3, uVar2, uVar1);
    if (cVar10 == '\0') {
        // Alternative combination using EDI storage
        uVar8 = edi->field_1;   // +0x04
        uVar9 = edi->field_0;   // +0x00

        cVar10 = FUN_00522330(uVar7, uVar6, uVar5, uVar2, uVar1, uVar9, uVar8);
        if (cVar10 == '\0') {
            // Another combination
            cVar10 = FUN_00522330(uVar7, uVar6, uVar5, uVar4, uVar3, uVar9, uVar8);
            if (cVar10 == '\0') {
                return 0;  // No overlap detected
            }
        }
    }
    return 1;  // Overlap detected
}