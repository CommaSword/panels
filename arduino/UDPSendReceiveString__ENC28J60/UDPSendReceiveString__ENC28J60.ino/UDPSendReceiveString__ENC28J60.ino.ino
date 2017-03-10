#include <UIPEthernet.h>

EthernetUDP udp;
unsigned long next;
IPAddress pongIP(192, 168, 36, 142);

void setup() {

  Serial.begin(9600);

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  Serial.println("aaa");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  Serial.println(Ethernet.localIP());
  next = millis()+5000;
}

void loop() {

  int success;
  int len = 0;

  if (((signed long)(millis()-next))>0)
    {
      do
        {
          success = udp.beginPacket(IPAddress(192,168,0,1),5000);
          Serial.print("beginPacket: ");
          Serial.println(success ? "success" : "failed");
          //beginPacket fails if remote ethaddr is unknown. In this case an
          //arp-request is send out first and beginPacket succeeds as soon
          //the arp-response is received.
        }
      while (!success && ((signed long)(millis()-next))<0);
      if (!success )
        goto stop;

      success = udp.write("hello world from arduino");

      Serial.print("bytes written: ");
      Serial.println(success);

      success = udp.endPacket();

      Serial.print("endPacket: ");
      Serial.println(success ? "success" : "failed");

      do
        {
          //check for new udp-packet:
          success = udp.parsePacket();
        }
      while (!success && ((signed long)(millis()-next))<0);
      if (!success )
        goto stop;

      Serial.print("received: '");
      do
        {
          int c = udp.read();
          Serial.write(c);
          len++;
        }
      while ((success = udp.available())>0);
      Serial.print("', ");
      Serial.print(len);
      Serial.println(" bytes");

      //finish reading this packet:
      udp.flush();

      stop:
      udp.stop();
      next = millis()+5000;
    }
}
