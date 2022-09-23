# P10-Display
SIM7600EI Module with ESP32 and Controlling P10 Display Board.
# P10_Led_display With ESP32 DMD32 

**Communication is done between ESP32 and SIM7600EI**

> We remove U6 From Board

DMD32 Library is woring completly fine for ESP32 and P10 Display.
Click Sketch → Include Library → Manage Libraries...
[DMD32](https://github.com/Qudor-Engineer/DMD32)

PinOut>>
<ul>
<li> #define PIN_DMD_nOE		9	<br/> >> Active low Output Enable. setting this low, lights all the LEDs in the selected rows. Brightness control. </li>
  <li> #define PIN_DMD_A 13		 </li>
  <li> #define PIN_DMD_B 12		 </li>
  <li> #define PIN_DMD_CLK 18	 </li>
  <li> #define PIN_DMD_SCLK	14   </li>
  <li> #define PIN_DMD_R_DATA 23	 </li>
</ul>
<br/>

![alt text](https://github.com/Ashutoshkarve007/P10_Led_display/blob/main/Images/connector_pin_change.png)
<ul>
  >Connection on SIM7600 and ESP32
  <li> Reference for Tx Rx connection </li>
  </ul>

![alt text](https://github.com/Ashutoshkarve007/P10_Led_display/blob/main/Images/wiring%20Diagram.PNG)

# P10 with Arduino Mega and ESP32 communication with SIM7600EI
code is in linkSerial file.

P10-Display

UART Communication for IOT

Hardware :
>	SIM7600EI Module
>	ESP32


GSM/GPRS SPECIFICATION

 ![image](https://user-images.githubusercontent.com/89137956/183588287-faf94751-9f7b-4a14-9f1a-74da6637bac3.png)


PIN DIAGRAM

 ![image](https://user-images.githubusercontent.com/89137956/183588326-8967e19d-c828-4218-90df-9fb500650929.png)


K4 RMC CONNECTOR

 ![image](https://user-images.githubusercontent.com/89137956/183588347-993a6208-428e-4964-9a5d-52b1f5b0887f.png)


Getting  Started
•	Insert an unlocked Micro Sim card to SIM card holder. 8 pin holder for Micro SIM card is provided on the modem.
•	Connect  GSM Antenna to the modem.
•	Connect serial cable to the modem.
•	Give power supply in between  4.5V to 12V through the power jack provided.
•	Default factory Baud rate is 115200.
•	When the modem is successfully powered-up, the Red LED on the modem (PWR) will be ON, the STS LED(GREEN) will light after 1-2 seconds and the NET LED(BLUE) will blink every second. After the Modem registers in the network (takes between 10-60 seconds), this LED will blink in step of 3 seconds.


LED Status Description

 ![image](https://user-images.githubusercontent.com/89137956/183588374-4cf2e062-6719-42fb-82e4-b9b861230917.png)


The Network LED indicates the various status of GSM module eg. Power on, Network registration & GPRS connectivity. When the modem is powered up, this NETWORK LED will glow. After the Modem registers in the network (takes between 10-60 seconds), this LED will blink in every seconds. At this stage you can start using Modem for your application,showing that modem is registered with the network.




SIM7600EI to USB TTL Connection
SIM7600  -  USB-TTL
___________________________
PKE           -       GND
RXD           -       TXD
TXD           -       RXD
V-INT        -       3V3
GND          -       GND
VCC           -       5V
____________________________
AT Commands. 


# **P10 Display**

By- Ashutosh Karve .

**Tools and Software:**

- **SIM7600 Module (H/W)**
- **Tera Term (S/W)**
- **Aws Iot Platform (WEB)**

**Pin Out:**

**\< Sim - TTL \>**

- **Pkey – GND**
- **GND – GND**
- **Tx -- Rx**
- **Rx -- Tx**
- **Vcc -- 5V**
- **Vint – 3V**

**Tera Term:**

- **Baud Rate: 115200**

**AWS IOT Core:**

- **Create IOT Thing.**

[**https://www.hackster.io/victorffs/connecting-sim7600x-h-to-aws-using-mqtt-and-at-commands-2a693c**](https://www.hackster.io/victorffs/connecting-sim7600x-h-to-aws-using-mqtt-and-at-commands-2a693c)

**AT Commands…./**

Go through Sequence…

[https://www.waveshare.net/w/upload/6/68/SIM7500\_SIM7600\_Series\_AT\_Command\_Manual\_V2.00.pdf](https://www.waveshare.net/w/upload/6/68/SIM7500_SIM7600_Series_AT_Command_Manual_V2.00.pdf)

[https://simcom.ee/documents/SIM7600C/SIM7500\_SIM7600%20Series\_AT%20Command%20Manual\_V1.01.pdf](https://simcom.ee/documents/SIM7600C/SIM7500_SIM7600%20Series_AT%20Command%20Manual_V1.01.pdf)

[https://www.elementzonline.com/downloads/SIM7600/SIM7500\_SIM7600%20Series\_AT\_Command\_Manual%20\_V1.10.pdf](https://www.elementzonline.com/downloads/SIM7600/SIM7500_SIM7600%20Series_AT_Command_Manual%20_V1.10.pdf)

**Note \>\>**

- **Test 10 is final AT Command configuration which is working.**
- **Task 1 and Task 2 both are working fine.**

**\<TeraTerm\>**

**Test 1: Check Device is working and removed certificate**

AT

OK

AT+CCERTLIST

+CCERTLIST: "cacert.pem"

+CCERTLIST: "clientcert.pem"
 +CCERTLIST: "clientkey.pem"
 OK

AT+CCERTDELE="cacert.pem"
 OK

AT+CCERTDELE="clientcert.pem"
 OK

AT+CCERTDELE="clientkey.pem"
 OK

 at+ccertlist
 OK

at+creset
 OK
 +CPIN: READY
 SMS DONE
 PB DONE

Test Done….Working

**Test 2: Calling test**

AT
 OK

ATD919284790258;
 OK

NO CARRIER

ATD9284790258;
 OK

AT+CHUP
 OK

Test Done…Working

**Test 3: SMS Test (Check SMS and Balance and Delete SMS)**

AT+CMGD Delete message

AT
 OK

AT+CSMS=?
 +CSMS: (0-1)
 OK

AT+CSMS?
 +CSMS: 0,1,1,1
 OK

AT+CPMS=?
 +CPMS: ("ME","MT","SM","SR"),("ME","MT","SM"),("ME","SM")
 OK

AT+CMGR=1
 +CMGR: "REC READ","749045741051118097121","","22/08/09,14:05:14+22"
 Recharge of Rs. 119.0 is successful for your Jio number 9156375647Entitlement: Benefits:
 1. UNLIMITED DATA - 21 GB (1.5 GB/Day)
 2. UNLIMITED CALLS
 OK

AT+CMGD=?
 +CMGD: (0,1,2,3,4,5,6,7,8,9),(0-4)
 OK

AT+CMGD=1

OK
 AT+CMGD=2
 OK
 AT+CMGD=3
 OK
 AT+CMGD=4
 OK
 AT+CMGD=5
 OK
 AT+CMGD=6
 OK
 AT+CMGD=7
 OK
 AT+CMGD=8
 OK
 AT+CMGD=9
 OK
 AT+CMGD=0
 OK

AT+CMGD=?
 +CMGD: (),(0-4)
 OK

Test Done….Working

**Test 3: Connecting with MQTT**

**Method from the link as it is.**

[**https://www.hackster.io/victorffs/connecting-sim7600x-h-to-aws-using-mqtt-and-at-commands-2a693c**](https://www.hackster.io/victorffs/connecting-sim7600x-h-to-aws-using-mqtt-and-at-commands-2a693c)

- **Creating AWS Mqtt Account**
- **Adding Certificates to SIM7600 Device**

AT+CCERTLIST
 +CCERTLIST: "cacert.pem"
 +CCERTLIST: "clientcert.pem"
 +CCERTLIST: "clientkey.pem"
 OK

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTSSLCFG=0,0
 OK

AT+CMQTTWILLTOPIC=0,31
 \>aws/things/simcom7600\_device01/

OK
 AT+CMQTTWILLMSG=0,17,1
 \>SIMCom Connected!
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK

**+CMQTTCONNECT: 0,26 // Expected 0,0**

**Test done…..Failed.**

**Test 4: PING**

AT
 OK

AT+HTTPINIT
 OK

AT+HTTPPARA="URL",http://www.google.com
 OK

AT+HTTPACTION=0
 OK
 +HTTPACTION: 0,200,490

AT+HTTPHEAD
 +HTTPHEAD: DATA,880
 HTTP/1.0 200 OK
 Date: Wed, 17 Aug 2022 08:47:18 GMT
 Expires: -1
 Cache-Control: private, max-age=0
 Content-Type: text/html; charset=ISO-8859-1
 P3P: CP="This is not a P3P policy! See g.co/p3phelp for more info."
 Server: gws
 X-XSS-Protection: 0
 X-Frame-Options: SAMEORIGIN
 Set-Cookie: 1P\_JAR=2022-08-17-08; expires=Fri, 16-Sep-2022 08:47:18 GMT; path=/; domain=.google.com; Secure
 Set-Cookie: AEC=AakniGO7mOtQo4SpSyHrTEyC0lsdgM7IyXtVt0XNqsNmxubc5OkOMRVuNMg; expires=Mon, 13-Feb-2023 08:47:18 GMT; path=/; domain=.google.com; Secure; HttpOnly; SameSite=lax
 Set-Cookie: NID=511=OmLZ7cEnerLkdW2m3d55UAcJxWNIuQ0ZnHSbgZ\_1Wd8c6OdEmCNrsnY81b9RP3BlNVGGqMiKbEqBLCp8Kw29t2E18p07GUu00qiL-grMvpvkLHO8UJP9sqS4o-hbeETpOw2\_BA73QBwGVD4RNhUeM-Y0\_Syjt93KZEiMp105M9s; expires=Thu, 16-Feb-2023 08:47:18 GMT; path=/; domain=.google.com; HttpOnly
 Accept-Ranges: none
 Vary: Accept-Encoding

OK

AT+CDNSGIP=[www.google.com](http://www.google.com/)
 +CDNSGIP: 1,"www.google.com","142.250.183.4"
 OK

AT+CDNSGIP="a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com"
 +CDNSGIP: 1,"a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com","3.6.227.51"
 OK

Test Done….Pass.

**Test 5: Connecting to MQTT**

AT+CGMM
 SIMCOM\_SIM7600EI
 OK

AT+CRESET
 OK
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="authmode",0,2
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CPIN?
 +CPIN: READY
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+CIPMODE=?
 +CIPMODE: (0-1)
 OK

AT+CIPMODE?
 +CIPMODE: 0
 OK

AT+CIPMODE=0
 OK

AT+CIPMODE
 OK

AT+CGDCONT?
 +CGDCONT: 1,"IP","jionet","0.0.0.0",0,0,0,0
 +CGDCONT: 2,"IPV4V6","ims","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,0
 +CGDCONT: 3,"IPV4V6","SOS","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,1
 OK

AT+NETOPEN
 OK
 +NETOPEN: 0

AT+CGACT=?
 +CGACT: (0,1)
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,0
 OK

AT+CGACT=1
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,1
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+IPADDR
 +IPADDR: 25.156.15.79
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTSSLCFG=0,0
 OK

AT+CMQTTWILLTOPIC=0,31
 \>aws/things/simcom7600\_device01/
 OK

AT+CMQTTWILLMSG=0,17,1
 \>SIMCom Connected!
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK
 +CMQTTCONNECT: 0,0

Test Done…Pass

**Test 6: Send Message to Subscribed ( from sim7600 to AWS IOT Mqtt Test)**

AT+CGMM
 SIMCOM\_SIM7600EI
 OK

AT+CRESET
 OK
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="authmode",0,2
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CPIN?
 +CPIN: READY
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+CIPMODE=?
 +CIPMODE: (0-1)
 OK

AT+CIPMODE?
 +CIPMODE: 0
 OK

AT+CIPMODE=0
 OK

AT+CIPMODE
 OK

AT+CGDCONT?
 +CGDCONT: 1,"IP","jionet","0.0.0.0",0,0,0,0
 +CGDCONT: 2,"IPV4V6","ims","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,0
 +CGDCONT: 3,"IPV4V6","SOS","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,1
 OK

AT+NETOPEN
 OK
 +NETOPEN: 0

AT+CGACT=?
 +CGACT: (0,1)
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,0
 OK

AT+CGACT=1
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,1
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+IPADDR
 +IPADDR: 25.156.15.79
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTSSLCFG=0,0
 OK

AT+CMQTTWILLTOPIC=0,31
 \>aws/things/simcom7600\_device01/
 OK

AT+CMQTTWILLMSG=0,17,1
 \>SIMCom Connected!
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK
 +CMQTTCONNECT: 0,0

AT+CMQTTSUBTOPIC=0,31,1
 \>aws/things/simcom7600\_device01
 OK

AT+CMQTTSUB=0
 OK
 +CMQTTSUB: 0,0
 AT+CMQTTTOPIC=0,31
 \>aws/things/simcom7600\_device01/
 OK

AT+CMQTTPAYLOAD=0,38
 \>{"message":"Hello from SIMCom Module"}
 OK

AT+CMQTTPUB=0,1,60
 OK
 +CMQTTPUB: 0,0

Test done….Pass

**Test 7: Connecting to mqtt ( AWS IOT to SIM7600 Module)**

AT+CRESET
 OK
 +CIPEVENT: NETWORK CLOSED UNEXPECTEDLY
 +CMQTTCONNLOST: 0,3
 +CMQTTNONET
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="authmode",0,2
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CPIN?
 +CPIN: READY
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+CIPMODE=?
 +CIPMODE: (0-1)
 OK

AT+CIPMODE?
 +CIPMODE: 0
 OK

AT+CIPMODE=0
 OK

AT+CIPMODE
 OK

AT+CGDCONT?
 +CGDCONT: 1,"IP","jionet","0.0.0.0",0,0,0,0
 +CGDCONT: 2,"IPV4V6","ims","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,0
 +CGDCONT: 3,"IPV4V6","SOS","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,1
 OK

AT+NETOPEN
 OK
 +NETOPEN: 0

AT+CGACT=?
 +CGACT: (0,1)
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,0
 OK

AT+CGACT=1
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,1
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+IPADDR
 +IPADDR: 25.155.88.6
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTSSLCFG=0,0
 OK

AT+CMQTTWILLTOPIC=0,31
 \>aws/things/simcom7600\_device01/
 OK

AT+CMQTTWILLMSG=0,17,1
 \>SIMCom Connected!
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK
 +CMQTTCONNECT: 0,0

AT+CMQTTSUBTOPIC=0,31,1
 +CMQTTSUBTOPIC: 0,12
 ERROR

AT+CMQTTSUBTOPIC=0,31,1
 \>sub12345678901234567890
 OK

AT+CMQTTSUB=0
 OK
 +CMQTTSUB: 0,0

AT+CMQTTTOPIC=0,31
 \>pub123456789012345678901
 OK

AT+CMQTTPAYLOAD=0,38
 \>{"message":"Hello from SIMCom Module"}
 OK

AT+CMQTTTOPIC=0,31
 \>pub123456789012345678901
 OK

AT+CMQTTPAYLOAD=0,38
 \>{"message":"Hello from SIMCom Module"}
 OK

AT+CMQTTPUB=0,1,60
 OK
 +CMQTTPUB: 0,6
 +CMQTTCONNLOST: 0,1

Test Done….Failed

**Test 8: Check base configuration parameters settings.**

AT+CRESET
 OK
 +CIPEVENT: NETWORK CLOSED UNEXPECTEDLY
 +CMQTTNONET
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE

AT&V
 &C: 2; &D: 0; &E: 1; &F: 0; &S: 0; &W: 0; E: 1; L: 0; M: 0; Q: 0; V: 1;
 X: 1; Z: 0; \Q: 3; \S: 0; \V: 0; O: 0; S0: 0; S2: 43; S3: 13; S4: 10;
 S5: 8; S6: 2; S7: 0; S8: 2; S9: 6; S10: 14; S11: 95; S30: 0; S103: 1;
 S104: 1; +FCLASS: 0; +ICF: 3,3; +IFC: 0,0; +IPR: 115200; +DR: 0;
 +DS: 0,0,2048,6; +CMEE: 2; +WS46: 25; +CFUN:; +IPREX: 115200;
 +SSIMSTAT: 0; +CBST: 0,0,1;
 +CRLP: (61,61,48,6,0),(61,61,48,6,1),(240,240,52,6,2);
 +CV120: 1,1,1,0,0,0; +CHSN: 0,0,0,0; +CSSN: 0,0; +CREG: 0; +CGREG: 0;
 +CEREG: 0; +CSCS: "IRA"; +CSTA: 129; +CR: 0; +CRC: 0;
 +CGDCONT: (1,"IP","jionet","0.0.0.0",0,0,0,0),(2,"IPV4V6","ims","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,0),(3,"IPV4V6","SOS","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,1);
 +CGDSCONT: ; +CGTFT: ; +CGEQREQ: ; +CGEQMIN: ; +CGEQOS: ; +CGQREQ: ;
 +CGQMIN: ; +CGEREP: 0,0; +CGDATA: "PPP"; +CGCLASS: "A"; +CGPIAF: 0,0,0,0;
 +CGSMS: 1; +CSMS: 0; +CMGF: 1; +CSAS: 0; +CRES: 0; +CSCA: "",;
 +CSMP: ,,0,0; +CSDH: 0; +CSCB: 0,"",""; +ES: ,,; +ESA: 0,,,,0,0,255,;
 +CMOD: 0; +CEMODE: 1; +CVHU: 1; ; ; ; ; ; ; +CSCLK: 0; +CCUART: 0;
 +CFGRI: 0,60,120; +CUARTSD: 500; +CURCD: 0; +CUARTLOG: 0; +CUARTRM: 0;
 +CFGRIDTM: 60,120; +CATR: 0; +CNMP: 2; +CNRP: 255; +CNAOP: 2; +CNSDP: 2;
 +CNSMOD: 0; +CNLSA: 0; +CEXTEPLMN: 1; +CSQFMT: 1; +AUTOCSQ: 0,0;
 +CSQDELTA: 5; +CPSI: 0; +CMGSI: 2; +CMGRMI: 4,0; +MONI: 0; +CRUPSI: 0;
 +CRUSET: 0; +CGPS: 0,1; +CGPSMSB: 1; +CGPSINFO: 0; +CGPSINFOCFG: 0,0,0;
 +CGPSHOR: 50; +CGPSPMD: 65407; +CGPSXD: 0; +CGNSSINFO: 0;
 +CSOCKAUTH: 1,0,""; +CGAUTH: 1,0,""; ; +CIPHEAD: 1; +CIPSRIP: 1;
 +CIPCCFG: 10,0,0,1,0,0,500; +CIPENSRXGET: 0; +CIPMODE: 0;
 +CPIN: ÿÿÿÿÿÿÿÿ,ÿÿÿÿÿÿÿÿ; +CMEC: 0,0,0,0; +CIND: 0,4,1,1,0,0,1,0;
 +CMER: 0,0,0,0,0; +CGATT: 1; +CGACT(1,1),(2,1),(3,0); +CPBS: "SM";
 +CPMS: "SM","SM","SM"; +CNMI: 2,1,0,0,0; +CMMS: 0; +CCUG: 0,0,0;
 +COPS: 0,0,""; +CUSD: 0; +CAOC: 1; +CCWA: 0; +CPOL: 0,2,"",0,0,0,0;
 +CPLS: 0; +CTZR: 0; +CTZU: 0; +CLIP: 0; +COLP: 0; +CDIP: 0; +CLIR: 0;
 +CSDF: 1; +CEN: 0; +CPSMS: 0,"","","",""; +CEDRXS: 0,1,""; +CCARDMA: 0;
 +STK: 0; +CSALPHA: 0; +MORING: 0; +CWAKEUPSMSSWITCH: 0;
 +CFILTERSMSSWITCH: 0; \*CNTI: 0; ^DSCI: 0; ^MODE: 0

OK

Test Done… Okay

**Test 9: Tring to send message from AWS IOT To device(other method)**

[https://github.com/elementzonline/Arduino-Sample-Codes/blob/master/SIM7600/Sim7600\_MQTT/Sim7600\_MQTT.ino](https://github.com/elementzonline/Arduino-Sample-Codes/blob/master/SIM7600/Sim7600_MQTT/Sim7600_MQTT.ino)

AT+CRESET
 OK
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="authmode",0,2
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CPIN?
 +CPIN: READY
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+CIPMODE=?
 +CIPMODE: (0-1)
 OK

AT+CIPMODE?
 +CIPMODE: 0
 OK

AT+CIPMODE=0
 OK

AT+CIPMODE
 OK

AT+CGDCONT?
 +CGDCONT: 1,"IP","jionet","0.0.0.0",0,0,0,0
 +CGDCONT: 2,"IPV4V6","ims","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,0
 +CGDCONT: 3,"IPV4V6","SOS","0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0",0,0,0,1
 OK

AT+NETOPEN
 OK
 +NETOPEN: 0
 AT+CGACT=?
 +CGACT: (0,1)
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,0
 OK

AT+CGACT=1
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,1
 OK

AT+CREG?
 +CREG: 0,1
 OK

AT+IPADDR
 +IPADDR: 26.168.0.19
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK
 +CMQTTCONNECT: 0,0

AT+CMQTTSUBTOPIC=0,13,1
 \>led/subscribe
 OK

AT+CMQTTSUB=0,4,1,1
 \>HAII
 OK
 +CMQTTSUB: 0,6
 +CMQTTCONNLOST: 0,1
 OK

Test done… failed

**Test 10: Send and receive message AWS IOT and SIM7600**

AT+CRESET
 OK
 +CIPEVENT: NETWORK CLOSED UNEXPECTEDLY
 RDY
 +CPIN: READY
 SMS DONE
 PB DONE
 AT+CSSLCFG="sslversion",0,4"
 ERROR

AT+CSSLCFG="sslversion",0,4
 OK

AT+CSSLCFG="authmode",0,2
 OK

AT+CSSLCFG="cacert",0,"cacert.pem"
 OK

AT+CSSLCFG="clientcert",0,"clientcert.pem"
 OK

AT+CSSLCFG="clientkey",0,"clientkey.pem"
 OK

AT+CPIN?
 +CPIN: READY
 OK

AT+CIPMODE=0
 OK

AT+CIPMODE
 OK

AT+NETOPEN
 OK
 +NETOPEN: 0

AT+CGACT=1
 OK

AT+CGACT?
 +CGACT: 1,1
 +CGACT: 2,1
 +CGACT: 3,1
 OK

AT+IPADDR
 +IPADDR: 56.213.168.200
 OK

AT+CMQTTSTART
 +CMQTTSTART: 0
 OK

AT+CMQTTACCQ=0,"SIMCom\_client01",1
 OK

AT+CMQTTSSLCFG=0,0
 OK

AT+CMQTTCONNECT=0,"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883",60,1
 OK

+CMQTTCONNECT: 0,0

AT+CMQTTSUBTOPIC=0,3,1
 \>aws

OK

AT+CMQTTSUB=0
 OK
 +CMQTTSUB: 0,0

AT+CMQTTTOPIC=0,3
 \>aws
 OK

AT+CMQTTPAYLOAD=0,38
 \>{"message":"Hello from SIMCom Module"}
 OK

AT+CMQTTPUB=0,1,60
 OK
 +CMQTTPUB: 0,0
 +CMQTTRXSTART: 0,3,38
 +CMQTTRXTOPIC: 0,3

Aws
 +CMQTTRXPAYLOAD: 0,38

{"message":"Hello from SIMCom Module"}

+CMQTTRXEND: 0

+CMQTTRXSTART: 0,3,45

+CMQTTRXTOPIC: 0,3

aws

+CMQTTRXPAYLOAD: 0,45

{"message": "Hello from AWS IoT console" }

+CMQTTRXEND: 0
 +CMQTTRXSTART: 0,3,45
 +CMQTTRXTOPIC: 0,3

Testing done…. Success

**\<Programming - Arduino Ide\>**

**TASK 1: ESP32 and SIM7600 Communication**

![](RackMultipart20220819-1-cm2wq4_html_cde1ad64ae238003.png)

**To do in code \>\>**

- **Reset SIM7600**
- **Delay of 20000 Ms**
- **Open Net**
- **Set IP address**
- **Connect to internet**
- **Set SSL and Mqtt config.**
- **Create client**
- **Connect to MQTT**
- **Subscribe to Topic**
- **Create Pub**
- **Send message to mqtt**

**Functions \>\>**

- **connecting to mqtt function through SIM7600, send AT Commands through ESP32.**

void connect\_mqtt()

{

sendData("AT+CSSLCFG=\"sslversion\",0,4", 1000, DEBUG);

// delay(1000);

sendData("AT+CSSLCFG=\"authmode\",0,2", 1000, DEBUG);

// delay(1000);

sendData("AT+CSSLCFG=\"cacert\",0,\"cacert.pem\"", 1000, DEBUG);

// delay(1000);

sendData("AT+CSSLCFG=\"clientcert\",0,\"clientcert.pem\"", 1000, DEBUG);

// delay(1000);

sendData("AT+CSSLCFG=\"clientkey\",0,\"clientkey.pem\"", 1000, DEBUG);

// delay(1000);

sendData("AT+CPIN?", 1000, DEBUG); //

delay(1000);

sendData("AT+CIPMODE=0", 1000, DEBUG);

delay(1000);

sendData("AT+CIPMODE", 1000, DEBUG);

delay(1000);

sendData("AT+NETOPEN", 1000, DEBUG); //

delay(1000);

sendData("AT+CGACT=1", 1000, DEBUG); //

delay(1000);

sendData("AT+CGACT?", 1000, DEBUG); //

delay(1000);

sendData("AT+IPADDR", 1000, DEBUG); //

delay(1000);

sendData("AT+CMQTTSTART", 1000, DEBUG); //

delay(1000);

sendData("AT+CMQTTACCQ=0,\"SIMCom\_client01\",1", 1500, DEBUG); //

delay(1000);

sendData("AT+CMQTTSSLCFG=0,0", 1000, DEBUG);

delay(1000);

Serial1.println("AT+CMQTTCONNECT=0,\"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883\",60,1");

delay(5000);

sendData("AT+CMQTTSUBTOPIC=0,3,1", 2000, DEBUG);

delay(1000);

sendData("aws", 1000, DEBUG);

delay(1000);

sendData("AT+CMQTTSUB=0", 1000, DEBUG);

delay(1000);

sendData("AT+CMQTTTOPIC=0,3", 1000, DEBUG);

delay(1000);

sendData("aws", 1000, DEBUG);

delay(1000);

sendData("AT+CMQTTPAYLOAD=0,38", 1000, DEBUG);

delay(1000);

sendData("{\"message\":\"Hello from SIMCom Module\"}", 1000, DEBUG);

delay(1000);

sendData("AT+CMQTTPUB=0,1,60", 1000, DEBUG);

}

COMMUNICATION……DONE

**TASK 2: Read JSON Format for DMD32 Function.**

- Usb Serial Function is both used for sending AT commands to SIM and also reading Response from SIM Module.

void usb\_serial()

{

while (Serial1.available() \> 0)

{

Serial.write(Serial1.read());

String a = Serial1.readString();

if (a.indexOf("PAYLOAD") != -1)

{

int new1 = a.indexOf("PAYLOAD");

String neww = a.substring(new1);

int new2 = neww.indexOf('\n');

String new3 = neww.substring(new2 + 1);

// Serial.print(new3);

StaticJsonDocument\<512\> doc;

deserializeJson(doc, new3);

Data = doc["m"];

Serial.println(Data);

graphics = doc["g"];

Serial.println(graphics);

animation = doc["a"];

Serial.println(animation);

positionx = doc["x"];

Serial.println(positionx);

positiony = doc["y"];

Serial.println(positiony);

fontm = doc["f"];

Serial.println(fontm);

}

yield();

}

while (Serial.available() \> 0)

{

#ifdef MODE\_1A

int c = -1;

c = Serial.read();

if (c != '\n' && c != '\r')

{

from\_usb += (char)c;

}

else

{

if (!from\_usb.equals(""))

{

sendData(from\_usb, 0, DEBUG);

from\_usb = "";

}

}

#else

Serial1.write(Serial.read());

// Serial.print(Serial1.read());

yield();

#endif

}

}

Reading JSON Format….DONE

**TASK 3: ESP32 and P10 Displaying message**

TO DO\>\>

- Connecting ESP32 and P10\_Display
- Send Hello Message
- Check with Single display if now Working
- Check with individual Esp32 .

O/P \>\>

- DMD32 Example : dmd.demo code.
- Displaying something glitch or noise.

Test…….Failed



