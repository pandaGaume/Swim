# Swim Academy AI workplace.  
## Abstract
Lara device, is a swim activity tracker dedicated to measure swim performance in real time, using **IMU**, **GPS** and **WIFI/LTE** as transmission mode.  
  
This repository host all the necessary documents, code and data to explain and build the dataflow, from sensor to AI.  
  
![Data flow](https://github.com/pandaGaume/Swim/blob/master/Medias/Images/swimminganalysis.png)  

Lara device is positioned on the back of the head, with the following IMU settings  

### Detectable Acceleration
![Detectable Acceleration](./medias/images/acceleration.png)  

### Angular rate
![Angular rate](./medias/images/angularrate.png)

## Metrics
Lara has the following main Functional features  
  
### Motion  
* Type of swim
* Acceleration pattern and efficiency
* speed
* Average speed
* Distance per cycle (Amplitude)
* Frequency per cycle
* Legs Frequency
* Duration of beats
  
### Underwater and turn  
* Underwater time
* Pushing power of the wall
* Turning time* Number of breaths
  
### Respiratory
* Breathing time
* Respiratory rate
* Behavior of the head during inspiration
  
### Indexes
* Swimming index 

## Type of swim  
Type of swim is divided into 4 classes. 

* Butterfly
* Backstroke
* Breaststroke
* Crawl  

## Speed (meters per seconds)
V = d/t 
where d is the distance traveled in meters and t the time (in seconds) set to cover the distance d
Howebver, the speed MAY come from the GPS Speed (which is doopler speed in km per hours).  
The GPS receiver can be augmented with the inertial navigation system (INS) to provide better positioning information. Kalman filter may be applied to estimate information about position, velocity, and acceleration. 

### Average speed
Average speed is calculated over given distance. In open water it's configurable with a default of 100 meters.  

## Distance per cycle or Amplitude (meter)
The amplitude is the distance covered during a swimming cycle. For instance, in crawl, a swimming cycle corresponds to 2 arm actions and can be delimited by 2 successive entries of the same hand in the water.  
A = d/n  
Where d is the distance traveled in meters and n the number of cycles to cover the distance d

## Frequency per cycle (F in cycle per minute)
F = (d/n) x 60  
Using Amplitude  
V = FxA/60 so F=(V/A)x60

## Swimming index
Stroke index (In) = Velocity x Amplitude
When V = d/t and A = d/n 
In = B = d2/(t x n)
Where 
* d = distance traveled in meters, 
* n = number of cycles made to go through 
* t = corresponds to the time (sec) set to travel d
the swimming index (in m 2 / s / cycle) represents a discriminating tool of the level of practice) 


| Swimmer | Speed | Amplitude | Frequency | Index |
|---------|-------|-----------|-----------|-------|
| Level 1 | 0.77  | 1.41      | 36.8      | 1.07  |
| Level 2 | 1.03  | 1.62      | 36.8      | 1.07  |
| Level 3 | 1.28  | 2.5      | 39      | 3.3  |
| Level 4 | 1.65  | 2.78      | 38.7      | 5.31  |
| World Record | 2.09  | 3.22      | 52      | 5.81  |


## Repository content

/Readme.md This file.

### AI
This folder contains both trainning data set and models.
#### Trainning
the training sets are divided into several file.
* A csv file under the timeseries folder with all recorded values, with the following structure.  
  
| Timestamp | Fix | Lat | Lon | Alt | pAcc | Mag | Speed | sAcc | Heading | Battery | AccX | AccY | AccZ | GyrX | GyrY | GyrZ | 
|-----------|-----|-----|-----|-----|------|-----|-------|------|---------|---------|------|------|------|------|------|------|
  
* an excel file with Meta and measured metrics
* a video showing the session 


### Hardwares
All about embedded hardware necessary datasheet.  

### Media
3D files (gltf) and images.

### References
Are research papers with usefull informations.

### Sources  
Usefull c# and c code for differents operations such **sensor fusion** or **FFT**. Embedded Neural Network source code is also provided under the C/NN folder. 

### Tools
Usefull files or templates.



