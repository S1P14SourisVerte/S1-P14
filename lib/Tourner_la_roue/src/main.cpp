#include <Arduino.h>
#include <librobus.h>

// FONCTION POUR TOURNER LA ROUE
int Tourner_Roue(float vitesse, int angle, int moteur);

int Tourner_Roue (float vitesse,int angle, int moteur)
{
  // On met la vitesse à 0.1 de sa capacité maximale de 1.0
  vitesse = 0.1;
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

  while (ratio_p_a <= pulse_reel)
  {
    MOTOR_SetSpeed(moteur, vitesse);
    pulse_reel = ENCODER_Read(moteur);
  }

}

void setup() {
  BoardInit();
}

void loop() {
int Tourner_Roue (0.1, 90 ,0);
delay(1000);
}
