import serial    # pip install pyserial
import sys

def readValue(serialPort):
  return ord(serialPort.read(1))

def plotValue(value):
  leadingSpaces = " " * (int)(value * (SCREEN_WIDTH-3) / 255)
  print("%s%3i" % (leadingSpaces, value))

def cheapScope(serialPort):
  while(1):
    newValue = readValue(serialPort)
    plotValue(newValue)

if __name__ == "__main__":
  
  PORT         = '/dev/tty.usbmodem2101'
  BAUDRATE     = 9600
  TIMEOUT      = None
  SCREEN_WIDTH = 80

  ## Take command-line arguments to override defaults above
  if len(sys.argv) == 3:
    port = sys.argv[1]
    baudrate = int(sys.argv[2])
  else:
    print("Optional arguments port, baudrate set to defaults.")
    port, baudrate = (PORT, BAUDRATE)

  serialPort = serial.Serial(port, baudrate, timeout=TIMEOUT)
  serialPort.flush()
  cheapScope(serialPort)