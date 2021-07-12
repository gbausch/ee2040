# Verwendung von AVR-GCC unter MPLAB X IDE

Innerhalb der MPLAB X IDE können verschiedene Compiler verwendet werden. Für die meisten ist der [XC8-Compiler](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers#tabs) für 8-Bit-Systeme von Microchip sicher die beste Wahl. Allerdings können wahlweise auch andere Compiler innerhalb der Entwicklungsumgebung genutzt werden. Dazu zählen:

- [AVR-GCC](https://gcc.gnu.org/wiki/avr-gcc)
- [IAR for AVR](https://www.iar.com/ewavr)

Im folgenden wird die Einbindung des AVR-GCC beschrieben.

## AVR-GCC für MacOS

```bash
brew install avr-gcc
```

Nach der Installation muss AVR-GCC noch in MPLAB X IDE eingebunden werden. Gehen Sie dazu in `MPLAB X IDE` --> `Preferences` und wählen den Reiter `Embedded` und `Build Tools`.

Klicken Sie auf `Add...` um eine neue Toolchain hinzuzufügen:

![Neue Toolchain hinzufügen](img/mplab_avr-gcc_macos_01.png)

Wählen Sie danach den Pfad aus, in dem sich die Toolchain befindet. Wird AVR-GCC mittels `brew install avr-gcc` installiert, befinden sich die Programme im Ordner `/usr/local/bin`. Klicken Sie anschließend auf `OK`.

![Pfadangabe für neue Toolchain](img/mplab_avr-gcc_macos_02.png)

MPLAB X IDE fügt automatisch alle entsprechenden Programme hinzu:

![Übersicht der neu hinzugefügten Toolchain](img/mplab_avr-gcc_macos_03.png)

Von nun an kann `AVR-GCC` als Toolchain ausgewählt werden.


## AVR-GCC für Linux

Tbd

## AVR-GCC für Windows

Tbd
