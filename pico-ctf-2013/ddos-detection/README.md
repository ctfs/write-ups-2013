# PicoCTF 2013: DDoS Detection

**Category:** Forensic
**Points:** 85
**Description:**

> It appears a SYN-flood style DDoS has been carried out on this system. Send us a list of the IP addresses of the attackers (in any order, separated by spaces), so we can track them down and stop them.
> 
> Pcap available to download [here](https://2013.picoctf.com/problems/syn_attack.pcap), or available to analyse online [at CloudShark](http://www.cloudshark.org/captures/88971318a309)
>
> [offline file](syn_attack.pcap)

## Write-up

First, we have to understand what SYN attack is. Simple is attacker send many packet with flag SYN = 1 at a time, server can't respond ACK because timer is longer than sending timer, server is overload.

Open pcap with `Wireshark > Statics > Conversations`:

![](conversations.png)

=> Server (victim): 128.237.255.81

Use filter to filt all packets from attack:

```
tcp && ip.dst == 128.237.255.81 && tcp.flags.syn == 1 && tcp.flags.ack == 0
```

We can lists source IP and it's all IP of attacker.

`Statics > IP Statics (unchanged filter)`

**Answer:** 

```
121.168.84.32 75.214.206.60 21.241.212.197 55.53.190.191 71.113.17.64 120.130.138.152 171.128.49.99 104.220.68.36 241.210.41.46 33.24.97.48 115.99.66.210 154.29.81.178 69.232.82.51 234.183.31.38 102.146.88.253 196.132.138.81 63.193.172.89 16.6.74.206 94.148.118.202 160.116.210.243 248.237.9.18 161.147.211.153 207.137.67.221 229.61.253.52 180.70.211.154 132.214.137.24 132.42.241.177 65.248.11.247 49.201.237.5 51.145.58.158
```

## Other write-ups and resources

* none yet