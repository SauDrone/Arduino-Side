void send_package(){
  String yaw=String(rc_varible_control(pulse_length[mode_mapping[YAW]]));
  String pitch=String(rc_varible_control(pulse_length[mode_mapping[PITCH]]));
  String roll=String(rc_varible_control(pulse_length[mode_mapping[ROLL]]));
  String throttle=String(rc_varible_control(pulse_length[mode_mapping[THROTTLE]]));
  String package=yaw+pitch+roll+throttle+lidar_distance+".";
  Serial.print(package);
}

unsigned int rc_varible_control(unsigned int variable){
  if(variable <1000){
    variable=1000;
  }else if(variable > 2000){
    variable=2000;
  }

  return variable;
}
