<h1 align="center">
<img alt="Access-RID" src="https://raw.githubusercontent.com/aragonxpd154/access-rid/main/images/ACCESS-RID_free-file.png"/>
<br>
</h1>

<h4 align="center">

This is a prototype project made to run on Arduino Uno together with an Ethernet Shield W5100, it performs status monitoring through digital inputs and Arduino calls and the respective values are updated and sent to the device's local page in real time. The same project would include a matrix of numbers that would be typed and, if correct, the device password would unlock the web page developed below.

</h4>

<p align="center">
<img alt="Github top language" src="https://img.shields.io/github/languages/top/aragonxpd154/access-rid">
<img alt="Github laguage count" src="https://img.shields.io/github/languages/count/aragonxpd154/access-rid">
<img alt="Repository size" src="https://img.shields.io/github/repo-size/aragonxpd154/access-rid">
<img alt="Github last commit" src="https://img.shields.io/github/last-commit/aragonxpd154/access-rid">
<a href="https://github.com/aragonxpd154/access-rid/issues">
<img alt="Repository issues" src="https://img.shields.io/github/issues/aragonxpd154/access-rid"> </a>
<img alt="Github license" src="https://img.shields.io/github/license/aragonxpd154/access-rid">
</a>
</p>

<p align="center">
<a href="#rocket-technologies">Technologies</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
<a href="#information_source">How To Use</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
<a href="#status">Development Status</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
<a href="#memo-license">License</a>
</p>

<p align="center">
<img alt="Demo on Photo" src="https://github.com/aragonxpd154/access-rid/blob/main/images/5d114e8e1c.gif">
</p>

## :rocket: Technologies

This project was used with the following technologies:

- [CodeBlocks](https://www.codeblocks.org/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [ArduinoIDE](https://www.arduino.cc/)
- [W3layout](http://w3layouts.com)
- [Bootstrap v3.3.5](http://getbootstrap.com)
- [Google FontsAPI](https://fonts.googleapis.com/css?family=Roboto:400,100,100italic,300,300italic,400italic,500,500italic,700,700italic,900,900italic)
- [Font Awesome 4.6.3 by @davegandy](http://fontawesome.io)
- [jQuery v2.0.3](https://jquery.com/)
- [Raphaël 2.0.1 - JavaScript Vector Library](https://cdn.jsdelivr.net/gh/aragonxpd154/rid-pro@master/js/raphael-min.js)
- [Morris - Olly Smith](https://cdn.jsdelivr.net/gh/aragonxpd154/rid-pro@master/js/morris.js)

The following development boards were used:

- [ArduinoUno](https://www.arduino.cc/)
- [Arduino Ethernet Shield](https://www.mouser.com/catalog/specsheets/a000056_datasheet.pdf)

## :information_source: How To Use

To clone and download all project directories you can use [Git](https://git-scm.com), or any other specific program.

To clone the current directory use the command:

```bash
# Clone this repository
$ git clone https://github.com/aragonxpd154/access-rid
```

You can open the script file with the Arduino IDE and perform the recording through it. The file_arduino.ino is located at the root of this repository

<p align="center">
<img alt="Arduino IDE" src="https://github.com/aragonxpd154/access-rid/blob/main/images/arduino_ide.png" width="520" heigh="405" />
</p>

```bash
# This local repository
$ /access-rid/file_arduino.ino
```

Consult the comments of the "file_arduino.ino" for configuring your Arduino Ethernet Shield both the IP Address and MAC of the device, by default the configuration of this project is in this form:

```bash
//MAC
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xED };

// IP Address
static uint8_t ip[] = { 192, 168, 200, 150 };

```

## 💻 Development Status

The project was completed ^^. Below are some images of the project.

<p align="center">
<img alt="Demo on Photo 1" src="https://i.imgur.com/awKWLSP.png">
</p>

<p align="center">
<img alt="Demo on Photo 2" src="https://i.imgur.com/EkbyJXr.png">
</p>

## :memo: License

This project is under the GPL v3.0 license. See the [LICENSE](https://github.com/aragonxpd154/access-rid/blob/main/LICENSE) for more information.

---

Made with ♥ by Marcos (Obel) :wave: [Get in touch!](https://www.linkedin.com/in/marcosobel)
