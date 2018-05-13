# minidox-custom
homebrew minidox keyboard driver

### How it works
The arduino running this code polls the buttons (using a [diode matrix](http://blog.komar.be/how-to-make-a-keyboard-the-matrix/)) and keeps track of their state. If a button goes from pressed to unpressed or _vise versa_, it sends the appriate keystroke to the computer. The microcontroller must support the [Keyboard Library](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/). 

However, only the left hand side runs this code. The other half of the story (ha!) is the right hand, who's serial out goes to a software serial in on the left. It spits out descriptions of what is happening to it. This isn't how I would like for it to work, but parsing its output is easier than fixing it. You see, I lost the code to it and it requires a bunch of work to upload to anyway. Now it is a black box that spits out coordinates of buttons as they are pressed and releasd. You might see the [Magic Number](http://wiki.c2.com/?MagicNumber) desity go way up in the section of code that deals with this unfortunate situation, but don't worry! We can use the old `#define THREE 3` trick if need be.

### Pictures
![The split keyboard. Aslo, gee what an ugly link](https://lh3.googleusercontent.com/TqqyvNfDozYrmk76GMwLjJWMCMYAnJOCzX3AjkooPlvmoK7fyBEbDBdQUPoFBP4JMggM2pyEG7EcrWet3GDYo4FHYkA2mKFDHp91VVaItrP2hit5AwuvUucTtLh0H9Ffy-8OkcNTrYkWs7QnFxCvsfHrHFmyitP0gihpYkamkzP2muORRWitXtuyuQGcnrTILK986-fbT5Eo5joLTpyLhU993SctoIf1HlnFRepVTz2fIBeYWIc6kOKrh-KmNqEQRrvptKEwVVbYyiTMbk-lTBwhZZyYw1KFpHqTveehLvnQZjzW9h36Mx1TpIfIKltCVqjFG_TEEeSraAGFEv4c5hCvq0-F-O8iR3JjDXyNR7C3fQE6sO3AYM4QVW1c1QN66bZ9qwBK2pXM58KvBzrT3kNYCtwOiE4aEy08P5RhxgUkRG86a4POjHMpbFtoZu8w01arRx-Jb5b_B0zXBJl2jlQ57GErjFmtkWwekfxTS8Qa72YWpA8AvUVAyCUSRExoNbKodDm6Ohy6w8z-lx0jgo41CdHSsgCi4mZQFH_pFLLKjuzP_fDNK2wYHc49U9O0H5ZhkZ75hzH4jjK2q29T0HRMXBz__xDbbaj45IE9ThOR5AIFOsozGagG3vuLbDVjdy5O9zgiu0296bNj5bN-HpXwNA7FenK4=w1012-h694-no)
