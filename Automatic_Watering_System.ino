/* Code Written by DPV TECHNOLOGY. WE have explained all the code in the grey comments.
we recommend you to go over the code, examine it, play with it, improve it and modify it according to your needs. 
SUBSCRIBE DPV TECHNOLOGY: 
https://www.youtube.com/dpvtechnology?sub_confirmation=1

*/
 
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);
int received ='r';
int pump=11;
int val; 
int motor_state=0;
String str;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(pump,OUTPUT);
  pinMode(8,INPUT);
}


void loop()
{
  val = digitalRead(8);  //Read data from soil moisture sensor  
    if(val == HIGH) //HIGH
    {
      digitalWrite(11,HIGH);//LOW//if soil moisture sensor provides LOW value send LOW value to relay
    }
    else
    {
      digitalWrite(11,LOW);//HIGH //if soil moisture sensor provides HIGH value send HIGH value to relay
    }
    delay(400); //Wait for few second and then continue the loop.
  if (Serial.available()>0){
    motor_state=Serial.read();
  }
  if(motor_state=='1'){
    digitalWrite(pump,LOW);
    delay(5000);
    digitalWrite(pump,HIGH);
    delay(1000);
    Serial.print("Watered");
    motor_state=0;
  }

 if (mySerial.available()>0){
   //received=mySerial.read();
   //str=mySerial.readString();
   received=mySerial.read();
   Serial.write(received);
   switch(received)
  {
    case 's':
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.print("Watered");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      received='n';
      digitalWrite(pump,LOW);
      delay(5000);
      digitalWrite(pump,HIGH);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      //Serial.println("Done");
      received='n';
      break;
  }
 }
}
