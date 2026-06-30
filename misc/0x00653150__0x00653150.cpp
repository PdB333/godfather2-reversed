#include <cstdint>

extern "C" {
    extern float DAT_00e2b05c;
    extern double DAT_00e44708;
    extern double DAT_00e448a8;
    extern unsigned char DAT_01203540;

    int FUN_0065bf40();
    char FUN_00653400(int param_2);
    void FUN_00653800(int* param_1);
    void FUN_00653080(const char* param_1);
    void FUN_006576b0(int param_1, int* param_2);

    void __thiscall FUN_00653150(int* param_1, int param_2)
    {
        double dVar1;
        char cVar2;
        int iVar3;

        if ((float)param_1[0x33] != DAT_00e2b05c) {
            iVar3 = FUN_0065bf40();
            dVar1 = (double)iVar3;
            if (iVar3 < 0) {
                dVar1 = dVar1 + DAT_00e44708;
            }
            if (dVar1 * DAT_00e448a8 < (double)(float)param_1[0x33]) {
                return;
            }
        }

        DAT_01203540 = '\0';
        cVar2 = FUN_00653400(param_2);
        if (cVar2 == '\0') {
            return;
        }

        param_1[3] = *(int*)(param_1[0x69] + 100);
        FUN_00653800(param_1);
        *(int*)(param_2 + 0x34) = param_1[0x72];
        (**(void(__thiscall**)(int))( *(int*)param_1 + 0x30))(param_2);

        if (*(char*)(param_2 + 0x1c) != '\0') {
            if (DAT_01203540 != '\0') {
                goto LAB_00653200;
            }
            FUN_00653080("Invalid Packet.");
        }

        if (DAT_01203540 == '\0') {
            DAT_01203540 = 0;
            return;
        }

    LAB_00653200:
        FUN_006576b0(param_1[0x69], param_1);
        DAT_01203540 = 0;
    }
}