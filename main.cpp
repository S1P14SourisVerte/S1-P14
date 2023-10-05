#include <Arduino.h>
#include <librobus.h>

// FONCTION POUR TOURNER LA ROUE
void Tourner_1_Roue(float vitesse, float angle, int moteur);

void Tourner_1_Roue (float vitesse,float angle, int moteur)
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
  Serial.println(ratio_a_c);
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
void Tourner_2_Roues(float vitesse, float angle, int direction);

void Tourner_2_Roues (float vitesse,float angle, int direction)
{
  // On met la vitesse à 0.2 de sa capacité maximale de 1.0
  // vitesse = 0.2;
  // Transcription de angle à pulse
  // ratio_a_c = ratio de l'angle par rapport à la circonférence / ratio_p_a = ratio du pulse par rapport à l'angle
  float ratio_p_a;
  float ratio_a_c;
  float circonferenceTrajectoire = 23.88;
  float circonferenceRoue = 9.4247;
  float nb_pulses;
  float pulse_reel1;
  float pulse_reel2;


  ratio_a_c = (angle / 360)* circonferenceTrajectoire;
  Serial.println(ratio_a_c);
  ratio_p_a = (ratio_a_c/circonferenceRoue);
  nb_pulses = (ratio_p_a*3200);
  


  // Variable encodeur
  pulse_reel1 = ENCODER_Read(0);
  pulse_reel2 = ENCODER_Read(1);

//direction = 0 => droite
  if (direction == 0)
  {
    while ((nb_pulses >= pulse_reel1) && (nb_pulses >= pulse_reel2) )
  {
    MOTOR_SetSpeed(0,(0.9721*vitesse));
    MOTOR_SetSpeed(1,-vitesse);
    pulse_reel1 = ENCODER_Read(0);
    pulse_reel2 = ENCODER_Read(1);



  }
  
}

// direction = 1 => gauche

  else 
  {
    while ((nb_pulses >= pulse_reel1) && (nb_pulses >= pulse_reel2) )
  {
    MOTOR_SetSpeed(0,(-0.988*vitesse));
    MOTOR_SetSpeed(1,vitesse);
    pulse_reel1 = ENCODER_Read(0);
    pulse_reel2 = ENCODER_Read(1);



  }
  
  }
     
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
ENCODER_Reset(0);
ENCODER_Reset(1);
}

void setup() {
  BoardInit();

}

void loop() {
Tourner_2_Roues(0.15,90,1);
delay(1000);
Tourner_2_Roues(0.15,90,0);
delay(1000);
Tourner_2_Roues(0.15,180,1);
delay(1000);
Tourner_2_Roues(0.15,180,0);
delay(1000);
Tourner_2_Roues(0.15,360,1);
delay(1000);
Tourner_2_Roues(0.15,360,0);
delay(1000);
}
