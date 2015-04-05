# Hack.lu CTF 2013: For whom the bell tolls

**Category:** Misc
**Points:** 250
**Author:** Til
**Description:**

> To be frank, the impact partying robots had on the Oktoberfest in the recent years was disastrous. While the authorities have been able to downplay all recent incidents in the press (which habitually tends to blame visitors from the U.S., Australia, Cologne, and other places, where proper beer can only be found by the initiated), they can no longer deny the problem. Several public safety and law enforcement agencies have joined forces to spoil the robot's fun. They have planned a massive crackdown on our fun-seeking robotic friends. Time and location are currently being communicated together with a passphrase. Our organization, Robots on Rampage (RoR), is determined to stop them from stopping our annual beer-tasting event. 
> A robot agent on location in Munich has dectected a transmission between timestamp 2013-10-19-20:21:42 and 2013-10-19-20:21:43. The precise beginning of the transmission is unknown. The agent was unable to decrypt the message content. Being not the smartest agent, he also disposed of the message capture. In the following we were able to determine the sender location and the Forensic Analysis Robot Team (FART) was able to retrieve the session key and a initialization vector (IV). Judging from the memory fragments FART found, our best guess is that OpenSSL's AES implementation was used in one of the better modes to encrypt the communication. As the session key length is 128bit, the long term key is most probably longer. Due to time constraints we strongly advise against trying to break it. We have less confidence in the humans' ability to design proper communication protocols and services, though. However, we need a human to attack their logic. 
> 
> We have no way to actively communicate with the server the use for coordination. However, we can give you access to one of the lawful interception wiretaps those humans build into all their equipment. A TCP connection to ctf.fluxfingers.net:1334 will give you a maximum of 60 seconds of traffic. We have also found active equipment of a human agent we can interact with. He seems to listen on ctf.fluxfingers.net:1333, but we have no idea what he does with the input, except that there is encrypted traffic.
> 
> Update:
> Sessionkey and IV can be downloaded here [bells_18e641306f5d43ed0aa02e0e534c7d1ae00a7c36.tar.bz2](bells_18e641306f5d43ed0aa02e0e534c7d1ae00a7c36.tar.bz2)
> 
> Announcements
>
> Ruby Version 1.8.7
>
> New Hints appeard! 
> RoR has determined that the human agents acts as a proxy and requests meeting place, time and password for others. We think the first message he sends serves to agree on a session key for the answer. RoR analysts have also been staring at pcaps a lot lately. We think that on port 1832 (which we can only monitor passively) we are observing a key establishment that follows the simple ISO/IEC 11770-2 Mechanism 1. However, on tcp/1333 our analysts say that marshalled Ruby DateTime objects are flying by. Not sure, why anyone would do this, but given what we see on the other port, it makes sense (in a twisted way).

## Write-up

None

## Other write-ups and resources

None