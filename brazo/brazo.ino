#include <Servo.h>
#include <math.h>

struct Angulos {
    float q1;
    float q2;
    float q3;
};

Servo servos[4];
void setup() {
  int inicial = 8;
  for(int i = 0; i<4; i += 1) {
    servos[i].attach(i+inicial);
  }
  Serial.begin(9600);
}

const float Pi = 3.14159;
int pos = 0;
float L1 = 8.5;
float L2 = 8.5;
/*
Angulos calcularAngulos(float x, float y, float z){
  Serial.println("====");
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Angulos angulos;
  angulos.q1 = atan2(y, x);
  angulos.q3 = acos(((x*x) + (y*y) + (z*z) - (L1*L1) - (L2*L2))/(2*L1*L2));
  angulos.q2 = atan2(sqrt(x*x + y*y), z ) - atan2((L1 + L2*cos(angulos.q3)), L2*sin(angulos.q3));
  //angulos.q2 = ((-1*L2 * sin(angulos.q3)*x) + (L1 + (L2 * cos(angulos.q3)*y)))/( (L2* sin(angulos.q3)*y) + (L1 + (L2*cos(angulos.q3)*x) ) );
  
  angulos.q1 = 180*angulos.q1/Pi;
  angulos.q2 = 180*angulos.q2/Pi;
  angulos.q3 = 180*angulos.q3/Pi;
  angulos.q3 = 180 - angulos.q3;
  return angulos;
}*/

float TeoCos(float a, float b, float c){
  return acos((a*a + b*b - c*c) / (2 * a * b));
}

float Dist(float x, float y){
  return sqrt(x*x + y*y);
}

float grad(float x){
    return 180*x/Pi;
}

Angulos calcularAngulos(float x, float y, float z){
    Angulos angulo;
    angulo.q1 = grad(atan2(y, x));
    float dist = Dist(y, z);
    float Q11 = atan2(z, y);
    float Q12 = TeoCos(dist, L1, L2);
    angulo.q2 = Q11 + Q12;
    angulo.q3 = TeoCos(L1, L2, dist);
  
    angulo.q2 = grad(angulo.q2);
    angulo.q3 = grad(angulo.q3);
    return angulo;
}

Angulos calibrarAngulos(Angulos angulos) {
  angulos.q1 = angulos.q1 - 10;
  angulos.q3 = angulos.q3 - (90-angulos.q2);
  angulos.q2 = 180-(angulos.q2);
  return angulos;  
}

Angulos angulos;

void loop() {
  if ( Serial.available()) {
    Serial.println("---");
    int x = Serial.readStringUntil(',').toInt();
    int y = Serial.readStringUntil(',').toInt();
    int z = Serial.readStringUntil('\n').toInt();
    angulos = calcularAngulos(x, y, z);
    Serial.println(angulos.q1);
    Serial.println(angulos.q2);
    Serial.println(angulos.q3);
    Serial.println("·········");
    angulos = calibrarAngulos(angulos);
    Serial.println(angulos.q1);
    Serial.println(angulos.q2);
    Serial.println(angulos.q3);

    
    servos[0].write(angulos.q1);
    servos[2].write(angulos.q2);
    servos[1].write(angulos.q3);

  }
}


