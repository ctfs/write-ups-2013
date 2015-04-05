# Hack.lu CTF 2013: ELF

**Category:** Reversing
**Points:** 400
**Author:** sqall
**Description:**

> We encountered a drunk human which had this binary file in his possession. We do not really understand the calculation which the algorithm does. And that is the problem. Can you imagine the disgrace we have to suffer, when we robots, based on logic, can not understand an algorithm? Somehow it seems that the algorithm imitates their masters and behaves …. drunk! So let us not suffer this disgrace and reverse the algorithm and get the correct solution.
> Here is your challenge: [reverse_me_766fbe758b338bd02d1bd65e14b4e5b844741308](reverse_me_766fbe758b338bd02d1bd65e14b4e5b844741308)
>
> Announcements:
> Ok I think we got it (thanks to Happy-H from Team ClevCode). Ubuntu introduced a patch to disallow ptracing of non-child processes by non-root users. This changes the calculated value. So when you use Ubuntu you should work as root. The other distributions should not be affected. Anyway, I created a VM where the executable works just fine: http://h4des.org/ELF.ova (User: elf:elf and root:root)
> 
> It seems that there are some problems with some Linux Distributions that lead to a wrong flag. The flag is printable and is written in leet-speak. We are working on a VM that works correctly with this challenge. When the VM is ready, you can download it and try again. Sorry for the inconvenience.

## Write-up

None

## Other write-ups and resources

* [https://charliex2.wordpress.com/2013/10/24/hack-lu-ctf](https://charliex2.wordpress.com/2013/10/24/hack-lu-ctf)
* [https://stratum0.org/blog/posts/2013/10/25/hack-dot-lu-2013-elf](https://stratum0.org/blog/posts/2013/10/25/hack-dot-lu-2013-elf)
* [http://blog.frizn.fr/hacklu-2013/reverse-400-elf](http://blog.frizn.fr/hacklu-2013/reverse-400-elf)
* [http://h4des.org/blog/index.php?/archives/338-hack.lu-CTF-2013-ELF-400-Making-Of.html](http://h4des.org/blog/index.php?/archives/338-hack.lu-CTF-2013-ELF-400-Making-Of.html)
* [https://github.com/sqall01/ZwoELF](https://github.com/sqall01/ZwoELF)