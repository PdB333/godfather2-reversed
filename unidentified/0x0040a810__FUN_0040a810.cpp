extern "C" void FUN_0040a810(int param_1)
{
    float value = static_cast<float>(param_1);

    if (param_1 < 0) {
        value = value + DAT_00e44578;
    }

    DAT_012067fc = value * DAT_01206a30;
}