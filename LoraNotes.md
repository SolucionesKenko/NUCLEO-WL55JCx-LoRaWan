# LoRa LoraWan Notes

## Introduction

LoRaWAN (Long Range Wide Area Network) and LoRa (Long Range) are wireless communication technologies designed for long-range, low-power communication in Internet of Things (IoT) applications. They offer a robust and efficient way to connect devices over long distances with minimal power consumption.

## LoRa

LoRa is a modulation technique developed by Semtech Corporation. It enables long-range communication with low power consumption, making it ideal for battery-operated IoT devices. LoRa operates in the unlicensed Industrial, Scientific, and Medical (ISM) bands, such as 868 MHz in Europe, 915 MHz in North America, and 433 MHz in Asia.

### Key Features of LoRa

- **Long Range**: LoRa can transmit data over several kilometers in rural areas and hundreds of meters in urban environments.
- **Low Power Consumption**: LoRa devices can operate on battery power for several years, making them suitable for remote and energy-constrained applications.
- **Robust Communication**: LoRa uses chirp spread spectrum modulation, which provides robust communication in noisy environments and non-line-of-sight conditions.
- **Scalability**: LoRa networks can support thousands of devices with minimal infrastructure.

## LoRaWAN

LoRaWAN is a protocol stack built on top of LoRa technology, enabling secure, bi-directional communication between IoT devices and network servers. It defines the communication protocol and system architecture for LoRa-based networks.

### Components of LoRaWAN

1. **End Devices (Nodes)**: These are the IoT devices equipped with LoRa modules for communication.
2. **Gateway**: Gateways act as intermediaries between end devices and the network server. They receive data from end devices and forward it to the network server.
3. **Network Server**: The network server manages the communication between gateways and end devices. It handles tasks such as authentication, encryption, and routing.
4. **Application Server**: Application servers process and store data received from end devices. They also facilitate integration with higher-level applications and services.

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/85259f4d-f81a-4b8b-bbc8-5c80fe76ef35/2703615e-753f-4513-9a47-dc14f8451d74/Untitled.png)

Figure 1. LoRaWan Network Architecture. Retrieved from https://www.thethingsnetwork.org/docs/lorawan/architecture/architecture.png

### Key Features of LoRaWAN

- **Long Range**: LoRaWAN extends the range of LoRa by creating a scalable network infrastructure.
- **Low Power**: LoRaWAN's power-saving features enable long battery life for end devices.
- **Secure Communication**: LoRaWAN employs strong encryption and authentication mechanisms to ensure the security of data transmission.
- **Adaptive Data Rate (ADR)**: ADR optimizes data rates and transmission parameters based on the signal strength and environmental conditions, improving network efficiency.
- **Geolocation**: LoRaWAN supports geolocation services, enabling tracking and localization of end devices.
    
    LoRaWAN operates in the unlicensed ISM (Industrial, Scientific, and Medical) bands. The table below lists all the frequency plans and their common names.
    
    | Plan ID | Frequency Plan | Common Name |
    | --- | --- | --- |
    | 1 | EU863-870 | EU868 |
    | 2 | US902-928 | US915 |
    | 3 | CN779-787 | CN779 |
    | 4 | EU433 | EU433 |
    | 5 | AU915-928 | AU915 |
    | 6 | CN470-510 | CN470 |
    | 7 | AS923-1 | AS923 |
    | 8 | AS923-2 | AS923-2 |
    | 9 | AS923-3 | AS923-3 |
    | 10 | KR920-923 | KR920 |
    | 11 | IN865-867 | IN865 |
    | 12 | RU864-870 | RU864 |
    | 13 | AS923-4 | AS923-4 |

