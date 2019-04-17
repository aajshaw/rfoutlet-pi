#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

// This pin is not the first pin on the RPi GPIO header
// http://wiringpi.com/wp-content/uploads/2013/03/pins.pdf
#define OUTPUT_PIN 0

// There are 24 code bits in the on and off commands
#define CODE_LENGTH_BITS 24

// Standard pulse length seems to be 181 micro seconds, but my
// switches don't always pick up that signel so I selected a
// range to fire over
#define PULSE_LENGTH_STD 181
#define PULSE_LENGTH_MIN PULSE_LENGTH_STD - 5
#define PULSE_LENGTH_MAX PULSE_LENGTH_STD + 5

// The number of times to send the command, can be overridden from command line
#define REPEAT_SEND 5

static void send(int code, int bits, int send_count);
static void transmit(int high_pulses, int low_pulses, int pulse_length);

int main(int argc, char *argv[])
{
  int repeat = REPEAT_SEND;

  if (argc < 3)
  {
    fprintf(stderr, "missing required arguments: %s <switch id in hex> <on/off> <repeat>\n", argv[0]);
    fprintf(stderr, "<repeat> is optional\n");
    return 1;
  }

//  int switch_id = atoi(argv[1]);
  int switch_id = strtol(argv[1], NULL, 16);

  // Shunt the switch ID up by 4 bit to make room for the on/off command
  int code = switch_id << 4;

  if (strcmp(argv[2], "on") == 0)
  {
    code |= 0x3;
  }
  else
  {
    code |= 0xc;
  }

  if (argc > 3)
  {
    repeat = atoi(argv[3]);
  }

  wiringPiSetup();
  pinMode(OUTPUT_PIN, OUTPUT);
  send(code, CODE_LENGTH_BITS, repeat);
  return 0;
}

static void send(int code, int bits, int send_count)
{
  // For a range of pulse lengths...
  for (int pulse_length = PULSE_LENGTH_MIN; pulse_length <= PULSE_LENGTH_MAX; pulse_length++)
  {
    // send a sync bit
    transmit(1, 31, pulse_length);
    for (int repeat = 0; repeat < send_count; repeat++)
    {
      for (int i = bits - 1; i >= 0; i--)
      {
        int bit = (code >> i) & 1;
        switch(bit)
        {
          case 0:
            // send 1 on, 3 off
            transmit(1, 3, pulse_length);
            break;
          case 1:
            // send 3 on, 1 off
            transmit(3, 1, pulse_length);
            break;
        }
      }
      // send a sync bit
      transmit(1, 31, pulse_length);
    }
    // Pause for a while after sending
    delayMicroseconds(32 * pulse_length);
  }
}

static void transmit(int high_pulses, int low_pulses, int pulse_length)
{
  digitalWrite(OUTPUT_PIN, HIGH);
  delayMicroseconds(pulse_length * high_pulses);
  digitalWrite(OUTPUT_PIN, LOW);
  delayMicroseconds(pulse_length * low_pulses);
}
