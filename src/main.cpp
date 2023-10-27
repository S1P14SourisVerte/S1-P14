#include <Arduino.h>
#include <librobus.h>

// FONCTION POUR TOURNER LA ROUE
void Turn_1_Wheel(float vitesse, float angle, int moteur);

void Turn_1_Wheel(float vitesse,float angle, int moteur)
{
  // On met la vitesse à 0.1 de sa capacité maximale de 1.0
  // vitesse = 0.1;
  // Transcription de angle à pulse
  // ratio_a_c = ratio de l'angle par rapport à la circonférence / ratio_p_a = ratio du pulse par rapport à l'angle
  float ratio_p_a;
  float ratio_a_c;
  float circonferenceTrajectoire = 47.00;
  float circonferenceRoue = 9.4247;
  float nb_pulses;
  float pulse_reel;

  ratio_a_c = (angle / 360)* circonferenceTrajectoire;
  ratio_p_a = (ratio_a_c/circonferenceRoue);
  nb_pulses = (ratio_p_a*3200);

  // Variable encodeur
  pulse_reel = ENCODER_Read(moteur);

  while (nb_pulses >= pulse_reel)
  {
    MOTOR_SetSpeed(moteur, vitesse);
    pulse_reel = ENCODER_Read(moteur);
  }
  
  MOTOR_SetSpeed(moteur,0);
ENCODER_Reset(moteur);

}

// FONCTION TOURNER LES DEUX ROUES
void Turn_2_Wheel(float speed, float angle, int direction) {
  float ratio_p_a;
  float ratio_a_c;
  float circonferenceTrajectory = 23.88;
  float circonferenceWheel = 9.4247;
  float pulses;
  float LeftPulses;
  float RightPulses;
  float pulsesDifference;
  float newSpeedLeft;
  float newSpeedRight;

  ratio_a_c = (angle / 360) * circonferenceTrajectory;
  ratio_p_a = (ratio_a_c / circonferenceWheel);
  pulses = (ratio_p_a * 3200);

  // Encoder variable
  LeftPulses = (float)abs(ENCODER_Read(0));
  RightPulses = (float)abs(ENCODER_Read(1));

  if (direction == 0) {
    
    while (LeftPulses < pulses)
    {
      MOTOR_SetSpeed(0, 0.98*speed);
      MOTOR_SetSpeed(1, -speed);
      LeftPulses = (float)abs(ENCODER_Read(0));
      RightPulses = (float)abs(ENCODER_Read(1));
    }

    LeftPulses = (float)abs(ENCODER_Read(0));
    RightPulses = (float)abs(ENCODER_Read(1));

    while (LeftPulses >= RightPulses)
    {
      Serial.print("rp: ");
      Serial.println(RightPulses);
      RightPulses = (float)abs(ENCODER_Read(1));
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, -0.01);
      RightPulses = (float)abs(ENCODER_Read(1));
    }

    MOTOR_SetSpeed(1, 0);


  } else
    while ((pulses >= LeftPulses) && (pulses >= RightPulses)) {
      LeftPulses = (float)ENCODER_Read(0);
      RightPulses = (float)ENCODER_Read(1);
      pulsesDifference = LeftPulses - RightPulses;
      newSpeedLeft = speed - (0.0005 * pulsesDifference);
      newSpeedRight= speed + (0.0001 * pulsesDifference);

      MOTOR_SetSpeed(0, -1*newSpeedLeft);
      MOTOR_SetSpeed(1, newSpeedRight);

      LeftPulses = (float)ENCODER_Read(0);
      RightPulses = (float)ENCODER_Read(1);
    }

  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}

void setup() {
  BoardInit();

}

void loop() {
Turn_2_Wheel(0.15,90,0);
delay(1000);

}
