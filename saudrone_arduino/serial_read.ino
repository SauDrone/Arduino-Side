void read_package() {
  if(Serial.available()){
  String coming_text = Serial.readStringUntil('.');
  if (coming_text.length() == 16) {
    String fl = coming_text.substring(0, 4);
    pulse_length_esc_fl = serial_variable_control(fl);
    String fr = coming_text.substring(4, 8);
    pulse_length_esc_fr = serial_variable_control(fr);
    String br = coming_text.substring(8, 12);
    pulse_length_esc_br = serial_variable_control(br);
    String bl = coming_text.substring(12, 16);
    pulse_length_esc_bl = serial_variable_control(bl);
  }
}
}

unsigned int serial_variable_control(String variable) {
  int int_var = variable.toInt();
  if (int_var > 2000) {
    int_var = 2000;
  } else if (int_var < 1000) {
    int_var = 1000;
  }

  return int_var;
}
