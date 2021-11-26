/*
*** ATHLETIC SOCKS ***
- Updated as of 2021-11-26
 - WIP
*/

int time=800;
int rounds = 98; //the amount of times the game will be repeated (< 100) 5 means 4 rounds will be played.
bool alive;

void setup() {
    pinMode(13, OUTPUT);
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
    Serial.begin (19200);
}

void loop(){
    int lamp_number;
    int level=1; //players level
    int repeat;
    //arrays
    int player[99];
    int order[99];
    alive = true;

    randomSeed(analogRead(A1)); //uses LDR for random seed

    //generate the lamp order
    for(int i = 0; i < rounds; ++i){
        order[i] = random(1,6);  //random number ranging 1-6
    }

    //gameloop
    while(alive && level<rounds) {
        Serial.println("enter control lamp(s)");

        //control lamp(s)
        for(int lys = 0; lys < level; ++lys) {
            lamp_number = order[lys]; //turns lamp ON
            lampa(lamp_number);
        }

        //control sensor(s)
        repeat = 0;
        while(alive && repeat < level) {
            player[repeat] = sensor();

            //correct answers
            if (order[repeat] == player[repeat]) {
                digitalWrite(9, HIGH);
                delay(time);
                digitalWrite(9, LOW);
            }
            else {
                loose();
            }
            repeat++;
        }
        level++;    
        if(rounds==level){
            win();  
        }
    }
}

//lamp function
void lampa(int l) {
    Serial.println("enter lampa");
    delay(time);
    switch (l) {
    case 1:
        digitalWrite(7, HIGH);
        delay(time);
        digitalWrite(7, LOW);
        break;
    case 2:
        digitalWrite(6, HIGH);
        delay(time);
        digitalWrite(6, LOW);
        break;
    case 3:
        digitalWrite(5, HIGH);
        delay(time);
        digitalWrite(5, LOW);
        break;
    case 4:
        digitalWrite(4, HIGH);
        delay(time);
        digitalWrite(4, LOW);
        break;
    case 5:
        digitalWrite(3, HIGH);
        delay(time);
        digitalWrite(3, LOW);
        break;
    //case 6:
    //    digitalWrite(2, HIGH);
    //    delay(time);
    //    digitalWrite(2, LOW);
    //    break;
    }
}

int sensor() {
    Serial.println("enter sensors");
    //variables
    int sensorID=0; //the ID of the select sensor
    while(sensorID==0){
        //sensor 1, generator
        //on A0
        if(analogRead(A0)<800){
            sensorID=1;
        }
        //sensor 2, pushbutton
        //on 13
        if(digitalRead(12)==HIGH){
            sensorID = 2;
        }
        //sensor 3, LDR
        //on A1
        if(analogRead(A1)<200){
            sensorID = 3;
        }
        //sensor 4, switch
        //on 11
        if(digitalRead(11)==HIGH){
            sensorID = 4;
        }
        //sensor 5, pushbutton 2
        //on 10
        if(digitalRead(10)==HIGH){
            sensorID = 5;
        }
        //sensor 6, humidity
        //on A2
        //if(analogRead(A2)>60){
        //    sensorID=6;
        //    wait();
        //}
    }
    Serial.print("sensor ID=");
    Serial.println(sensorID);
    return(sensorID);
}

void win(){
    //win routine
    Serial.println("congratulations");
    digitalWrite(9, HIGH);
    digitalWrite(13, HIGH);
    delay(time);
    digitalWrite(9, LOW);
    digitalWrite(13, LOW);
    delay(time);
    digitalWrite(9, HIGH);
    digitalWrite(13, HIGH);
    delay(time);
    digitalWrite(9, LOW);
    digitalWrite(13, LOW);
    delay(time);
    digitalWrite(9, HIGH);
    digitalWrite(13, HIGH);
    delay(time);
    digitalWrite(9, LOW);
    digitalWrite(13, LOW);
}

//game lost
void loose(){
    //loose routine
    Serial.println("looser :(");
    digitalWrite(8, HIGH);
    digitalWrite(13, HIGH);
    delay(time);
    digitalWrite(8, LOW);
    delay(time);
    digitalWrite(8, HIGH);
    delay(time);
    digitalWrite(8, LOW);
    digitalWrite(13, LOW);
    delay(time);
    digitalWrite(8, HIGH);
    delay(time);
    digitalWrite(8, LOW);

    //reset
    alive=false;
}

void wait(){ //wait for sensor "clearing".
    for(int i=0; i < 6; i++){
        digitalWrite(8, HIGH);
        delay(500);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        delay(500);
        digitalWrite(9, LOW);
        delay(500);
    }
}