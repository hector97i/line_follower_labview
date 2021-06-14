#include <SPI.h>

// SPI Pins
// #define SCK 13
// #define MISO 12
// #define MOSI 11
// #define SS 10
 
// 
#define POT A5
// Enable signal w(PWM)
#define fl_pwm 3
#define fr_pwm 9
#define rl_pwm A4
#define rr_pwm A3

// Front motors directions
#define fl_1 4
#define fl_2 5
#define fr_1 6
#define fr_2 7

// Rear motors directions
#define rl_1 2 // REAR
#define rl_2 A2
#define rr_1 10
#define rr_2 11

String usartD = "";
int c = 0;
long distance = 0.0;
byte rx = 0;
byte pwm_speed = 150;

// boolean SSlast = LOW;

// //Initialize SPI slave.
// void SlaveInit(void) {

//   SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
//   // Serial.println("SPI INIT");

//   // Initialize SPI pins.
//   pinMode(SCK, INPUT);
//   pinMode(MOSI, INPUT);
//   pinMode(MISO, INPUT);
//   pinMode(SS, INPUT);

//   // Enable SPI as slave.
//   SPCR = (1 << SPE);
// }

// // SPI Transfer.
// byte SPItransfer(byte value) {

//   SPDR = value;
//   while(!(SPSR & (1<<SPIF)));
//   delay(10);
//   return SPDR;
// }

void setup()
{

	// Initialize serial for troubleshooting.
	Serial.begin(9600);

	// Initialize SPI Slave.
	// SlaveInit();
  pinMode(POT, INPUT);
  
	// Set PWM output pins.
	pinMode(fl_pwm, OUTPUT);
	pinMode(fr_pwm, OUTPUT);
	pinMode(rl_pwm, OUTPUT);
	pinMode(rr_pwm, OUTPUT);

	// Set front motors output pins.
	pinMode(fl_1, OUTPUT);
	pinMode(fl_2, OUTPUT);
	pinMode(fr_1, OUTPUT);
	pinMode(fr_2, OUTPUT);

	// Set rear motors output pins.
	pinMode(rl_1, OUTPUT);
	pinMode(rl_2, OUTPUT);
	pinMode(rr_1, OUTPUT);
	pinMode(rr_2, OUTPUT);

	// Init motor power at 0.
	analogWrite(fl_pwm, 0);
	analogWrite(fr_pwm, 0);
	analogWrite(rl_pwm, 0);
	analogWrite(rr_pwm, 0);
}

void frontLeftMotor(bool dir, bool state)
{

	if (!state)
	{
		analogWrite(fl_pwm, 0);
    digitalWrite(fl_1, LOW);
    digitalWrite(fl_2, LOW);
	}
	else
	{

		if (dir)
		{

			digitalWrite(fl_1, LOW);
			digitalWrite(fl_2, HIGH);
		}
		else
		{

			digitalWrite(fl_1, HIGH);
			digitalWrite(fl_2, LOW);
		}

		analogWrite(fl_pwm, pwm_speed);
	}
}

void frontRightMotor(bool dir, bool state)
{

	if (!state)
	{
		analogWrite(fr_pwm, 0);
    digitalWrite(fr_1, LOW);
    digitalWrite(fr_2, LOW);
	}
	else
	{

		if (dir)
		{

			digitalWrite(fr_1, HIGH);
			digitalWrite(fr_2, LOW);
		}
		else
		{

			digitalWrite(fr_1, LOW);
			digitalWrite(fr_2, HIGH);
		}

		analogWrite(fr_pwm, pwm_speed);
	}
}

void rearLeftMotor(bool dir, bool state)
{

	if (!state)
	{
		analogWrite(rl_pwm, 0);
    digitalWrite(rl_1, LOW);
    digitalWrite(rl_2, LOW);
	}
	else
	{

		if (dir)
		{

			digitalWrite(rl_1, HIGH);
			digitalWrite(rl_2, LOW);
		}
		else
		{

			digitalWrite(rl_1, LOW);
			digitalWrite(rl_2, HIGH);
		}

		analogWrite(rl_pwm, pwm_speed);
	}
}

void rearRightMotor(bool dir, bool state)
{

	if (!state)
	{
		analogWrite(rr_pwm, 0);
    digitalWrite(rr_1, LOW);
    digitalWrite(rr_2, LOW);
	}
	else
	{

		if (dir)
		{

			digitalWrite(rr_1, HIGH);
			digitalWrite(rr_2, LOW);
		}
		else
		{

			digitalWrite(rr_1, LOW);
			digitalWrite(rr_2, HIGH);
		}

		analogWrite(rr_pwm, pwm_speed);
	}
}

