# Introduction

The example application shows how to use mxchip-wifi-at-driver modules at mbed and was tested on NUCLEO_F412ZG.

Until now,mxchip-wifi-at-driver module can used for *EMW3031* and *EMW3080B*.

# How to use
* Burn the latest AT firmware to *EMW3080B* or *EMW3031*
* Get the example application
* Program your board

## Burn the latest AT firmware to EMW3080B or EMW3031!
To use mxchip-wifi-at-driver module,Firstly, you should get the latest AT firmware from http://developer.mico.io/at,
then download it to EMW3080B or EMW3031.

## Get the example application!

From the command line, import the example:

```
mbed import https://github.com/MXCHIP/mbed-wifi-at-example
cd mbed-wifi-at-example
```

## Program your board(with NUCLEO_F412ZG)

1.Connect your mbed device to the compoter over USB.

2.You will find a removable device USB Mass Storage named NODE_F412ZG

3.Send mbed-wifi-at-example.bin into the device

4.Reboot your deivce,the application will excute automatically

## Troubleshooting
1. Make sure `mbed-cli` is working correctly and its version is `>1.0.0`

 ```
 mbed --version
 ```

&#8195;If not, you can update it easily:

 ```
 pip install mbed-cli --upgrade
 ```

2. If using Keil MDK, make sure you have a license installed. [MDK-Lite](http://www.keil.com/arm/mdk.asp) has a 32KB restriction on code size.
