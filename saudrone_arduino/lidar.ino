void lidar_scan() {
  if (lidar_counter % 10 == 0) { // ~every 50 ms
    uint16_t dist = tfmini.getDistance();
    lidar_distance = convertDistance(dist);
  }
  lidar_counter++;
}

String convertDistance(uint16_t dist) {
  String strValue = "";

  if (dist > 9999)
    dist = 9999;

  if (dist < 10) {
    strValue = "000" + String(dist);
  } else if (dist < 100) {
    strValue = "00" + String(dist);
  } else if (dist < 1000) {
    strValue = "0" + String(dist);
  } else if (dist < 10000) {
    strValue = String(dist);
  }
  return strValue;
}
