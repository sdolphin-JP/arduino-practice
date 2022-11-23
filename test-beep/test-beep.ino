
static int _NoteFreq[84] =
{
  // ド ド#    レ    レ#   ミ    ファ   ファ# ソ     ソ#   ラ    ラ#    シ
  262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,
  523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,
  1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
  2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,
};

static long dorakue[] =
{
  1760, 1661, 1568, 1480, 1397, 1319, 1245, 1175, 1109, 1047, 932, 880, 831, 784, 740, 698, 659, 622, 587, 587, 554, 523, 494, -10000466,
  -5001397, -7002093, -6001976, -500000, -1001568, -1001661, -10001760,
  3136, 1397, 2217, 1047, 1568, 1760, 2794, 1175, 1568, 1760, 784, 1568, 698, 2093, 831, 1319, 698, 1568, 1760, 1568,
  0
};

static int  notePos     = 0;
static char spbuff[256] = { 0 };

void setup()
{
  Serial.begin(115200);

  digitalWrite(8, LOW);
  pinMode(8, OUTPUT);
}

void loop()
{
  noTone(8);

  if (0 == dorakue[notePos])
  {
    notePos = 0;
    delay(2000);
  }

  if (0 > dorakue[notePos])
  {
    long on = (-1 * dorakue[notePos]) % 10000;
    long dt = (-1 * dorakue[notePos]) / 10000;

    sprintf(spbuff, "note = %ld on = %ld dt = %ld", dorakue[notePos], on, dt);
    Serial.println(spbuff);

    if (0 != on)
    {
      tone(8, on);
    }

    delay(dt);
  }

  else
  {
    tone(8, dorakue[notePos]);
    delay(50);
  }

  notePos++;
}
