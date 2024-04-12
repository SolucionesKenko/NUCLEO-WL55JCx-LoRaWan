# NUCLEO-WL55JCx-LoRaWan

- [Click here](./LoraNotes.md) to get more details about the LoRaWan Notes.

## STM32WL RTC-Calendar Mode Issue
The LoRaWan stack for STM32 utilizes RTC in Binary Mode and for our application we need to use the BCD Mode (for calendar, timestamp). Reported Issues on ST Community:
-  [Issue 1](https://community.st.com/t5/stm32-mcus-wireless/configuring-rtc-alarm-a-in-binary-mode-on-stm32wl-for-lora/td-p/591096)
-  [Issue 2](https://community.st.com/t5/stm32-mcus-wireless/using-rtc-with-lora/td-p/630295)
-  [Issue 3](https://community.st.com/t5/stm32-mcus-wireless/bcd-calendar-and-binary-mode-mix-mode-alarm-is-not-working-in/td-p/101386)
