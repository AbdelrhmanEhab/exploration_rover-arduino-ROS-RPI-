#importing packages
from picamera import PiCamera
from time import sleep
import cv2
#loading the camera 
camera = PiCamera() 
camera.start_preview() 
print("The camera is ready!")
 
while True: 
   
        #capturing key input from user to take photo or record video             
    command = input("To take photo press p, to record video press v or x to exit: ") 

        #taking picture         
    if command == 'p':             

            #showing preview of the image you are about to shoot                             
        sleep(2)
        print("capturing image...")
        camera.capture('image.png')
        print("Image Captured!")            

    #recording video         
    elif command == 'v':             

        #showing preview of the video being recorded
        seconds = int(input("For how many seconds do you want to record"))
        camera.start_recording('video.h264')
        sleep(seconds)
        camera.stop_recording()
    elif command =='x':
        break;
        
    else:
        print("Invalid Command")
camera.stop_preview();
print("Thank you for using Picam")