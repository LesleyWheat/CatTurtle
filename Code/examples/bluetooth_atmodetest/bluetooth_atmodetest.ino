void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  establishContact();
  
}

int count =0;
int timeoutcount=0;
void loop() {
  byte temp;
  int outcount = 0;
  
  // put your main code here, to run repeatedly:
  switch(count){
    case 0:
      Serial1.print("at+init\r\n");
      Serial.println("at+init\r\n");
      break;
    case 1:
      Serial.println("at+iac=9e8b33\r\n");
      Serial1.print("at+iac=9e8b33\r\n");
      break;
    case 2:
      Serial.println("at+class=0\r\n ");
      Serial1.print("at+class=0\r\n ");
      break;
    case 3:
      Serial.println("at+inqm=1,1,20");
      Serial1.print("at+inqm=1,1,20");
      break;
    default:
      Serial1.print("At+inq\r\n");
      Serial.println("At+inq\r\n");
      break;
  }

  count++;

  Serial.println("");
  
  temp = Serial1.read();
  while ((temp == -1) || (temp == 255) && (timeoutcount < 10000)) {
    temp = Serial1.read();
    timeoutcount++;
  }
  //Serial.print((char)temp);
  while ((temp != -1)&&(temp != 255) && (outcount < 50)){
      outcount++;
      Serial.print((char)temp);
      Serial.print(temp, DEC);
      temp = Serial1.read();
  }
  Serial.println("");

  delay(1000);

}

void establishContact() {
      
      while (Serial.available() <= 0) {
        Serial.print('A');   // send a capital A
        delay(500);
      }
      Serial.println(' ');
    }
