# Policy Alarm Service
This is a server that serves the simple purpose of transmitting information from our customer.io policy sold flow to the microcontroller for the Policy Alarm (POLAR) v1.

## What is POLAR?
This is POLAR
https://github.com/user-attachments/assets/f4216313-1b6a-4877-b1bf-d1899fddba35

## Why was this needed?
Arduino microcontrollers (like the WT32-ETH01 board used) are unable to act as a webserver without adding port forwarding settings. This server gets around that by exposing whether or not a policy was sold in the last 5 seconds to the web (POST on /customer), which the microcontroller GETs (on /beacon).
