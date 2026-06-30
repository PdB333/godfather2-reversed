// Xbox PDB: AptRenderingContext::pushVertexMatrix
// FUNC_NAME: AptRenderer::pushVertexMatrix
void AptRenderer::pushVertexMatrix(void)
{
    // Assert: stack not full
    if (this->vertexMatrixStackCount >= 16) {
        // Assertion failed: "nVertexMatrixStack < ((int)(sizeof(aVertexMatrixStack) / sizeof(aVertexMatrixStack[0])))"
        // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_Apt.h, line 507
        char* expr = "nVertexMatrixStack < ((int)(sizeof(aVertexMatrixStack) / sizeof(aVertexMatrixStack[0])))";
        char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_Apt.h";
        int line = 0x1fb; // 507
        int type = 2; // likely assertion type
        char* assertFlag = &DAT_0112902b; // global assert enable flag
        if (*assertFlag != '\0') {
            int* piVar2 = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30) + 0x30); // CRT assertion handler
            uint uVar4 = 1;
            if (piVar2 != (int*)0x0) {
                uVar4 = (**(code**)(*piVar2 + 8))(&expr, expr); // call assertion handler
            }
            if ((uVar4 & 2) != 0) {
                *assertFlag = 0;
            }
            if (((piVar2 != (int*)0x0) || (type != 4)) &&
                (((uVar4 & 1) != 0 || ((type == 0) || (type == 1))))) {
                code* pcVar3 = (code*)swi(3); // debug break
                (*pcVar3)();
                return;
            }
        }
    }

    // Push current matrix onto stack
    // Stack slot at +0x238 + count * 0x18 (24 bytes per slot)
    undefined8* dest = (undefined8*)(this + 0x238 + this->vertexMatrixStackCount * 0x18);
    dest[0] = *(undefined8*)(this + 0x220);
    dest[1] = *(undefined8*)(this + 0x228);
    dest[2] = *(undefined8*)(this + 0x230);

    // Increment stack count
    this->vertexMatrixStackCount++;

    // Reset current matrix to identity (or clear)
    FUN_005b4540(this + 0x220); // likely sets matrix to identity

    // Call release/cleanup callback on current matrix
    (*DAT_0119cb68)(this + 0x220);
}