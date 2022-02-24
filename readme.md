# ProIMU (Under Development)
### A high precision interial measurement unit with altitute and GPS support.

### Features available: 
<li>Yaw  (degrees / rad)</li>
<li>Pitch  (degrees / rad)</li>
<li>Roll   (degrees / rad)</li>
<li>Quaternions (degrees / rad)</li>
<li>Pressure (Pa / Hg)</li>
<li>Altitude </li>
<li>Temperature (C / F) </li>
<li>Longitutde </li>
<li>Lattitude </li>
<li>Raw Accelerometer, Gyroscope & Magnetometer </li>
<li>Direction (N/W/E/S) </li>
</br>

### Communication Protocols Available:

<li>CAN FD</li>
<li>RS232</li>
<li>USB</li>
<li>TCP IP Socket</li>
<li>MQTT</li>
</br>


### Project Folders:

    📁 Documentation
    📁 Firmware
    📁 Hardware
        ↳ 📁 3D Model
        ↳ 📁 assembly_outputs
        ↳ 📁 BOM
        ↳ 📁 fab_outputs
        ↳ 📁 position_file
        ↳ 📁 footprints.pretty
        ↳ 📁 kicad_proj
            ↳ 📁 ProIMU_V1
        ↳ 📁 lib_fp.pretty
    📁 Images
    📄 README.md

</br>

### Pinout of the MCU:
<img src="Images/Pinout.png">

</br>

### Communication Protocols used:

<table>
    <tr>
        <th> Protocol
        <th> Instance
        <th> Device
    </tr>
    <tr>
        <td> UART
        <td> 1
        <td> GNSS Module
    </tr>
    <tr>
        <td> 
        <td> 2
        <td> Air602 WiFi Module
    </tr>
    <tr>
        <td> 
        <td> 3
        <td> RS232 Port
    </tr>
    <tr>
        <td> I2C
        <td> 1
        <td> MPU9250, BMP280
    </tr>
    <tr>
        <td> 
        <td> 2
        <td> Battery Charger, Fuel Gauge
    </tr>
    <tr>
        <td> SDIO
        <td> 1
        <td> SD Card Module
    </tr>
    <tr>
        <td> USB 
        <td> 1
        <td> USB Port
    </tr>
</table>
</br>




