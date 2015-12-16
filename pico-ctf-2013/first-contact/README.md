# PicoCTF 2013: First Contact

**Category:** Network
**Points:** 40
**Description:**

> You notice that the indicator light near the robot’s antenna begins to blink. Perhaps the robot is connecting to a network? Using a wireless card and the network protocol analyzer Wireshark, you are able to create a PCAP file containing the packets sent over the network.
>
> You suspect that the robot is communicating with the crashed ship. Your goal is to find the location of the ship by inspecting the network traffic.
>
> You can perform the analysis online on [Cloudshark](http://www.cloudshark.org/captures/bc1c0a7fae2c) or you can download the [PCAP file](https://2013.picoctf.com/problems/first_contact.pcap).
>
> [file offline](first_contact.pcap)

## Write-up

Open file with Wireshark, Select a TCP packet > Follow TCP Stream:

```
AWAITING NEW LOCATION STATUS
NEW LOCATION STATUS: 302
NEW LOCATION COORDINATES: 37 14'06"N 115 48'40"W
NEW LOCATION INFO: LOCKED
NEW LOCATION UPDATE COMPLETE
NEW LOCATION UPDATE SUCCESS
```

**Answer:** ```37 14'06"N 115 48'40"W```

## Other write-ups and resources

* none yet