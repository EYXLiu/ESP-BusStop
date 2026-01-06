# Transit Display
Tech Stack: C++, Python, Flask, Make, Wokwi, Platformio, STM32, Arduino 

# Example
https://github.com/user-attachments/assets/0524eb74-d70c-49ae-836f-d0cb71b9e597

# Compile
A Go Transit API Key is required for this, set it in the `.env` file as "GOTRANSIT_KEY"  
Run the following commands to set up the virtual environment  
```
python -m venv .venv
source .venv/bin/activate
pip install requirements.txt
```
To get the MAC_IP, on macOS, run `ipconfig getifaddr en0` and that's the MAC_IP  
Run `export MAC_IP=$(ipconfig getifaddr en0)`  
Get the BUS_STOP from `localhost:8080/station` (find the LocationCode)  
Run `export BUS_STOP={bus stop ip}`  

Run `make run` to startup the flask backend + create the pio `.elf` and `.bin` files  
Run `make clean` to clean up the flask backend + delete log/pid files  

# Visualize 
Requires the Wokwi Simulator extension  
Navigate to the diagram.json file, a Wokwi diagram should appear  
Click on the green run button to run  

# Debugging
If the server doesn't shut down properly (eg. didn't clean properly after use)  
Run `lsof -i :8080` to check for servers running on port 8080  
Run `kill {pid}` to kill the process running (make sure it's the python script and not another backend project)  
