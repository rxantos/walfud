# Introduction #

This program is to synchronous system time from internet. You can specify which time server you want to query or how many time you can affort to wait. It's all in easy use.

[download](http://walfud.googlecode.com/svn/trunk/wApp/bin/timeSync.exe)

# Details #

_Param:_
  * -p: "tp"	=>	time protocol by tcp;
> > "ntp"	=>	network time protocol by udp. (default)
  * -h: time server host name. seperated by backspace.
  * -i: time server ip. seperated by backspace. (unimplement)
  * -t: time out per try, in millisecond. (default is 3000 ms.)
  * -d: debug mode. In this mode, all time server hosts will be tested and NOT change your system time.

# Example #
timeSync.exe -p ntp -h india.colorado.edu time-b.nist.gov -t 300 -d