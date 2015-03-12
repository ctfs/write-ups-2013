# CSAW Quals CTF 2015: Networking 2

**Category:** Misc
**Points:** 50
**Solves:** 864
**Description:** 

> [networking.pcap](networking.pcap)
> 
> [networking.pcap.process](networking.pcap.process)

## Write-up

We are given the same tcpdump as [network1-50](../network1-50/):

```bash
$ diff networking.pcap ../network1-50/networking.pcap
$ [...]
```

However, we are also given a `networking.pcap.process` file, which contains the flag:

```bash
$ strings -a networking.pcap.process | sort | uniq
flag{f9b43c9e9c05be5e08ea163007af5144}.exe
flag{f9b43c9e9c05be5e08ea163007af5144}.exe

flag{f9b43c9e9c05be5e08ea163007af5144}.exe!
flag{f9b43c9e9c05be5e08ea163007af5144}.exe"
flag{f9b43c9e9c05be5e08ea163007af5144}.exe$
flag{f9b43c9e9c05be5e08ea163007af5144}.exe%
flag{f9b43c9e9c05be5e08ea163007af5144}.exe'
flag{f9b43c9e9c05be5e08ea163007af5144}.exe(
flag{f9b43c9e9c05be5e08ea163007af5144}.exe*
flag{f9b43c9e9c05be5e08ea163007af5144}.exe+
flag{f9b43c9e9c05be5e08ea163007af5144}.exe-
flag{f9b43c9e9c05be5e08ea163007af5144}.exe/
flag{f9b43c9e9c05be5e08ea163007af5144}.exe0
flag{f9b43c9e9c05be5e08ea163007af5144}.exe1
flag{f9b43c9e9c05be5e08ea163007af5144}.exe2
flag{f9b43c9e9c05be5e08ea163007af5144}.exe3
flag{f9b43c9e9c05be5e08ea163007af5144}.exe5
flag{f9b43c9e9c05be5e08ea163007af5144}.exe7
flag{f9b43c9e9c05be5e08ea163007af5144}.exe8
flag{f9b43c9e9c05be5e08ea163007af5144}.exe:
flag{f9b43c9e9c05be5e08ea163007af5144}.exe;
flag{f9b43c9e9c05be5e08ea163007af5144}.exe<
flag{f9b43c9e9c05be5e08ea163007af5144}.exe=
flag{f9b43c9e9c05be5e08ea163007af5144}.exe?
```

The flag is `flag{f9b43c9e9c05be5e08ea163007af5144}`.

## Other write-ups and resources

* none yet