[More info.](https://www.thethingsnetwork.org/docs/lorawan/regional-parameters/)

### Basic Concepts

- **Classes of Devices**: LoRaWAN defines three classes of devices (Class A, B, and C), each with different power consumption and communication characteristics. Class A devices have the lowest power consumption but limited flexibility in communication timing, while Class C devices offer continuous receive windows but consume more power. Find more details [here](https://developerhelp.microchip.com/xwiki/bin/view/applications/lora/lorawan-end-device-types/).
- **Join Procedure**: Devices need to join a LoRaWAN network before they can communicate with it. The join procedure involves authentication and key exchange between the device and the network server. Find more details [here](https://developerhelp.microchip.com/xwiki/bin/view/applications/lora/join-types/).
- **MAC Commands**: LoRaWAN uses MAC (Media Access Control) commands to manage device communication parameters, such as data rate, transmission power, and acknowledgment settings. Find more details [here](https://www.thethingsnetwork.org/docs/lorawan/message-types/).
- **Downlink and Uplink Messages**: Communication in LoRaWAN is bi-directional, with devices sending uplink messages to the network server and receiving downlink messages in return. Find more details [here](https://www.thethingsnetwork.org/docs/lorawan/message-types/).
- **Gateway Placement**: The placement of gateways is crucial for network coverage and performance. Proper gateway placement ensures adequate signal coverage and minimizes dead zones.
- **Network Topology**: LoRaWAN networks can have various topologies, including star, mesh, and hybrid topologies, depending on the deployment requirements and infrastructure constraints.

### Security (Keys and EUI’s)

In a LoRaWAN network, several keys and identifiers are used for secure communication between devices (end nodes) and the network server. These keys and identifiers play critical roles in ensuring the integrity, confidentiality, and authenticity of the transmitted data. Here are the basic keys and identifiers commonly used in LoRaWAN:

1. **Device EUI (EUI-64)**:
    - The Device EUI (Extended Unique Identifier) is a globally unique 64-bit identifier burned into the hardware of the LoRaWAN device during manufacturing.
    - It uniquely identifies each end node within the LoRaWAN network and is used during the join process and communication with the network server.
2. **Application EUI (AppEUI- JoinEUI)**:
    - The Application EUI is a 64-bit identifier that identifies the application or device group within the LoRaWAN network.
    - It is used during the join process to authenticate the device with the network server.
3. **Application Key (AppKey)**:
    - The Application Key is a 128-bit secret key shared between the end node and the network server.
    - It is used for secure communication between the end node and the network server, including key derivation during the join process and encryption of application payloads.
4. **DevAddr**:
    - DevAddr is a 32-bit identifier assigned to each end node during the join process in a LoRaWAN network.
    - It is used for routing and identifying the end node within the network.
    - DevAddr is assigned by the network server and is unique within the network.
    - DevAddr is not globally unique like DevEUI but serves as a local identifier within the network.
5. **Network Session Key (NwkSKey)**:
    - The Network Session Key is a 128-bit session key derived during the join process in OTAA or pre-configured in ABP.
    - It is shared with the network and it is used for integrity checking and encryption of the network layer messages exchanged between the end node and the network server.
6. **Application Session Key (AppSKey)**:
    - The Application Session Key is a 128-bit session key derived during the join process in OTAA or pre-configured in ABP.
    - It is used for encryption and decryption of application payloads exchanged between the end node and the network server, ensuring confidentiality.

In summary:

- **DevEUI** is globally unique and identifies the individual end node.
- **AppEUI** groups devices under a common application or organization.
- **AppKey** is shared between the end node and the network server for secure communication.
- **DevAddr** is assigned locally within the network to identify the end node for routing purposes after ‘join’ process.
- **NwkSKey** and **AppSKey** are derived during the join process and used for securing network and application layer communications, respectively.
- **DevAddr** and **DevEUI** are both associated with individual end nodes, but they serve different purposes. DevAddr is used for local addressing and routing within the network, while DevEUI is a globally unique identifier for device identification.
- **AppEUI** is used at the application level to group devices or specify the application context, but it is not directly related to **DevAddr** or **DevEUI**.
- During the join process, **DevEUI** and **AppEUI** are used for authentication and authorization, while **DevAddr** is assigned by the network server to provide a local address for the device within the network.

Find more details [here](https://www.thethingsnetwork.org/docs/lorawan/security/).

## Conclusion

LoRa and LoRaWAN technologies offer a cost-effective and efficient solution for deploying IoT applications requiring long-range communication. With their long battery life, robust communication, and scalability, they are well-suited for a wide range of use cases, including smart cities, agriculture, asset tracking, and environmental monitoring.