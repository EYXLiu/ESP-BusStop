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

Run `make run` to startup the flask backend + create the pio `.elf` and `.bin` files  
Run `make clean` to clean up the flask backend + delete log/pid files  

# Visualize 
Requires the Wokwi Simulator extension  
Navigate to the diagram.json file, a Wokwi diagram should appear  
Click on the green run button to run  
