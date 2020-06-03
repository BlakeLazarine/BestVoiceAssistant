//Updated to most recent list of commands

void chooseCommand(const int in)
{
  switch(in)
  {
    case 1:
      turnOnTheLights();
      break;
    case 2:
      turnOffTheLights();
      break;
    case 3:
      getText(); //Time
      break;
    case 4:
      getText(); //Weather
      break;
    case 5:
      sayAJoke();
      break;
    case 6:
      playMusic();
      break;
    case 7:
      lightShow();
      break;
    case 8:
      bitchesInTheTesla();
      break;
    case 9:
      break;

    default:
      break;
  }
  return;
}
