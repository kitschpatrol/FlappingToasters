**Flapping Toasters**  
Developed by Michael Edgcumbe and Eric Mika in March 2011.
A final project for ITP's 3D Sensing and Visualization class.

**Interaction**  
You embody a flying toaster. Strike the psi pose to get calibrated, and then start flapping. Tilt in either direction to do a barrel roll. Clap to release toast. Supports multiple players.

**Interface**  
Tab toggles the GUI
K toggles the Kinect window
F toggle full screen mode

**Notes**  

- Uses a Kinect + OpenNI skeleton tracking to detect arm flapping.

- Built with openFrameworks 0062

- Compiled against [gameoverhack's fork of ofxOpenNI](https://github.com/gameoverhack/ofxOpenNI/commit/a1ec3ffea09bdbd644e57cc9f5c2a1c20a65f02c)

- Should work on Linux / Windows, but I haven't tested and don't have IDE project files for those platforms. Sorry.

- Inclues ofxControlPanel, which requires the ofxDirList addon.

- Xcode project file is for Xcode 4.

- Binaries are Intel-only, for Mac OS X 10.6.

- This project was renamed on github from FlyingKinectToasters to FlappingToasters on April 4th 2011.

**Problems**  

- Sometimes ofxOpenNI freezes the keyboard on my laptop. External keyboards work fine. The rest of the machine continues to work fine.

- Startup is slow. This is getting better with subsequent revisions of ofxOpenNI, but don't lose hope if it takes forever to start.

- Initial wing flapping animation is glitchy until the flap-detection system has enough data to automatically calibrate itself.

**Thanks**  
Thanks to Kyle McDonald and Zach Lieberman for creating the 3DSAV class.
More student projects here: [http://3dsav.blogspot.com/](http://3dsav.blogspot.com/)

Thanks to Wagner for the music.

Big thanks to After Dark for their brilliant and twisted screen savers (and for kindly refraining from suing us).
