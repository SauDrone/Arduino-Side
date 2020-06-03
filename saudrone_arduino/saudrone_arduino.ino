//---------------------------RC Variables-----------------------
#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2
#define CHANNEL4 3

#define YAW      0
#define PITCH    1
#define ROLL     2
#define THROTTLE 3

volatile byte previous_state[4];

volatile unsigned int pulse_length[4] = {1000, 1000, 1000, 1000};

// Used to calculate pulse duration on each channel
volatile unsigned long current_time;
volatile unsigned long timer[4]; // Timer of each channel

// Used to configure which control (yaw, pitch, roll, throttle) is on which channel
int mode_mapping[4];

void configureChannelMapping();
//---------------------------RC Variables-----------------------



//--------------------------LIDAR Variables---------------------
#include "TFMini.h"
TFMini tfmini;
unsigned long lidar_counter=0;
String lidar_distance="0000";
void lidar_scan();
String convertDistance();
//--------------------------LIDAR Variables---------------------


//--------------------------ESC Variables-----------------------
#define ESC_FL 4
#define ESC_FR 5
#define ESC_BR 6
#define ESC_BL 7

unsigned int  period = 5000; // Sampling period, 200 Hz
unsigned long loop_timer;
unsigned long now, difference;

unsigned int pulse_length_esc_fl = 1000;
unsigned int pulse_length_esc_fr = 1000;
unsigned int pulse_length_esc_br = 1000;
unsigned int pulse_length_esc_bl = 1000;

void applyMotorSpeed();
//--------------------------ESC Variables-----------------------


//--------------------------SERIAL SEND Variables --------------
void send_package();
unsigned int rc_varible_control();
//--------------------------SERIAL SEND Variables --------------


//--------------------------SERIAL READ Variables --------------
void read_package();
unsigned int serial_variable_control();
//--------------------------SERIAL READ Variables --------------


//-----------------------DEBUG------------------------
#define YES 1
#define NO 2


#define DEBUG NO0 
//-----------------------DEBUG------------------------




void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2);

  Serial1.begin(TFMINI_BAUDRATE);
  Serial1.setTimeout(5);
  tfmini.begin(&Serial1);

  configureChannelMapping();

    // Configure interrupts for receiver
    PCICR  |= (1 << PCIE0);  // Set PCIE0 to enable PCMSK0 scan
    PCMSK0 |= (1 << PCINT4); // Set PCINT0 (digital input 10) to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT5); // Set PCINT1 (digital input 11) to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT6); // Set PCINT2 (digital input 12)to trigger an interrupt on state change
    PCMSK0 |= (1 << PCINT7); // Set PCINT3 (digital input 13)to trigger an interrupt on state change

}

void loop() {
  long a=micros();
  lidar_scan();
  long b=micros();
  send_package();
  long c=micros();
  read_package();
  long d=micros();
  applyMotorSpeed();
  long e=micros();

  #if DEBUG == YES
Serial.println("");
  Serial.print(" b-- ");Serial.print(b-a);
  Serial.print(" c-- ");Serial.print(c-b);
  Serial.print(" d-- ");Serial.print(d-c);
  Serial.print(" e-- ");Serial.print(e-d);Serial.println("");
#endif
}
