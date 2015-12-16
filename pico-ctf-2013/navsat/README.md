# PicoCTF 2013: NAVSAT

**Category:** Forensic
**Points:** 70
**Description:**

> Near the Sun, you find a malfunctioning warp beacon which is broadcasting a distress signal in a navigational channel. It looks like it's been damaged by solar radiation, and [some of its data](https://2013.picoctf.com/problems/recovery.zip) have been corrupted. If you can recover it, perhaps it will point at you to something interesting.
>
> [Offline file](recovery.zip)

## Write-up

Open with Winrar, we can see "key.txt". But extract file is error.

```
! [...]\NAVSAT\recovery.zip: The archive is corrupt
```

View file in hex:

```
00000000  3F 3F 03 04 0A 00 00 00 00 00 22 79 8E 42 F6 7D  ??........"yŽBö}
00000010  2E EF 1B 00 00 00 1B 00 00 00 0F 00 1C 00 4D 61  .ï............Ma
00000020  67 37 2D 42 57 2F 6B 65 79 2E 74 78 74 55 54 09  g7-BW/key.txtUT.
00000030  00 03 D0 FE 6A 51 0B FF 6A 51 75 78 0B 00 01 04  ..ÐþjQ.ÿjQux....
00000040  E8 03 00 00 04 E8 03 00 00 4B 65 79 3A 20 4E 65  è....è...Key: Ne
00000050  78 74 20 73 74 6F 70 20 54 61 75 20 45 72 69 64  xt stop Tau Erid
00000060  61 6E 69 0A 50 4B 03 04 14 00 00 00 08 00 27 B6  ani.PK........'¶
00000070  47 32 1B A6 C8 9C E4 52 04 00 8C 36 05 00 14 00  G2.¦ÈœäR..Œ6....
00000080  1C 00 4D 61 67 37 2D 42 57 2F 43 68 61 72 74 2D  ..Mag7-BW/Chart-
00000090  31 35 2E 70 64 66 55 54 09 00 03 BA 36 08 42 AF  15.pdfUT...º6.B¯
```

Now, contents of key.txt is display.

```
00000040  E8 03 00 00 04 E8 03 00 00 4B 65 79 3A 20 4E 65  è....è...Key: Ne
00000050  78 74 20 73 74 6F 70 20 54 61 75 20 45 72 69 64  xt stop Tau Erid
00000060  61 6E 69 0A 50 4B 03 04 14 00 00 00 08 00 27 B6  ani.PK........'¶
```

Other way, we can determine file signature ZIP is `50 4B 03 04`, `3F 3F 03 04` is corrupt signature.

We can edit 2 byte first to fix. Then, open with Winrar, extract is ok.

**Answer:** Next stop Tau Eridani

## Other write-ups and resources

* none yet