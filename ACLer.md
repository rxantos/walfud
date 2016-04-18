# Introduction #

Grant target all permissions to everyone, or strip permissions.

You can use both command line both GUI.

For command line:
> ACLer.exe   [grant|strip]   "target1"   "target2"   ...

For GUI:
> Just drag target to the list, then click "grant" or "strip" button.

[Download](https://walfud.googlecode.com/svn/trunk/wApp/bin/ACLer.exe)

# Details #

No matter "grant" or "strip", the program will change the target's ownership to your current user.

If "grant", the target will be grant all access permissions to "everyone"(user name).

If "strip", all access permissions will be stripped except regrant permission. In this case, no one can read or write target without regrant.

# History #

1.0.0.3
> Support XPx32.

1.0.0.2
> Disable file redirection, but program may not run under XPx32.

1.0.0.1
> Can grant/strip permission to a file.