void wheelTest()
{

	frontLeftMotor(true, true);
	delay(1000);
	frontLeftMotor(true, false);

	frontRightMotor(true, true);
	delay(1000);
	frontRightMotor(true, false);

	rearLeftMotor(true, true);
	delay(1000);
	rearLeftMotor(true, false);

	rearRightMotor(true, true);
	delay(1000);
	rearRightMotor(true, false);

	// Opposite direction

	frontLeftMotor(false, true);
	delay(1000);
	frontLeftMotor(false, false);

	frontRightMotor(false, true);
	delay(1000);
	frontRightMotor(false, false);

	rearLeftMotor(false, true);
	delay(1000);
	rearLeftMotor(false, false);

	rearRightMotor(false, true);
	delay(1000);
	rearRightMotor(false, false);

	delay(1000);
}

// long readSensor(int id) {

//   long t = 0.0;
//   long d = 0.0;

//   if(id == 1) {

//     digitalWrite(trigger1, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigger1, LOW);

//     t = pulseIn(echo1, HIGH);

//     d = t/59;

//   }else if(id == 2) {

// //    digitalWrite(trigger2, HIGH);
// //    delayMicroseconds(10);
// //    digitalWrite(trigger2, LOW);
// //
// //    t = pulseIn(echo2, HIGH);
// //
// //    d = t/59;

//   }else return 0.0;
//   // Serial.println(d);
//   return d;
// }

// void sendSPI(long d) {

//   // Slave Enabled?
//   if (!digitalRead(SS))
//   {
//     // Yes, first time?
//     if (SSlast != LOW) {

//       // Yes, take MISO pin.
//       pinMode(MISO, OUTPUT);
//       // Serial.println("***Slave Enabled.");

//       //receive master command code
//       rx = SPItransfer(255);

//       if (rx == 97) {
//         // Acknowledge temperature.
//         rx = SPItransfer(97);

//         rx = SPItransfer(d);
//         // Serial.print("Distance: ");
//         // Serial.println(d);
//       }

//       // Update SSlast.
//       SSlast = LOW;

//     }
//   }else {

//     // No, first time?
//     if (SSlast != HIGH) {

//       // Yes, release MISO pin.
//       pinMode(MISO, INPUT);
//       // Serial.println("Slave Disabled.");

//       // Update SSlast.
//       SSlast = HIGH;
//     }
//   }
// }

void loop()
{
  pwm_speed = map(analogRead(POT), 0, 1023, 0, 255);
	// sendSPI(readSensor(1));
  // Serial.println("Speed: "+String(pwm_speed));
  // pwm_speed = 150;
	if (Serial.available())
	{

		c = Serial.read();
    
		switch (c)
		{

		case 'w':
			frontLeftMotor(true, true);
			frontRightMotor(true, true);
			rearLeftMotor(true, true);
			rearRightMotor(true, true);
			// Serial.println("FORWARD");
      Serial.print(1);
			break;

		case 'a':
			frontLeftMotor(false, true);
			frontRightMotor(true, true);
			rearLeftMotor(false, true);
			rearRightMotor(true, true);
//			Serial.println("LEFT");
      Serial.print(1);
			break;

		case 's':
			frontLeftMotor(false, true);
			frontRightMotor(false, true);
			rearLeftMotor(false, true);
			rearRightMotor(false, true);
//			Serial.println("BACK");
      Serial.print(1);
			break;

		case 'd':
			frontLeftMotor(true, true);
			frontRightMotor(false, true);
			rearLeftMotor(true, true);
			rearRightMotor(false, true);
			// Serial.println("RIGHT");
      Serial.print(1);
			break;

		case 'f':
			frontLeftMotor(false, false);
			frontRightMotor(true, false);
			rearLeftMotor(false, false);
			rearRightMotor(true, false);
			// Serial.println("STOP");
      
			break;
		}
    
	}
  analogWrite(fr_pwm, pwm_speed);
  analogWrite(fl_pwm, pwm_speed);
  analogWrite(rl_pwm, pwm_speed);
  analogWrite(rr_pwm, pwm_speed);
  delay(40);
  analogWrite(fr_pwm, 0);
  analogWrite(fl_pwm, 0);
  analogWrite(rl_pwm, 0);
  analogWrite(rr_pwm, 0);
  delay(300);
	// usartD = Serial.read();
}
