## Aim: 

The goal of this project is to create a smart monitoring system for home plants, utilizing a range of sensors to observe environmental conditions and make real-time adjustments to optimize plant health. The system aims to enhance the care of house plants by monitoring key factors such as temperature, air quality, humidity, and light intensity. This project is part of a broader initiative involving a nano matter board challenge, where innovative sensor-based solutions are explored to address environmental monitoring and automation needs.

## Nano Matter Board Challenge:

The Smart Plant Monitoring System is developed as part of a thread challenge using a nano matter board. This board offers advanced capabilities to handle multiple sensor inputs simultaneously and perform real-time data processing. The nano matter board serves as the backbone of the system, efficiently managing sensor data and coordinating various control actions.

### Sensors and Components:

#### BMP280-3.3 Atmospheric Pressure and Temperature Sensor:
Measures ambient temperature and pressure. In this project, it is used to track the temperature of the environment.

#### MICS-6814 Air Quality Sensor: 
Monitors the levels of gases such as CO2 and other pollutants, giving insights into air quality parameters around the plants.

#### DHT11 Humidity Sensor:
Measures the humidity levels of the environment, which are crucial for maintaining optimal soil moisture for the plants.

#### LDR (Light Dependent Resistor):
Measures the intensity of ambient light. A 1K ohm resistor is used as a voltage divider to convert the changing resistance into a measurable voltage signal.

#### 3-Color LED Module: 
Provides visual feedback for different environmental conditions based on sensor data.


## Working:

The system continuously monitors the environment using the sensors listed above and provides feedback and control based on specific threshold values to maintain ideal growing conditions for the plants. Here’s how each parameter is utilized:



#### Temperature Monitoring: 
When the temperature falls below a predefined value of 23°C, the system triggers the LED module to turn red, indicating that the temperature is too low and could affect plant growth.

#### Humidity Monitoring: 
The DHT11 sensor continuously monitors humidity levels. If the detected humidity exceeds a critical level of 29%, the LED module turns green, indicating that the humidity is optimal for the plants.

#### Light Intensity Control: 
The LDR measures the ambient light intensity. The LED module changes its colors based on the specific requirements of the plants or the severity of the conditions. This visual feedback helps the user take appropriate actions to improve the environment for the plants. If the ambient light intensity remains within normal levels, the system indicates stability with the blue LED.

## Actuation and Alexa Integration:



Irrigation System: The system uses real-time data analysis to avoid over-watering or under-watering, only providing irrigation when necessary based on feedback from multiple sensors.

LED Lights: Provide visual cues regarding different environmental conditions:

Red Light: Indicates low temperature.
Blue Light: Indicates normal conditions.
Green Light: Indicates optimal humidity levels.


#### Alexa Integration: 
The system is equipped to be commissioned and decommissioned Alexa, allowing users to control the irrigation system easily and efficiently.







#### Feature Utilization and System Depth: 
The project leverages multiple sensors to monitor environmental conditions, including temperature, air quality, humidity, and light intensity. It effectively utilizes the Matter protocol for device management and integration, enhancing the system’s capabilities.



#### Impact: 
The system’s real-time monitoring and visual feedback features help users maintain optimal plant conditions effortlessly. By automating irrigation and providing clear indicators of environmental factors, the project saves time, reduces water wastage, and prevents plant damage, resulting in better plant health and lower maintenance efforts.



#### Utility and Innovative Impact: 
The project introduces a creative approach by integrating a nano matter board with multi-sensor inputs and utilizing Alexa for seamless control. The use of dynamic visual feedback through the 3-color LED module and the incorporation of the Matter protocol demonstrates the board’s versatility and its applicability in building smart home solutions. This combination of features showcases a unique, scalable solution to enhance plant care automation.



### Nano Matter Integration:

The nano matter board plays a key role in processing and integrating data from all sensors. It enables multi-sensor coordination and uses its onboard capabilities to process environmental information in real-time, optimizing decision-making for irrigation and lighting adjustments. The thread challenge focuses on leveraging the board’s capabilities to build sustainable and efficient automation solutions for smart homes.



##### Video Link: 

https://www.youtube.com/shorts/x_2_6TyORtY

## Conclusion:

The Smart Plant Monitoring System integrates multiple sensors with the nano matter board to create a dynamic and responsive environment for house plants. By continuously monitoring temperature, air quality, humidity, and light intensity, the system effectively manages irrigation and provides visual cues through LED indicators. Additionally, Alexa integration enhances user control and ease of use. This project provides a practical and scalable solution to maintain plant health with minimal human intervention, promoting an eco-friendly and efficient approach to home gardening.



Project By: Udisha Dutta Chowdhury and Shriya Dugyala
