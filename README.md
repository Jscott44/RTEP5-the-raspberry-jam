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
