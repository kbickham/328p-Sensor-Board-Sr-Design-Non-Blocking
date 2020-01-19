# 328pSensorBoard
328p non blocking code running a sensor array of 4 (MLX90614) IR sensors, 3 DHT22s, and barometer.
![First protype of sensor array](https://github.com/kbickham/328pSensorBoard/blob/master/sensorsarraysupport.jpg)


The timing on the DHTs is a little wierd...it's something like 20 usecs high for 0, and 70 usec high for 1. They can't
be queried faster than 0.5hz or they'll stop responding.I had some issues integrating the timing with my main controller
Board (The esp8266 runs an event handler for UART commms with the display, updates thingspeak via POST method, updates fans
 and heaters at 3hz, among otherthings)

This uses hardware uart to send structs (eztransfer library) to an esp8266.
The concept is that you put one sensor read command in each of the switch case "states".
Then call the function containing this "state ladder" every loop in the main program, 
using the regular non blocking approach in arudino IDE:
  if( millis() - variable  >= timeconstraint >= approach)
                        { do stuff;
                          step++
                        };
                      
Allows for the utilization of other code on the processor.
In sufficiently complex systems you really can't use the delay command in the ms range.     

On the far left in th DIP package, the 328p driving this can be seen
![Total sysem image](https://github.com/kbickham/4Dsystems8266heatsys/blob/master/PowerBControlBsensorBtop.jpg)

video of my project is here:
https://www.youtube.com/watch?v=EiXSyNlM34c
