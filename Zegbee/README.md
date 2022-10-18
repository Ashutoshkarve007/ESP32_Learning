For End to End Device

> Co-Ordinator

+ CH : C
+ ID : 1001
+ DL : FFFF
+ MY : ENABLE

> EndPoint

+ CH : C
+ ID : 1001
+ DL : 0
+ MY : 1
+ CE : END Device

# About

* Coordinator

ZigBee networks always have a single coordinator device. This radio is responsible
for forming the network, handing out addresses, and managing the other functions
that define the network, secure it, and keep it healthy. Remember that each network must be formed by a coordinator and that you’ll never have more than one
coordinator in your network.

* Router

A router is a full-featured ZigBee node. It can join existing networks, send information, receive information, and route information. Routing means acting as a
messenger for communications between other devices that are too far apart to
convey information on their own. Routers are typically plugged into an electrical
outlet because they must be turned on all the time. A network may have multiple
router radios

* End Device

There are many situations where the hardware and full-time power of a router are
excessive for what a particular radio node needs to do. End devices are essentially
stripped-down versions of a router. They can join networks and send and receive
information, but that’s about it. They don’t act as messengers between any other
devices, so they can use less expensive hardware and can power themselves down
intermittently, saving energy by going temporarily into a nonresponsive sleep
mode. End devices always need a router or the coordinator to be their parent device.
The parent helps end devices join the network, and stores messages for them when
they are asleep. ZigBee networks may have any number of end devices. In fact, a
network can be composed of one coordinator, multiple end devices, and no routers
at all.


