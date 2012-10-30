package suschord.pocketrave;

import net.rim.device.api.system.AccelerometerSensor;
import net.rim.device.api.system.Application;
import processing.core.PMIDlet;

public class PocketRave extends PMIDlet {
  int white;
  AccelerometerSensor.Channel accl;
  short[] xyz = new short[3];
  
  public void setup() {
    accl = AccelerometerSensor.openRawDataChannel(Application.getApplication());
    white = color(255);
    background(white);
    framerate(30);
  }
  
  public void draw() {
    background(accelcolor());
  }
  
  public void destroy() {
    accl.close();
  }
  
  int accelcolor() {
    accl.getLastAccelerationData(xyz);
    return color(xyz[0], xyz[1], xyz[2]);
  }
}
