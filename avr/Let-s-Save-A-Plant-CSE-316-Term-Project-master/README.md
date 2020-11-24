#Let's Save A Plant CSE-316-Term-Project

The main aim  of this project is to automate the process of watering a plant whenever it needs watering by measuring the soil moisture of the plant.




     We measured moisture of the soil of the plant by a soil moisture     sensor. Using ADC, the ATMega32 micro-controller converts the input from the sensor into a digital value. We then use an equation to convert thus value to show percentage moisture level in AVR 	code. While coding, a threshold percentage level is set. Whenever 	the percentage moisture of soil falls below the threshold which is set, the watering system starts working. A piezo buzzer starts  buzzing and a red LED starts blinking and flow of water starts towards the plant. Flow of water increases the moisture of the soil. After crossing the threshold percentage moisture, the micro-controller signals the watering system to stop watering. The watering system works  through a 12v DC motor.  
	


Here’s the project video. 
https://youtu.be/ATzfSjtFCaI

Here's the full report of the project.
https://drive.google.com/file/d/1n1g5utzxyTQevRQjtOjWim-8lMAH3gsH/view?usp=sharing


			



Software Requirements:
Atmel Studio 7 ( to compiler .c code and build .hex file )
progISP Burner ( to load .hex file onto ATmega32 )
Proteus 8 Professional ( for circuit design )
