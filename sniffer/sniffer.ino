#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;
// Storage for the raw data
unsigned int rawCodes[300];
int codeLen;
unsigned int code [] = {8800, 4600, 450, 650, 450, 650, 450, 700, 450, 650, 450, 700, 450, 650, 450, 650, 450, 1800, 450, 1750, 450, 1800, 400, 1800, 400, 1800, 450, 1750, 450, 1750, 450, 1800, 400, 700, 450, 650, 450, 1800, 400, 700, 450, 1750, 450, 1800, 400, 700, 450, 650, 450, 650, 450, 1800, 450, 650, 450, 1800, 400, 700, 450, 650, 450, 1800, 400, 1800, 400, 1800, 450};

// Extracts the raw data
void extractRaw (decode_results *results) {
  codeLen = results->rawlen - 1;
  // To store raw codes:
  // Drop first value (gap)
  // Convert from ticks to microseconds
  // Tweak marks shorter, and spaces longer
  // to cancel out IR receiver distortion
  for (int i = 1; i <= codeLen; i++)
    if (i % 2)
      // Mark
      rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
    else
      // Space
      rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
}

/*
// Sends a previously sniffer IR signal
void sendCmd (unsigned int * code, unsigned long duration)
{
  unsigned long timeStart = millis();
  do {
    irsend.sendRaw(code, codeLen, 38); // 38KHz
    delay(40);
  } while (millis() &lt;= timeStart + duration);
  
  delay(40);
}*/

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
  { 
    extractRaw(&results);
    
    // Displays the raw codes
    for (int i = 0; i < codeLen; i ++)
    {
      Serial.print(rawCodes[i]);
      Serial.print(", ");
    }
    Serial.println();

    irrecv.resume(); // Receive the next value
  }
  delay(100);
  irsend.sendRaw(code,codeLen,38);
}
