// FUNC_NAME: CrimeScene::processObjectives
int __thiscall CrimeScene::processObjectives(CrimeScene *this)
{
    int currentObjective;
    int checkResult;
    int success;

    success = 0;
    if (this != 0) {
        // Set processing flag at +0x08
        *(char *)(this + 8) = 1;
        // Check with global CrimeManager at DAT_012234bc
        checkResult = FUN_005e51a0(DAT_012234bc, this);
        if (checkResult != 0) {
            // Pre‑advance processing if check passed
            FUN_005f3770();
            currentObjective = *(int *)(this + 0x10); // m_pCurrentObjective
            if ((currentObjective != 0) && (*(char *)(currentObjective + 0xc) != 0)) {
                // Objective completed – clear its flag
                *(char *)(currentObjective + 0xc) = 0;
                // Clear processing flag
                *(char *)(this + 8) = 0;
                // Complete current objective and advance to next
                FUN_005f57b0();
                FUN_005f0420();
                success = 1;
            }
        }
    }
    return success;
}