// ArduinoのHardSerial(RX/TX)に接続したXBee経由で
// APIモードで信号を送る
// Coordinatorは API、RouterはAPI TYPE2

#include <XBee.h>
const double interval(1)/*[sec]*/;
struct xbee_manager {
  XBee manager;
  uint8_t payload[5];
  //XBeeAddress64 destination_address64;
  XBeeAddress64 destination_address64 = XBeeAddress64(0x0013a200, 0x40994180);//実際の送信先64bitアドレスを記入
  ZBTxRequest tx;
  xbee_manager() : destination_address64(0, 0), tx(destination_address64, payload, sizeof(payload))
  {
    manager.setSerial(Serial);
  }
  
  void loop(int val1=0, int val2=0, int val3=0,int val4=0,float val5=0)
  {
    payload[0] = val1;
    payload[1] = val2;
    payload[2] = val3;
    payload[3] = val4;
    payload[4] = val5;
    manager.send(tx);
    delay(500*interval);
  }
} xbee;


//Servo ----------------------
#include <Servo.h> 
Servo myservo_oyaYB; 
Servo myservo_hitosashiYB; 
Servo myservo_nakaYB; 
Servo myservo_kusuriYB; 
Servo myservo_koYB; 

int oyaYB;
int hitosashiYB;  
int nakaYB;
int kusuriYB;
int koYB;


void setup() {
  Serial.begin(9600);
  myservo_oyaYB.attach(9);
  myservo_hitosashiYB.attach(10);
  myservo_nakaYB.attach(11);
  myservo_kusuriYB.attach(12);
  myservo_koYB.attach(13);
}


void loop() {
  oyaYB       = analogRead(A4);
  hitosashiYB = analogRead(A3);
  nakaYB      = analogRead(A2);
  kusuriYB    = analogRead(A1);
  koYB        = analogRead(A0);

  // oyaYB       = map(oyaYB,        90, 10, 0,    99);
  // hitosashiYB = map(hitosashiYB,  20, 40, 159,  40);
  // nakaYB      = map(nakaYB,       20, 40, 159,  40);
  // kusuriYB    = map(kusuriYB,     20, 40, 0,   179);
  //koYB        = map(koYB,         20, 40, 159,  40);
  
  xbee.loop(koYB,kusuriYB, nakaYB, hitosashiYB,oyaYB);  //A0, A1, A2, A3, A4
}
