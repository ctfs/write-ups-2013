# PicoCTF 2013: Second Contact

**Category:** Forensic
**Points:** 85
**Description:**

> As you're bumming around the Kuiper Belt, you catch an [incoming transmission](https://2013.picoctf.com/problems/kuiper.pcap) from a distant source. They seem to be scanning the area, looking for something... Maybe you should try to find it first.
>
> This trace file is also available in cloudshark [here](http://www.cloudshark.org/captures/f0741cdfee53)
>
> [Offline file](kuiper.pcap)

## Write-up

Open file with Wireshark.

Quote: *They seem to be scanning the area, looking for something...*

We will focus to search engine (Google, Bing, etc).

When Follow TCP Stream, we see `packet 1018`:

``` 
http://www.bing.com/search?q=smashing+the+stack+for+fun+and+profit&form=MOZSBR&pc=MOZI
```

They were looking for something that involved to "smashing+the+stack+for+fun+and+profit"

This is a magazine,the first things that we things is author, contents, ...

Suprising, flag is the name of author of magazine.

**Answer:** Aleph One

## Other write-ups and resources

* none yet