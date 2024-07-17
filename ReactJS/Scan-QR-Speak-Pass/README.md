# Scan QR Speak Pass

I have made an employee card ,that contains some basic details. There is a QR at the below of the card. Scan the QR & if you are scanning it at 10 AM or between 12 Am-10 Am,you can see the message 'Welcome to work!" within an alert box. By any chance if you are late by 1 or more minutes then you can see the message "Sorry, you are late!" .<br><br>
Employee Card with QR Code and Voice Alerts<br>
Description<br>
This project implements an employee card that displays essential details about an employee along with a QR code. The QR code provides real-time feedback based on the time of scanning, accompanied by voice alerts.<br><br>

Components<br>
Avatar Section: Displays the employee's photo within a circular avatar.<br>
Employee Information:<br><br>
Name: Full name of the employee.<br>
Title: Current designation or role.<br>
ID: Unique identifier for the employee.<br>
QR Code Section: Positioned at the bottom of the card, provides real-time feedback based on the current time.<br><br>
Functionalities<br>
Time-Based Messages:<br>
Welcome Message: Displays "Welcome to work!" if the QR code is scanned at exactly 10 AM or between 12 AM to 10 AM.<br>
Late Message: Displays "Sorry, you are late!" if scanned one minute or more past 10 AM.<br>
Real-Time Feedback: Uses moment-timezone for accurate time calculations in the Asia/Kolkata timezone.<br>
Voice Alerts: Utilizes the SpeechSynthesisUtterance API to provide auditory feedback corresponding to the displayed message.<br><br>

# Here is the full video of working process



https://github.com/user-attachments/assets/0e84a536-9768-42c5-b88f-84f6f449228d

