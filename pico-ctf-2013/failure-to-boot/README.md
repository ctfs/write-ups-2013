# PicoCTF 2013: Failure To Boot

**Category:** Trivia
**Points:** 20
**Description:**

> After opening the robot's front panel and looking inside, you discover a small red button behind a tangle of wires. Pressing the button lights up the robot's primary screen. It glows black and quickly flashes blue. A line of small text types out:
>
> ```ERROR: 0x00000023```
>
> The text refreshes and displays the prompt:
>
> 	FILE SYSTEM RECOVERY INITIATED...
>
> 	FILE SYSTEM COULD NOT BE IDENTIFIED...
>
> 	PLEASE ENTER FILE SYSTEM FORMAT:

## Write-up

Google keyword `ERROR: 0x00000023` for several results.

And: `STOP 0x00000023 : FAT_FILE_SYSTEM` - a problem with file "Fastfat.sys".

**Answer:** FAT

## Other write-ups and resources

* none yet