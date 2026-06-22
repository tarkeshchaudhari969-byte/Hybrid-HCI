@echo off
cd /d "%~dp0"
call gest\Scripts\activate
cd src
python Gesture_Controller.py
pause