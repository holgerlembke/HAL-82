# HAL-82

It is a widely unknown fact that before HAL 9000 was developed there was a small hand wired test system build to monitor some devices within the Saugus Ironworks factory. It was called HAL 82.

Little is known about the overall details. Fortunately some parts were rescued from a wall in the factory. Parts only consist of one IO-Modul and a small double-cased processor node. Surprisingly archologists found a surreal modern looking set of compact splicing connectors.

## Current Use

Challenge for the archaeologists was to keep the processors in an active state. So they developed a monitoring device for the museum.

![Hal 82 Vorderseite](https://github.com/holgerlembke/HAL-82/blob/main/media/hal82vorderseite.jpg?raw=true)

![Hal 82 Rückseite](https://github.com/holgerlembke/HAL-82/blob/main/media/hal82rueckseite.jpg?raw=true)

HAL-82 can

* ping hosts
* query http connections
* query tcp connections
* subscribe to mqtt topics

HAL-82 provids a status web page, a web based configuration editor and a binary visual IO-interface.

![Hal 82 Statusmeldung](https://github.com/holgerlembke/HAL-82/blob/main/media/hal82aniklein.gif?raw=true)

## jobs.txt

```
// verteilt die Bearbeitung um +-/10
random 20

// tests werden in dem Intervall ausgeführt
intervall 120

// hosts anpingbar
ping 192.168.1.7
ping 192.168.1.9
ping 8.8.8.8

// URL ohne bzw. mit Resultcodeprüfung
// apache
http http://192.168.1.7/
http http://192.168.1.7/dasisteintest 404

// syncthing server
http http://192.168.1.12:8384/

// simple connect check
// MYSQL server
tcp 192.168.1.22 3306

// mqtts müssen in dem Intervall ankommen (kein random)....
intervall 400
mqtt 192.168.1.19 alive/app23
mqtt 192.168.1.19 alive/lamp42 
```

