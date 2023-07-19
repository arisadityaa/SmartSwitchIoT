#define pSaklar 14
#define lampu 2

void initPin() {
  pinMode(pSaklar, INPUT_PULLUP);
  pinMode(lampu, OUTPUT);
  tmpSaklar = digitalRead(pSaklar);
  digitalWrite(lampu, saklarState);
}
