import datetime                                                            # Importing datetime library to check current date and time.
import pywhatkit                                                           # Importing pywhatkit library to send messages on whatsapp.
import urllib.request                                                      # Importing url library to open thingspeak url and to fedge data.
import pyttsx3                                                             # Importing pyttsx3 library to make our assistant to speak.
import re                                                                  # Importing regex library to cut some lines from the data and to convert it into usefull information.
import time                                                                # Importing time library to give delay time when needed.
import os                                                                  # Importing os library to shut down google crome when it is not in use.
import json

engine = pyttsx3.init('sapi5')                                             # Setting up voice type, speech rate and other necessary things related to speech.
voices = engine.getProperty('voices')
rate = engine.getProperty('rate')
engine.setProperty('rate', rate-10)
engine.setProperty('voice',voices[0].id)
 
browserExe = "chrome.exe" 

def speak(audio):                                                          # Defining a speak function to make our work easy in upcoming lines of code.
    engine.say(audio)
    engine.runAndWait()

speak("Hello sir I am fire detecting assistant. Sir my task is to detect fire in the house. If in case there will be fire then I will alert you and I will also send you what's app message.") # Introduction line to be spoken.

if __name__=="__main__":

    while True:
        
        time.sleep(30)
        data = urllib.request.urlopen("https://api.thingspeak.com/channels/2357430/feeds.json?api_key=TX5VK5OYDHEVPDM9&results=2")   # Requesting for url to get open. 
        data =repr(data.read())                                                                                                    # Making the data coming from the url to read.
                                                                                                        
        
        find1 = data.find("field1", 200)                                     # Finding the field1 or sensor1 value from the raw data.
        find1 = find1 + 9  

        flame1 = data[find1:]                                                # Making the field1 value or sensor1 value to be readable.
        flamesensor1 = flame1[:1]


        now = datetime.datetime.now()                                        # Reading date and time. 
        print("Today's Date and Time:" + now.strftime("%y-%m-%d %H:%M:%S"))  # Printing today's date and time.
        hour = now.strftime("%H")                                            # Fetching hours value from date and time.
        minutes = now.strftime("%M")                                         # Fetching minutes value.
        min2 = int(minutes) + 2                                              # Adding 2 in minutes value.
        # time.sleep(2)        

        print("Flame sensor 1 value : " + flamesensor1)                        # Printing sensor value 1. 
        
        if int(flamesensor1) == 1:         # Checking sensor's value if sensor 1 value is 0 then it will execute the following lines.    
            speak("Danger. danger. Sir its your fire detecting assistant speaking. Sir I have detected fire in the house. I am sending you details on your whatsapp number.\n")                                                                       # It will first speak this line.
            time.sleep(1)
            pywhatkit.sendwhatmsg("+919477497343","Hello my I am your fire detecting assistant speaking. I have detected fire at your home. Please call Fire Fighters. Number of fire fighters is :- 101 and please also call your neighbours so that they can have a look what is going on.\n ", int(hour) , int(min2)) # Now our assistant will send the given message to the specified number.
            time.sleep(5)
         