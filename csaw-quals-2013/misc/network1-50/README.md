# CSAW Quals CTF 2015: Networking 1

**Category:** Misc
**Points:** 50
**Solves:** 1004
**Description:** 

> [networking.pcap](networking.pcap)

## Write-up

We can find the flag in the tcpdump using `strings`:

```bash
$ file networking.pcap
networking.pcap: tcpdump capture file (little-endian) - version 2.4 (Ethernet, capture length 65535)
$ strings -a networking.pcap | sort | uniq

)&~
38400,38400
Login incorrect
Password: 
Ubuntu 12.04.2 LTS
XTERM
flag{d316759c281bf925d600be698a4973d5}
hockeyinjune-virtual-machine login: 
```

The flag is `flag{d316759c281bf925d600be698a4973d5}`.

## Other write-ups and resources

* none yet