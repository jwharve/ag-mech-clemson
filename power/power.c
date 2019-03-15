#include <wiringPi.h>
#include <stdio.h>

#define ON_PIN 28

int main(int argc, char * argv[])
{
//	digitalWrite(ON_PIN,LOW);

	wiringPiSetup();
	digitalWrite(ON_PIN,LOW);

	if (argc < 2)
	{
		digitalWrite(ON_PIN,LOW);
		printf("power off\n");
		return 0;
	}

	if (argv[1][0] == 'o')
	{
		digitalWrite(ON_PIN,HIGH);
		printf("power on\n");
		return 0;
	}
	printf("power off\n");


	return 0;
}
