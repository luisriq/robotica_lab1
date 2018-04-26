#include <Servo.h>
#include <math.h>

struct Angulos {
    float q1;
    float q2;
    float q3;
};

struct Coordenada {
  float x;
  float y;
  float z;
  float pinza;
};

Coordenada coord(float x, float y, float z, float pinza){
  Coordenada c1;
  c1.x = x;
  c1.y = y;
  c1.z = z;
  c1.pinza = pinza;
  return c1;
  }

Coordenada rutina[] = {
  //Bajando de a poco
  coord(-7,7,7,60),
  coord(-4,4,5,60),
  coord(-3,3,4,60),
  coord(-4,4,3,60),
  coord(-5,5,2,60),
  coord(-5,5,1,60),
  coord(-5,5,0,60),
  coord(-6,6,-1,60),
  
  coord(-7,7,-1,60),
  coord(-7,7,-1,25),
  coord(-7,7,7,25),
  coord(0,7,7,25),
  coord(7,7,7,25),
  coord(7,7,0,25),
  coord(7,7,0,60),
  coord(7,7,7,60),
  coord(0,7,7,60),

//Bajando de a poco
  coord(-7,7,7,60),
  coord(-4,4,5,60),
  coord(-3,3,4,60),
  coord(-4,4,3,60),
  coord(-5,5,2,60),
  coord(-5,5,1,60),
  coord(-5,5,0,60),
  coord(-6,6,-1,60),
  

  coord(-7,7,-1,60),
  coord(-7,7,-1,25),
  coord(-7,7,7,25),
  coord(0,7,7,25),
  coord(7,7,7,25),
  coord(7,7,3,25),
  coord(7,7,3,60),
  coord(7,7,7,60),
  coord(0,7,7,60),  

  //Bajando de a poco
  coord(-7,7,7,60),
  coord(-4,4,5,60),
  coord(-3,3,4,60),
  coord(-4,4,3,60),
  coord(-5,5,2,60),
  coord(-5,5,1,60),
  coord(-5,5,0,60),
  coord(-6,6,-1,60),

  coord(-7,7,-1,60),
  coord(-7,7,-1,25),
  coord(-6,6,10,25),
  coord(0,7,9,25),
  coord(7,7,8,25),
  coord(7,7,7,25),
  coord(7,7,7,60),
  coord(7,7,9,60),
  coord(0,7,9,60)
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

float TeoCos(float a, float b, float c){
  return acos((a*a + b*b - c*c) / (2 * a * b));
}

float grad(float x){
    return 180*x/Pi;
}

Angulos calcularAngulos(float x, float y, float z){
    Angulos angulo;
    angulo.q1 = grad(atan2(y, x));
    float dist = sqrt(y*y + z*z);
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

  for(int i = 0; i<sizeof(rutina)/sizeof(Coordenada); i++){
    delay(500);
    Serial.println("---");
    int x = rutina[i].x;
    int y = rutina[i].y;
    int z = rutina[i].z;
    int p = rutina[i].pinza;
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
    delay(50);
    servos[2].write(angulos.q2);
    delay(50);
    servos[1].write(angulos.q3);
    servos[3].write(p);
  
  }
}



