# **Hardware**
The Rasberry Jam includes a specialised audio sound card for the capture and playback of high fidelity audio. The impact of the hardware is designed to be as inaudible as possible and all of the effects are achieved digitally in software. The hardware design is modular in nature allowing the cutsomisation to suit different applications.

# **Features**
- Highly integrated stereo audio CODEC
- Sample rates: 44.1kHz, 48kHz, 96kHz or 192kHz
- Hardware or Software control
- On-board oscillator
- 1x mono audio input (guitar)
- 2x stereo outputs (speakers)
- 1x stereo output (headphones with volume control)

# **Audio Inputs and Outputs**
The current version of the sound card supports one single ended mono instrument input up to 2Vrms. 
![inputConn](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/84d42c54-0e83-4249-b260-841ee46d69e1)

The output support two single ended connectors to create a stereo speaker output with a maximum level of 1.8Vrms before amplification. 
![outConn](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/fc9cd11d-3369-43ee-b805-05c3eb2c20e4)

The output also support a headphone driver with analogue volume to control to adjust to different load impedance headphones.
- Default gain range 18dB.
- To alter gain range adjust R43, R44, R45 and R46.
- Adjust output power by altering R41 and R42.
![HPConn](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/5c115497-0540-46d4-a63c-194a685a53ec)

# **CODEC**

![cdc](https://github.com/Jscott44/RTEP5-the-raspberry-jam/assets/122903573/2c777151-9825-4673-8def-be6ddb6971c3)

<h2>CS4271 Sample Rate Truth Table</h2>

<table>
  <tr>
    <th>Resistor R49</th>
    <th>Resistor R50</th>
    <th>Resistor R10</th>
    <th>Resistor R11</th>
    <th>M1</th>
    <th>M0</th>
    <th>Sample Rate (kHz)</th>
  </tr>
  <tr>
    <td>Not Populated</td>
    <td>Not Populated</td>
    <td>Populated</td>
    <td>Populated</td>
    <td>0</td>
    <td>0</td>
    <td>44.1</td>
  </tr>
  <tr>
    <td>Not Populated</td>
    <td>Populated</td>
    <td>Populated</td>
    <td>Not Populated</td>
    <td>0</td>
    <td>1</td>
    <td>48</td>
  </tr>
  <tr>
    <td>Populated</td>
    <td>Not Populated</td>
    <td>Not Populated</td>
    <td>Populated</td>
    <td>1</td>
    <td>0</td>
    <td>96</td>
  </tr>
  <tr>
    <td>Populated</td>
    <td>Populated</td>
    <td>Not Populated</td>
    <td>Not Populated</td>
    <td>1</td>
    <td>1</td>
    <td>192</td>
  </tr>
</table>

</body>
</html>
</html>

<h2>CS4271 Audio Mode Truth Table</h2>

<table>
  <tr>
    <th>R9 </th>
    <th>R32 </th>
    <th>ADO </th>
    <th>Audio Mode</th>
  </tr>
  <tr>
    <td>Populated</td>
    <td>Not Populated</td>
    <td>1</td>
    <td>I2S</td>
  </tr>
  <tr>
    <td>Not Populated</td>
    <td>Populated</td>
    <td>0</td>
    <td>Left Justified</td>
  </tr>

  </tr>
</table>

</body>
</html>


# **Digital Audio Format**


By default the digital audio interface will operate using the I2S protocol
- MSB first (big endian)
- Signed 24-bits per channel
- 2 channels
- Interleaved channels
