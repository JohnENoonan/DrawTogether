# DrawTogether
Kinect based interactive drawing app

<div align="center">
  <a href="https://vimeo.com/288469348"> <img alt="Program Demo" src="https://github.com/JohnENoonan/DrawTogether/blob/master/videoImg.jpg"/> 
</div>

## About
This project is made with the intention of being an exhibit based interactive. In it, users are given a light that is tracked by a kinect that allows them to draw to a projection. Once the drawing is finished it joins all the other drawings as they flow off and on the projected screen, allowing present and past drawings to interact with each other and create a nonlinear form of communication between visitors.

## Installation
Here are two quick renders of an example of what the installation of this piece might look like:
<div align="center">
  <img alt="Labeled sketch" src="https://i.imgur.com/Yqi5eKt.png"/>  
</div>

<div align="center">
  <img alt="sketch 2" src="https://i.imgur.com/wExSqJP.png"/>  
</div>

## Notes
This application was developed and tested on a windows system using the related libusbk drivers and therefore may not work immediatly on other machines or operating systems. 

## Issues
Current implementation is not very efficient in storing the images as they are currently stored as FBOs. If I get time to improve that will be worked on. 

