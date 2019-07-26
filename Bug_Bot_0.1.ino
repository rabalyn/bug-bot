#include <Servo.h>
//#include <hcsr04.h>

//#define TRIG_PIN 49
//#define ECHO_PIN 47

#define defaultXdegree 90
#define defaultKneeDegree 30
#define moveLegX 20

//HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 10, 4000);

Servo frontRightX;
Servo frontRightY;
Servo frontRightZ;

Servo midRightX;
Servo midRightY;
Servo midRightZ;

Servo backRightX;
Servo backRightY;
Servo backRightZ;


Servo frontLeftX;
Servo frontLeftY;
Servo frontLeftZ;

Servo midLeftX;
Servo midLeftY;
Servo midLeftZ;

Servo backLeftX;
Servo backLeftY;
Servo backLeftZ;

Servo frontUltrasonic;

// Bein Array im Uhrzeigersinn von vorne rechts nach vorne links
Servo legs[6][3] = {
  { frontRightX, frontRightY, frontRightZ },
  { midRightX, midRightY, midRightZ },
  { backRightX, backRightY, backRightZ },
  { frontLeftX, frontLeftY, frontLeftZ },
  { midLeftX, midLeftY, midLeftZ },
  { backLeftX, backLeftY, backLeftZ },
};


void setup() {
  // warte auf Initialisierung der seriellen Schnittstelle
  /*
  while(!Serial) {
    ;
  }
  Serial.begin(9600);
  */
//#### zuordnung der Servopins  
frontRightX.attach(36); frontRightY.attach(38); frontRightZ.attach(40);
midRightX.attach(28);   midRightY.attach(30);   midRightZ.attach(32);
backRightX.attach(22);  backRightY.attach(24);  backRightZ.attach(26);

frontLeftX.attach(23); frontLeftY.attach(25); frontLeftZ.attach(27);
midLeftX.attach(29);   midLeftY.attach(31);   midLeftZ.attach(33);
backLeftX.attach(37);  backLeftY.attach(39);  backLeftZ.attach(41);

  frontUltrasonic.attach(43);


setAllLegServos(defaultXdegree);      //Stellt alle Gelenke auf 90°
frontUltrasonic.write(defaultXdegree);//90° Ultraschallsensor
}


void setAllLegServos(int liftFootdegree) {    //fährt alle Beine in einen Standart-Walker-Modus
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 3; j++) {
      if(j == 0) {
        legs[i][j].write(liftFootdegree);
      } else {
        if(i < 3) { // rechts i = 0, 1, 2
          legs[i][j].write(defaultXdegree + defaultKneeDegree);
        } else {  // links i = 3, 4, 5
          legs[i][j].write(defaultXdegree - defaultKneeDegree);
        }
      }
    }
  }
}

void leftFrontLegForward(Servo leg[], int liftFootdegree) {         // Vorne Links nach Vorn
  //hebt Fuß an
  leg[1].write(defaultXdegree - defaultKneeDegree - liftFootdegree);
  leg[2].write(defaultXdegree - defaultKneeDegree - liftFootdegree);
  delay(50);

  //Bewegt Bein nach vorne
  for (int i = defaultXdegree; i > defaultXdegree - moveLegX; i--) {
    leg[0].write(i);
    delay(15);
  }

  //senkt und belastet den Fuß
  leg[1].write(defaultXdegree);
  leg[2].write(defaultXdegree);
  delay(50);

// Bewegt Bein nach hinten
  for (int i = defaultXdegree - moveLegX; i < defaultXdegree; i++) {
    leg[0].write(i);
//    legs[0][0].write(defaultXdegree-abs(defaultXdegree-i));  //?????
    delay(15);
  }
// entlastet das Bein
  leg[1].write(defaultXdegree - defaultKneeDegree);
  leg[2].write(defaultXdegree - defaultKneeDegree);
}

void leftMidLegForward(Servo leg[], int liftFootdegree) {         // Mitte Links nach Vorn 
  leftFrontLegForward(leg, liftFootdegree);
}



void leftBackLegForward(Servo leg[], int liftFootdegree) {
  leg[1].write(defaultXdegree + defaultKneeDegree + liftFootdegree+30);
  leg[2].write(defaultXdegree + defaultKneeDegree + liftFootdegree+30);
  legs[4][1].write(defaultXdegree);
  legs[4][2].write(defaultXdegree);
  delay( 200);

  for (int i = defaultXdegree + moveLegX; i > defaultXdegree; i--) {
    leg[0].write(i);
    delay(15);
  }
  legs[4][1].write(defaultXdegree-defaultKneeDegree);
  legs[4][2].write(defaultXdegree-defaultKneeDegree);
  leg[1].write(defaultXdegree);
  leg[2].write(defaultXdegree);
  delay(50);

  for (int i = defaultXdegree; i < defaultXdegree + moveLegX; i++) {
    leg[0].write(i);
    delay(15);  
  }
  leg[1].write(defaultXdegree + defaultKneeDegree );
  leg[2].write(defaultXdegree + defaultKneeDegree );
}


void rightFrontLegForward(Servo leg[], int liftFootdegree) {
  leg[1].write(defaultXdegree + defaultKneeDegree + liftFootdegree);
  leg[2].write(defaultXdegree + defaultKneeDegree + liftFootdegree);
  delay(50);

  for (int i = defaultXdegree; i < defaultXdegree + moveLegX; i++) {
    leg[0].write(i);
    delay(15);  
  }
  
  leg[1].write(defaultXdegree);
  leg[2].write(defaultXdegree);
  delay(50);

  for (int i = defaultXdegree + moveLegX; i > defaultXdegree; i--) {
    leg[0].write(i);
    //legs[5][0].write(defaultXdegree+abs(defaultXdegree-i));//???
    delay(15);
  }

  leg[1].write(defaultXdegree + defaultKneeDegree);
  leg[2].write(defaultXdegree + defaultKneeDegree);
}

void rightMidLegForward(Servo leg[], int liftFootdegree) {
  rightFrontLegForward(leg, liftFootdegree);
}

void rightBackLegForward(Servo leg[], int liftFootdegree) {
  leg[1].write(defaultXdegree - defaultKneeDegree - liftFootdegree-30);
  leg[2].write(defaultXdegree - defaultKneeDegree - liftFootdegree-30);
  legs[1][1].write(defaultXdegree);
  legs[1][2].write(defaultXdegree);
  delay( 200);

  for (int i = defaultXdegree; i < defaultXdegree + moveLegX; i++) {
    leg[0].write(i);
    delay(15);  
  }
  legs[1][1].write(defaultXdegree+defaultKneeDegree);
  legs[1][2].write(defaultXdegree+defaultKneeDegree);  
  leg[1].write(defaultXdegree - defaultKneeDegree);
  leg[2].write(defaultXdegree - defaultKneeDegree);
  delay(50);

  for (int i = defaultXdegree + moveLegX; i > defaultXdegree; i--) {
    leg[0].write(i);
    delay(15);
  }  
  leg[1].write(defaultXdegree - defaultKneeDegree);
  leg[2].write(defaultXdegree - defaultKneeDegree);
}

void loop() {
  //Serial.println(hcsr04.distanceInMillimeters());
  int liftFootdegree = 30;
  rightFrontLegForward(legs[0], liftFootdegree);
  leftFrontLegForward(legs[5], liftFootdegree);
  rightMidLegForward(legs[1], liftFootdegree);
  leftMidLegForward(legs[4], liftFootdegree);
  rightBackLegForward(legs[2], liftFootdegree);
  leftBackLegForward(legs[3], liftFootdegree);

}
