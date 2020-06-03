void applyMotorSpeed() {
  // Refresh rate is 200Hz: send ESC pulses every 5000µs
  while ((now = micros()) - loop_timer < period);

  // Update loop timer
  loop_timer = now;

  /*arduino mega pin4= PG5
    arduino mega pin5= PE3
    arduino mega pin6= PH3
    arduino mega pin7= PH4
  */
  PORTG |= B00100000; //pin 4 high
  PORTE |= B00001000; //pin 5 high
  PORTH |= B00011000; //pin 6,7 high

  bool fl_flag=false, fr_flag=false, br_flag=false, bl_flag=false;

  
  // Wait until all pins #4 #5 #6 #7 are LOW
  while (!fl_flag || !fr_flag || !br_flag || !bl_flag ) {
    now        = micros();
    difference = now - loop_timer;
    /*
      fl=4
      fr=5
      br=6
      bl=7
    */

    if (difference >= pulse_length_esc_fl) {
      PORTG &= B11011111; // Set pin #4 LOW
      fl_flag = true;
    }

    if (difference >= pulse_length_esc_fr) {
      PORTE &= B11110111; // Set pin #5 LOW
      fr_flag = true;
    }

    if (difference >= pulse_length_esc_br) {
      PORTH &= B11110111; // Set pin #6 LOW
      br_flag=true;
    }

    if (difference >= pulse_length_esc_bl) {
      PORTH &= B11101111; // Set pin #7 LOW
      bl_flag=true;
    }

  }
}
