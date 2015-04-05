# Hack.lu CTF 2013: ECKA

**Category:** Crypto
**Points:** 100
**Author:** asante
**Description:**

> Hey you!
> Come over and help me, please. We discovered a strange key agreement protocol used on this server: ctf.fluxfingers.net:1330.
> They send a curve which they use later. But we think the robots are a bit UBER-cautious and do not use the curve's P. So they first exchange their public point with a technique we could not figure out. It looks like they do not need a public key for this step.
> Afterwards they use another technique to agree on a key which they ultimately use to send some encrypted password.
> 
> We need this last password to shut down the robo-factory on our way to the Oktoberfest.
> 
> Oh btw, the robots use AES-ECB for symmetric encryption.
> 
> Hint: He, we have the latest news for you. The first part of their strange key agreement was designed by the famous SHA-Robot Мир!
> For all robo hunters out there: Your quest-description was updated - check it!

## Write-up

None

## Other write-ups and resources

* [https://stratum0.org/blog/posts/2013/10/26/hack-dot-lu-2013-ecka](https://stratum0.org/blog/posts/2013/10/26/hack-dot-lu-2013-ecka)