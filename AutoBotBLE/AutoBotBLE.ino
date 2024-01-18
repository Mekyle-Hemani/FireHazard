#include <SoftwareSerial.h> //HM10 library
#include <Servo.h> //Servo library

SoftwareSerial HM10(50, 51); // RX = 50, TX = 51

char appData; //Sets a one byte arduino value that will recieve the data of the HM10 character by character

//Sets a variable that will be assigned from the appData variable and will be cleaned while there is no incoming data
String inData = "";

//Assigns all the servos to an objectg to be programmed later

Servo servoFLH; //Front Left Hip
Servo servoFLK; //Front Left Knee
Servo servoFLA; //Front Left Ankle

Servo servoBLH; //Back Left Hip
Servo servoBLK; //Back Left Knee
Servo servoBLA; //Back Left Ankle

Servo servoBRH; //Back Right Hip
Servo servoBRK; //Back Right Knee
Servo servoBRA; //Back Right Ankle

Servo servoFRH; //Front Right Hip
Servo servoFRK; //Front Right Knee
Servo servoFRA; //Front Right Ankle

void setup()

{
  Serial.begin(9600); //Begins the serial connection

  Serial.println("HM10 serial started at 9600"); //Prints a confirmation message

  HM10.begin(9600); //Set the HM10 serial module at 9600 baud rate


  //Attaches the servos
  servoFLH.attach(46); //Attaching Front Left Hip
  servoFLK.attach(45); //Attaching Front Left Knee
  servoFLA.attach(44); //Attaching Front Left Ankle

  servoBLH.attach(11); //Attaching Back Left Hip
  servoBLK.attach(10); //Attaching Back Left Knee
  servoBLA.attach(9); //Attaching Back Left Ankle

  servoBRH.attach(6); //Attaching Back Right Hip
  servoBRK.attach(5); //Attaching Back Right Knee
  servoBRA.attach(3); //Attaching Back Right Ankle

  servoFRH.attach(13); //Attaching Front Right Hip
  servoFRK.attach(12); //Attaching Front Right Knee
  servoFRA.attach(11); //Attaching Front Right Ankle


  //Write the servos to a default standing value
  //A=90
  //B=105
  //C=0

  servoFLH.write(90);
  servoFLK.write(105);
  servoFLA.write(0);

  servoBLH.write(90);
  servoBLK.write(105);
  servoBLA.write(0);

  servoBRH.write(90);
  servoBRK.write(105);
  servoBRA.write(0);

  servoFRH.write(90);
  servoFRK.write(105);
  servoFRA.write(0);

  delay(1000); //Adds a delay time to give the robot time to move the servos
}

void loop()
{
  HM10.listen();  //Listening to the HM10 module
  
  while (HM10.available() > 0) {   //While the HM10 module is sending data...

    appData = HM10.read(); //Setting the variable called earlier to the newest piece of data from the HM10

    inData = (inData+String(appData));  //Save the data to a total string

    Serial.write(appData); //Write the data recieved

  }
    if (Serial.available()) {  //Sends any input sent from the computer locally to the HM10 client
      HM10.write(Serial.read()); //Writes the serial data to the HM10 module
    }


    //This code is for sending direct serial commands and not controller based

    if (inData == "ON") { //Checks if the data recieved is the string "ON"

      //Sets all the servos to be an open standing position
      //A=0
      //B=120
      //C=0

      servoFLH.write(0);
      servoFLK.write(120);
      servoFLA.write(0);

      servoBLH.write(0);
      servoBLK.write(100);
      servoBLA.write(0);

      servoBRH.write(0);
      servoBRK.write(120);
      servoBRA.write(0);

      servoFRH.write(0);
      servoFRK.write(120);
      servoFRA.write(0);

      delay(1000); //Adds a delay time to allow for the servos to reach their destination

      Serial.println(inData); //Print any other data recieved
    }

    if (inData == "OFF") { //Checks if the data recieved is the string "ON"

      //Sets all the servos to be a closed sitting position
      //A=90
      //B=105
      //C=90

      servoFLH.write(90);
      servoFLK.write(105);
      servoFLA.write(90);

      servoBLH.write(90);
      servoBLK.write(105);
      servoBLA.write(90);

      servoBRH.write(90);
      servoBRK.write(105);
      servoBRA.write(90);

      servoFRH.write(90);
      servoFRK.write(105);
      servoFRA.write(90);

      delay(1000); //Adds a delay time to allow for the servos to reach their destination

      Serial.println(inData); //Prints any other data recieved
    }
  
  if (HM10.available() == 0){ //If the HM10 is not sending data at the moment...
    inData = ""; //Reset the string that contains all the messages to 0
  }

  Serial.println(inData); //Print the variable that contains the HM10 client data
}