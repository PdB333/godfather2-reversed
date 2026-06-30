// FUNC_NAME: objectConstructChain_00604030
void objectConstructChain(int param_1, int param_2, int param_3, int param_4)
{
    // Call base initialization (likely a constructor or setup routine)
    // Passes all four parameters through
    baseConstruct(param_1, param_2, param_3, param_4);
    
    // Additional initialization on param_3 (e.g., a sub-object or extra state)
    extraInit(param_3);
}