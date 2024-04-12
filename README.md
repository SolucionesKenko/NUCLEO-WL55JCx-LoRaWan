# NUCLEO-WL55JCx-LoRaWan

## Introduction

This README serves as a guide for understanding and setting up the firmware for the LoRaWan End Node Project. The project aims to monitor and control and control a smart irrigation system using LoRa and LoraWan.

- [Click here](./LoraNotes.md) to get more details about the LoRaWan Notes.

## Issues

### STM32WL RTC-Calendar Mode Issue

The LoRaWan stack for STM32 utilizes RTC in Binary Mode and for our application we need to use the BCD Mode (for calendar, timestamp). Reported Issues on ST Community:

-  [Issue 1](https://community.st.com/t5/stm32-mcus-wireless/configuring-rtc-alarm-a-in-binary-mode-on-stm32wl-for-lora/td-p/591096)
-  [Issue 2](https://community.st.com/t5/stm32-mcus-wireless/using-rtc-with-lora/td-p/630295)
-  [Issue 3](https://community.st.com/t5/stm32-mcus-wireless/bcd-calendar-and-binary-mode-mix-mode-alarm-is-not-working-in/td-p/101386)

## Requisites SW and HW

### Software

- STM32CubeMx-6.8.8
- STM32CubeIDE-1.12.0
- STM32WL MCU Package-1.3.0


### Hardware

- Nucleo-WL55JCx

## HW Installation

### Wire Diagram / Schematic

[Provide a link or detailed description of the wire diagram or schematic]

### Jumpers or Pins Selector

[Explain any jumper settings or pin configurations needed]

### Pinout Description Table 

| Pin Number | Function            | Description                  |
|------------|---------------------|------------------------------|
| 1          |                     |                              |
| 2          |                     |                              |
| ...        |                     |                              |

## FW Setup and Installation

[Instructions for setting up the firmware environment, including IDE setup, toolchain installation, etc.]

## FW Configuration & Build Flags Description

[Explain any configuration options or build flags that need to be set before building the firmware.]

## FW Build and Upload Instructions

1. Clone the repository: `git clone [repository_url]`
2. Navigate to the firmware directory: `cd firmware`
3. Build the firmware: `make`
4. Upload the firmware to the microcontroller: [Provide specific instructions or commands for uploading]

## Unit Tests and Test Coverage Instruction

This section describe how to setup your enviroment and run tests using CPPUtest on Host Machine. Target tests are not considered for the current project.

Docker and GitHub actions are used to build a CI pipeline when developer merge their working branch in to the `main` branch.

### Docker Setup

To simplify the development environment setup, you can use Docker with the provided `Dockerfile`. The `Dockerfile` sets up the necessary dependencies and tools required for the project.

##### Build Docker Image

To build the Docker image, navigate to the project's root directory and run the following command:
``` bash
    docker build -t stm32-ci-ubuntu-base:1.2 . 
```

##### Run Docker Container

Once the Docker image is built, you can run a Docker container to build and manage the project.

``` bash
docker run -it --rm -v $(pwd):/app stm32f103-ubuntu-base:1.1 /bin/sh
```

This command will start a Docker container with the project files mounted at `/app` inside the container. You can execute the available `Makefile` commands inside the Docker container.

### Running locally

If don't prefer to use Docker, you will be able to run the `Makefile` commands, just simply need to install some dependencies manually.

**Note**: this approach was tested only on Linux enviroment, this will work on MacOS but not Windows OS. 
**TODO**: run test and write a guide for setting test enviroment on Windows OS. 

1. First install required system dependencies : *autoconf*, *automake*, *lcov*

```
sudo apt install autoconf automake lcov
```

2. Run the `setup-cpputest.sh` script to install and configure cpputest.

``` bash
 chmod +x setup-cpputest.sh
```

``` bash
./setup-cpputest.sh
```
- If you want to force download of CppUTest, use ```./setup-cpputest.sh -reinstall```.
- If you want to uninstall CppUTest, use ```./setup-cpputest.sh -uninstall```.


3. Set the `CPPUTEST_ENV` enviroment variable to specify the location of cpputest

``` bash
export CPPUTEST_HOME=$(pwd)/cpputest
```
4. Now, you've completed the cpputest installation. Please refers to the **USAGE Commands** Sections 

### USAGE Commands

- Run test by running the following command
```
make test
```
or
```
make all
```

### Generate Test Coverage Report

- We can generate the test coverage report from LCOV using the following command

```
make coverage
```
You can find the generated coverage HTML files in ```Test/coverage``` directory.

## Additional Sections (Optional)
- Troubleshooting
- Contributing
- License
- Contact Information

## Troubleshooting

[Provide solutions for common issues or errors encountered during setup or usage.]

## Contributing

[Explain how others can contribute to the project, including guidelines for pull requests, coding standards, etc.]

## License

[Specify the project's license, e.g., MIT, Apache, GPL, etc.]

## Contact Information

[Provide contact information for the project maintainer or team for questions or support.]