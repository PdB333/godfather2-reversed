// FUNC_NAME: Sentient::getHealth
int __thiscall Sentient::getHealth(Sentient* this) {
    // Default value 0; calls internal function to fetch health
    int value = 0;
    byte success; // ignored – indicates if retrieval succeeded
    FUN_006039d0(this, &value, &success);
    return value;
}