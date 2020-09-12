// // connect motor controller pins to Arduino digital pins
// // motor one
// int enA = 10;
// int in1 = 7;
// int in2 = 8;
// // motor two
// int enB = 5;
// int in3 = 7;
// int in4 = 6;
// void setup()
// {
//     // set all the motor control pins to outputs
//     pinMode(enA, OUTPUT);
//     pinMode(enB, OUTPUT);
//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
//     pinMode(in3, OUTPUT);
//     pinMode(in4, OUTPUT);
// }
// void demoOne()
// {
//     // this function will run the motors in both directions at a fixed speed
//     // turn on motor A
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     // set speed to 200 out of possible range 0~255
//     analogWrite(enA, 200);

//     delay(2000);
//     // now change motor directions
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);

//     delay(2000);
//     // now turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
// }
// void demoTwo()
// {
//     // this function will run the motors across the range of possible speeds
//     // note that maximum speed is determined by the motor itself and the operating voltage
//     // the PWM values sent by analogWrite() are fractions of the maximum speed possible
//     // by your hardware
//     // turn on motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);

//     // accelerate from zero to maximum speed

//     for (int i = 150; i < 256; i++)
//     {
//         analogWrite(enA, i);

//         delay(500);
//     }
//     // decelerate from maximum speed to zero
//     for (int i = 255; i > 150; --i)
//     {
//         analogWrite(enA, i);

//         delay(500);
//     }

//     // now turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
// }
// void loop()
// {
//     demoTwo();
// }