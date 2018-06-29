#include <Wire.h>
#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
#include <Keypad\Keypad.h>

#define COL 4
#define ROW 4

char keym[COL][ROW] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' },
};

byte rowk[COL] = { 5,4,3,2 };
byte colk[ROW] = { 9,8,7,6 };

String keypress;
Keypad ksp = Keypad(makeKeymap(keym), rowk, colk, ROW, COL);

LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup()
{
	Serial.begin(9600);
	lcd.backlight();
	lcd.setCursor(0, 0);
}

void input()
{
	String in, cache;
	while (true)
	{
		cache = String(ksp.getKey());
		if (cache)
		{
			if (cache != "#" && in.length() < 16 && cache != "*")
			{
				in += cache;
			}
			else if (cache == "*" && in.length() >= 0)
			{
				in.remove(in.length() - 1);
			}
			else
			{
				keypress = in;
				Serial.println(in);
				break;
			}
		}
	}
}

void loop()
{
	input();
	char *out;
	keypress.toCharArray(out, keypress.length());
	char output[16];
	for (int  i = 0; i < 16; i++)
	{
		output[i] = out[i];
	}
	Serial.println(output);
}