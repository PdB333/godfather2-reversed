// FUNC_NAME: LineReader::readLine
void LineReader::readLine(int flags, char *delimiters)
{
  char *in_EAX;
  char cVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  
  if (in_EAX != (char *)0x0) {
    if (DAT_01164078 < 1) {
      DAT_01164078 = 1;
    }
    cVar2 = *in_EAX;
    iVar5 = DAT_01164078;
    while (cVar2 != '\0') {
      if (cVar2 == '\n') {
        if (flags != 0) {
          return;
        }
        in_EAX = in_EAX + 1;
        iVar5 = iVar5 + 1;
        DAT_01164078 = iVar5;
      }
      else if ((cVar2 != '#') || (DAT_010c3684 != 0)) {
        if ((cVar2 == ' ') || ((cVar2 == '\t' || (cVar2 == '\r')))) {
          do {
            cVar2 = *in_EAX;
            DAT_01164078 = iVar5;
            if ((cVar2 != ' ') && (((cVar2 != '\t' && (cVar2 != '\r')) && (cVar2 != '\n'))))
            goto LAB_004d5e55;
            if (cVar2 == '\n') {
              if (flags != 0) goto LAB_004d5e55;
              iVar5 = iVar5 + 1;
            }
            in_EAX = in_EAX + 1;
          } while( true );
        }
        if (cVar2 == '/') {
          cVar1 = '/';
          if (in_EAX[1] == '/') {
            do {
              if (cVar1 == '\n') break;
              cVar1 = in_EAX[1];
              in_EAX = in_EAX + 1;
            } while (cVar1 != '\0');
            if ((flags != 0) && (*in_EAX == '\n')) goto LAB_004d5e55;
          }
          else {
            if (in_EAX[1] != '*') goto LAB_004d5efa;
            cVar2 = '/';
            while ((in_EAX[-1] != '*' || (cVar2 != '/'))) {
              cVar2 = in_EAX[1];
              in_EAX = in_EAX + 1;
              if (cVar2 == '\0') {
                return;
              }
            }
          }
          if (*in_EAX == '\0') {
            return;
          }
        }
        else {
LAB_004d5efa:
          if (delimiters == (char *)0x0) {
            return;
          }
          pcVar3 = delimiters;
          if (*delimiters == '\0') {
            return;
          }
          while (pcVar4 = pcVar3 + 1, cVar2 != *pcVar3) {
            pcVar3 = pcVar4;
            if (*pcVar4 == '\0') {
              return;
            }
          }
        }
        in_EAX = in_EAX + 1;
      }
LAB_004d5e55:
      cVar2 = *in_EAX;
    }
  }
  return;
}