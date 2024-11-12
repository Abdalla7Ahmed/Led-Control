#!/usr/bin/python

import cv2
import time
import os
import HandTrackingModule as htm
import paho.mqtt.publish as publish
import json  # Import json to handle encoding/decoding

wCam, hCam = 640, 480

cap = cv2.VideoCapture(0)
cap.set(3, wCam)
cap.set(4, hCam)


folderPath = "FingerImages"
myList = os.listdir(folderPath)
# Sort the list of file names numerically
# This assumes that the file names are in the format of "1.jpg", "2.jpg", etc.
myList = sorted(myList, key=lambda x: int(os.path.splitext(x)[0]))

# Print the sorted list (optional)
print("Sorted list:", myList)

overlayList = []

for impath in myList:
    image = cv2.imread(f'{folderPath}/{impath}')
    #print(f'{folderPath}/{impath}')
    overlayList.append(image)


print(len(overlayList))
ptime = 0 
tipsid = [4,8,12,16,20]
detector = htm.handDetector(detectionCon=0.75)
while True:

    success , img = cap.read()
    img = detector.findHands(img)
    lmList = detector.findPosition(img,draw=False)
    #print(lmList)
    fingers = []
    if len(lmList) != 0:

        # Thumb
        if lmList[tipsid[0]][1] > lmList[tipsid[0] - 1][2]:
            fingers.append(1)
        else:
            fingers.append(0)
        # 4 Fingers
        for i in range(1,5):
            if lmList[tipsid[i]][2] < lmList[tipsid[i] -2 ][2]:
                fingers.append(1)
            else:
                fingers.append(0)
            
        print(fingers)

    totalFingers = fingers.count(1)
    payload_json = json.dumps(fingers)

    publish.single("test/message",payload_json, hostname="test.mosquitto.org")
    print("Done")
    print(f"the number is {totalFingers} fingers")
    h1,w1,c1 = overlayList[totalFingers].shape
    img[0:h1,0:w1] = overlayList[totalFingers]
    
    cv2.rectangle(img, (25, 255), (170, 425), (0, 255, 0), cv2.FILLED)
    cv2.putText(img, str(totalFingers), (45, 400), cv2.FONT_HERSHEY_PLAIN,
                    10, (255, 0, 0), 25)

    ctime = time.time()
    fps = 1/(ctime - ptime)
    ptime = ctime
    cv2.putText(img,f"FPS :{int(fps)}",(400,70),cv2.FONT_HERSHEY_PLAIN,3,(255,0,0),3)

    cv2.imshow("image ",img)
    cv2.waitKey(1)

