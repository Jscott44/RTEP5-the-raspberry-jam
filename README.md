<!-- display the social media buttons in your README -->



<!-- To Link your profile to the media buttons -->






# **The Raspberry Jam**

The realtime Raspberry PI powered digital guitar effects pedal.


<div style="float:left;margin:0 1px 1px 0" markdown="2">

![logoPicBlkStrip](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/d662a7d8-005c-4412-90bc-d30af63cd982)

</div>

# **Usage**

Ensure the Raspberry Pi is updated:

```bash
# Update package lists
sudo apt update

# Upgrade installed packages
sudo apt upgrade

# Remove unused packages
sudo apt autoremove

# Clean up package cache
sudo apt clean
```
Install Git 
```bash
# Install Git
sudo apt-get install git -y

# Verify Git installation
git --version
```
Install ALSA resources
```bash
# Install ALSA utilities and libraries
sudo apt-get install alsa-utils libasound2-dev -y

# Verify ALSA installation
aplay --version
```
Install CMake in order to build the project
```bash
# Install CMake
sudo apt-get install cmake -y

# Verify CMake installation
cmake --version
```
Clone the repository
```bash
# Clone the repository from GitHub
git clone https://github.com/Jscott44/RTEP5-the-raspberry-jam.git

# Change directory to the cloned repository
cd RTEP5-the-raspberry-jam

# List files in the repository
ls
```
For use with a generic sound card a device tree overlay needs to be created.

To make sound card master and Raspberry Pi on I2S bus (credit: https://github.com/AkiyukiOkayasu/RaspberryPi_I2S_Slave):
```bash
# Change to device tree directory
cd deviceTree

# Compile on Raspberry Pi  
dtc -@ -H epapr -O dtb -o genericstereoaudiocodec.dtbo -Wno-unit_address_vs_reg genericstereoaudiocodec.dts

# Copy i2smaster.dtbo to /boot/overlays  
sudo cp genericstereoaudiocodec.dtbo /boot/overlays

# Return to repository directory
cd ..
```

Edit /boot/config.txt   
```/boot/config.txt    # Uncomment some or all of these to enable the optional hardware interface
#dtparam=i2c_arm=on
dtparam=i2s=on
#dtparam=spi=on
dtoverlay=genericstereoaudiocodec
```
To make sound card slave and Raspberry Pi master on I2S bus (credit: https://github.com/AkiyukiOkayasu/RaspberryPi_I2S_Master):

```bash
# Compile on Raspberry Pi
# Change to device tree directory
cd deviceTree

dtc -@ -H epapr -O dtb -o i2smaster.dtbo -Wno-unit_address_vs_reg i2smaster.dts

# Copy i2smaster.dtbo to /boot/overlays  
sudo cp i2smaster.dtbo /boot/overlays

# Return to repository directory
cd ..
```

Edit /boot/config.txt  
```/boot/config.txt
# Uncomment some or all of these to enable the optional hardware interface
#dtparam=i2c_arm=on
dtparam=i2s=on
#dtparam=spi=on
dtoverlay=i2smaster
```

Bulding the project with CMake
```bash 
# Create a build directory (optional)
mkdir -p build
cd build

# Configure the build using CMake
cmake ..

# Build the project
make
```
# **Key Features**
- Realtime audio loop
- Cutsomisable effects
- User profiles
- Low cost
- Simple effect creation
- Specialised audio electronics design
![RJ_Schematic_v1 0](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/62d96636-ebfb-40e5-95e0-d459cd9fca2a)



# **Social Media Links**
[![instagram](https://github.com/shikhar1020jais1/Git-Social/blob/master/Icons/Instagram.png (Instagram))][2]
[![github](https://github.com/shikhar1020jais1/Git-Social/blob/master/Icons/Github.png (Github))][5]

[2]: https://www.instagram.com/the_raspberry_jam/ 
[5]: https://github.com/Jscott44/RTEP5-the-raspberry-jam

# **Authors**
- Jed Scott
- Dario Petinella
- Alan Hamilton
- Elad Perets
- Matthew Stewart
