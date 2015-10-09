# PicoCTF 2013: Yummy

**Category:** Web Vuln
**Points:** 60
**Description:**

> You want to find out the docking bay numbers for space ships that are ready to launch. Luckily for you, [the website](https://2013.picoctf.com/problems/yummy) for the docking bay ship status page doesn't seem so secure....
>
> Enter the docking bay for any of the ships that are awaiting launch.

## Write-up

`Ctrl+U` > viewsource:

```html
<div style="position: relative; width: 728px; margin: auto;">
<h1>Docking Bay Ship Status</h1>

<h2>Login Failure</h2>
<hr>
<p style="color:red">You are not authorized to view this page.</p><!-- DEBUG: Expected Cookie: "authorization=administrator"
received Cookie: "_ga=GA1.2.1340421657.1422378902; flask=.eJwNyjkOgzAQAMC_bE3hA5tdPhPtZQkhTIRMFeXvMPX84PP16-DufcA6rtsnGOfuHVZQi1xbii1WnAM3yu6WiQMGRQ4ZJrg3e2NaUNREhbzMaCqJLGsrzFSLCcL_AZb9H0I.B8D6_A.bwT7VjEnDxXR-9xfsK5u4zTJoa0; __utma=159077049.1340421657.1422378902.1424015468.1424017131.17; __utmb=159077049.2.9.1424019633889; __utmc=159077049; __utmz=159077049.1423281743.7.2.utmcsr=facebook.com|utmccn=(referral)|utmcmd=referral|utmcct=/l.php; flask2013=eyJzZXNzaW9uX2lkIjp7IiBiIjoiTWpRd09ETTRNV0kzT1dZMU5EWXpOV0ZpWkdVNVpUYzJNREJqTjJJelltRT0ifSwidGlkIjoiMzMyYWFhMjcwOTVlNDFjMjlhMWZmOWQyZDY1Y2E2ZDgifQ.B8JkeQ.mg6M1lio8B5vRGIiiJhjYIfa_rI" -->
</div>
```
Important is `Expected Cookie: "authorization=administrator"`

By a tool [edithiscookie](https://chrome.google.com/webstore/detail/editthiscookie/fngmhnnpilhplaeedifhccceomclgfbg), add cookie entry: "authorization=administrator", a list will display.

We need "the docking bay for any of the ships that are **awaiting launch**.".

**Answer:** `DX6-7` or `DX7-2` or `DX9-5` or `DX4-9`

## Other write-ups and resources

* none yet