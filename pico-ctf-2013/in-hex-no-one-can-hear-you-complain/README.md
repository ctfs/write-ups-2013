# PicoCTF 2013: In Hex, No One Can Hear You Complain

**Category:** Forensic
**Points:** 90
**Description:**

> While flying through the outskirts of the Ripley system, you notice a distress signal from one of the outer moons. It appears a ship has crash-landed near a 16-sided pyramid. The lone survivor, a [docx file](https://2013.picoctf.com/problems/kane.docx), tells you that a malicious programmer has embedded an egg in his chest and he's afraid that it's going to hatch. He offers his assistance if you can help find the egg.
>
> [Offline file](kane.docx)

## Write-up

First, we need know, the essence of Word file  is a normal ZIP file.

We will extract it. Flag isn't difficult to see: `\word\media\key.png`

![](key.png)

**Answer:** docx_why_not_docz

## Other write-ups and resources

* none yet