// FUNC_NAME: SingletonClass::~SingletonClass
void __thiscall SingletonClass::destructor(SingletonClass *this) {
  // Check if this object is the global singleton instance
  if (*this == reinterpret_cast<SingletonClass *>(DAT_0120e93c)) {
    // If yes, call shutdown/cleanup on the global instance
    FUN_004086d0(&DAT_0120e93c);
  }
  // Call base destructor or cleanup for this instance
  FUN_0046efc0(this);
  return;
}