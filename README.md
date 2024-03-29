# HukyAutomation


This is my approach on automating the Huky 500 Roaster using Artisan Software, VINT-Hardware from Phidgets and some selfmade electrics, based on an ATtiny85.
All necessary files can be found in this repository.

My goal was to automate the Huky as much as possible, but with as little effort as necessary.
Since - for the Huky - the fan has very high impact on ET and therefore BT, this was my starting point.
Furthermore it is quite tricky to change the gas stove's needle valve for a proportional control valve or to automate the installed one - which i also tried.

First i switched the Huky's original AC fan for a powerfull 12V DC fan.
To be more precise, i chose the [Noctua NF-A14 industrialPPC-3000 PWM](https://noctua.at/en/nf-a14-industrialppc-3000-pwm).
I then 3d-printed two adapter-rings to mount the fan to the original vent-bowl.
This fan (like many others) has a separate PWM-Line, which is essential for my further setup.

![enter image description here](http://up.picr.de/32625522el.jpg)

I wanted to controll the fan via Artisan besides the possibility to record the ET and BT.
Since version 1.2 Artisan [supports the new VINT-Phidgets](https://artisan-roasterscope.blogspot.de/2017/12/more-phidgets.html), which draw my attention to the [HUB0000](https://www.phidgets.com/?tier=3&catid=2&pcid=1&prodid=643) and the means to connect one Phidget for each of my needs.
In my case this was the [TMP1101](https://www.phidgets.com/?tier=3&catid=14&pcid=12&prodid=726) for temperature readings and the [OUT1000](https://www.phidgets.com/?tier=3&catid=2&pcid=1&prodid=711) for controlling the fan.

![enter image description here](http://up.picr.de/32625524su.jpg)

So, till here i was - technically - capable of displaying temperature readings in Artisan and controlling an output voltage of 0 - 4.2V utilizing Artisan's buttons and sliders.
I will outline the corresponding setup in Artisan (which is btw very simple) at the end of this article.

Next step was to convert the outputted voltage to a 5V PWM-Signal @ 20KHz.
The 20KHz are mandatorry for the fan's internal PWM-Controller to work (see [Intel's specs on 4-wire pwm controlled fans](http://www.formfactors.org/developer%5Cspecs%5Crev1_2_public.pdf)  for more information).

I did some research and it appeared to me, the simplest option available would be, to built a little circuit around an ATtiny85 MCU. 
My circuit reads the incoming voltage and converts it to the required PWM-Signal.
Furthermore it powers the 12V fan. The MCU itself is powered by 5V from 7805 IC, which is sourced by the same 12V as the fan.
I'm not an electrician and this is virtually my first self-made circuit - hence kept very simple and stripped-down.

![enter image description here](https://up.picr.de/40870494lu.jpeg)

![enter image description here](https://up.picr.de/36542459hq.jpg)

![enter image description here](https://up.picr.de/37553748ij.jpg)

The final step was to configure Artisan to read the temperature recordings and to control the fan.
This is easily done by selecting the `TMP1101` under `Extras >> Devices >> ET/BT` and by creating a slider with the following settings. 

![enter image description here](https://up.picr.de/32631776co.jpeg)

As `Action` i chose `VOUT Command` and `Command` is `out(n,{})`, with 'n' = channel '0' (in my case). `Factor` is set to `0.042`, since the maximum output is 100 * 0.042 = 4.2 Volts.

I also created a bunch of buttons to set the slider to some pre-configured values, e.g. Off, 60%, 80%, 100% (this range works quite well for me). Syntax is the same as for the slider.

![enter image description here](https://up.picr.de/32631777ji.jpeg)

As said before, the fan and therefore convection has a high impact on the Huky's ET.
The above setup can therefore easily be used with Artisan's software PID to hold a certain temperature, e.g. for warming up the whole roaster or in between roasts.

For those interested and german-speaking, [this](https://roboternetz.de/community/threads/71926-Einfache-ATtiny-basierte-spannungsgesteuerte-L%C3%BCfter-Regelung) is the topic in german "Roboternetz", where the circuit was planned. Many thanks to those people over there, who helped me a lot!
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE4MzkwMDMzNzUsMzk0NTEwMTI3LC0xOT
Q1MzU3MTQ4LC0yMDM2ODYzMTgwLC0zMjUzNjU5NDQsNDM4NDM4
NzQ2LC00NjI4NDUwMTldfQ==
-->
