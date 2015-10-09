# PicoCTF 2013: XMLOL

**Category:** WebVuln
**Points:** 30
**Description:**

> The book has instructions on how to dump the corrupted configuration file from the robot's memory. You find a corrupted [XML file](https://2013.picoctf.com/autoproblems/tmpVrg2Ah.xml) and are looking for a configuration key.
>
> [file offline](tmpVrg2Ah.xml)

## Write-up

We can view-source by `Ctrl+U`.

```xml
<super_secret_flag>534987452539085818703732732882</super_secret_flag>
```

**Answer:** 534987452539085818703732732882

## Other write-ups and resources

* none yet