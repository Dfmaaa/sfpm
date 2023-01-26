# sfm
## What does it stand for?
It stands for Simple and Free Package Manager.
## Why is it being coded?
I use an RPM based distribution. I use `dnf` and `flatpak` as my primary package managers. Both of them lock the installation command when one package is being installed. That sounds reasonable at first. Other packages shouldn't be able to delete files being used by another package that is being installed. I don't like this. I want to be able to install multiple packages at the same time. That is the only purpose of SFPM.
## Why not Python or C, why both?
Some operations are complex. Some need speed. I used the `ctypes` module to create a bridge between the two languages. 
