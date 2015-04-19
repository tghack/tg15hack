# QR Code

**100 points**

Can you find our beautiful QR code poster?

NB! No climbing or trespassing involved.

[clicky](pic.jpg).


### Write-up

We're only given a lovely picture of a tree.

Nobody uses geotag data, right?

```
exif pic.jpg
EXIF tags in 'pic.jpg' ('Intel' byte order):
--------------------+----------------------------------------------------------
Tag                 |Value
--------------------+----------------------------------------------------------
Image Width         |3264
Image Length        |2448
Manufacturer        |SAMSUNG
[...]
Latitude            |60, 47, 30
East or West Longitu|E
Longitude           |11,  5, 56
[...]
--------------------+----------------------------------------------------------
EXIF data contains a thumbnail (13482 bytes).
```

Neat!

To convert from DMS to DD, we can use [this](http://www.fcc.gov/encyclopedia/degrees-minutes-seconds-tofrom-decimal-degrees) page.

Entering these coordinates in Google maps leads us [here](https://www.google.no/maps/place/60%C2%B047'30.0%22N+11%C2%B005'56.0%22E/@60.791667,11.098889,680m/data=!3m1!1e3!4m2!3m1!1s0x0:0x0?hl=en), which is where we gently duct taped a huge QR code poster to a wall.


### How we made it

The QR code was created with `qrencode`:

`qrencode --verbose -d 300 -s 45 -l H -m 10 -o qr.png https://youtu.be/dQw4w9WgXcQ`

<a href="http://www.youtube.com/watch?feature=player_embedded&v=dQw4w9WgXcQ
" target="_blank"><img src="http://img.youtube.com/vi/dQw4w9WgXcQ/0.jpg" 
alt="rickroll" width="240" height="180" border="10" /></a>
