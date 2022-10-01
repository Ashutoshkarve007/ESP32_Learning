
#define DEBUG true
#define MODE_1A

#define UART_BAUD 9600

#define MODEM_RXD 16
#define MODEM_TXD 17

String from_usb = "";

void setup() {
  Serial.begin(9600);
  Serial1.begin(UART_BAUD, SERIAL_8N1, MODEM_RXD, MODEM_TXD);

}

void loop() {

usb_serial();
}


String sendData(String command, const int timeout, boolean debug)
{

  String response = "";
  if (command.equals("1A") || command.equals("1a"))
  {
    Serial.println();
    Serial.println("Get a 1A, input a 0x1A");

    //Serial1.write(0x1A);
    Serial1.write(26);
    Serial1.println();
    return "";
  }
  else
  {
    Serial1.println(command);
  }

  long int time = millis();
  while ((time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}


void usb_serial()
{
  while (Serial1.available() > 0)
  {
    Serial.write(Serial1.read());

    yield();
  }
  while (Serial.available() > 0)
  {
#ifdef MODE_1A
    int c = -1;
    c = Serial.read();
    if (c != '\n' && c != '\r')
    {
      from_usb += (char)c;
    }
    else
    {
      if (!from_usb.equals(""))
      {
        sendData(from_usb, 0, DEBUG);
        from_usb = "";
      }
    }
#else
    Serial1.write(Serial.read());
    //  Serial.print(Serial1.read());
    yield();
#endif
  }
}
