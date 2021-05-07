#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *gen_pswd(unsigned int length) //Надо передать сюда еще count'ы из main'а
{
  unsigned int i, j;
  unsigned int nrand;
  unsigned int ns_russ, ns_gruss, ns_latin, ns_glatin, ns_esc,
      ns_dig; //Переменные для хранения информации о количестве различных
              //символов в пароле

  char *pswd; //Новый пароль будет возвращен в эту функцию

  char s_russ[] = {
      'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'к',
      'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х',
      'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я'}; //Русские вперед

  char s_gruss[] = {
      'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'К',
      'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х',
      'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я'}; // Заглавные русские

  char s_latin[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; //Малые латинские

  char s_glatin[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                     'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; //Заглавные
                                                              //латинские

  char s_esc[] = {
      '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
      '-', '=', '+', '.', ',', ':', ';', '"', '?'}; //Специальыне символы

  pswd = (char *)malloc(length * sizeof(char)); //Выделение памяти под пароль

  ns_russ = length - rand() % (length + 1);
  //Должна будет быть проверка на наличие ключа отвечающего за включение
  //заглавных букв
  ns_gruss = length - ns_russ - rand() % (length - ns_russ + 1);

  ns_latin =
      length - ns_russ - ns_gruss - rand() % (length - ns_russ - ns_gruss + 1);

  //ДОлжна будет быть проверка на наличие ключа отвечающего за включение
  //заглавных букв
  ns_glatin = length - ns_russ - ns_gruss - ns_latin -
              rand() % (length - ns_russ - ns_gruss - ns_latin + 1);

  if (ns_gruss > 0)
    ns_esc = length - ns_russ - ns_gruss;
  else
    ns_esc = length - ns_russ;

  if (ns_glatin > 0)
    ns_esc = length - ns_latin - ns_glatin;
  else
    ns_esc = length - ns_latin;

  for (i = 0; i < length; i++) {
    nrand = rand() % 100;

    if (nrand > 80) {
      pswd[i] = s_russ[rand() % sizeof(s_russ)];
    }
    if (nrand > 60 && nrand <= 80) {
      pswd[i] = s_gruss[rand() % sizeof(s_gruss)];
    }

    else if (nrand > 40 && nrand <= 60) {
      pswd[i] = s_latin[rand() % sizeof(s_latin)];
    } else if (nrand > 20 && nrand <= 40) {
      pswd[i] = s_glatin[rand() % sizeof(s_glatin)];
    } else {
      pswd[i] = s_esc[rand() % sizeof(s_esc)];
    }
  }

  return pswd;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  unsigned int countN; //Число паролей
  int countc; //Будет включена хотя бы одна заглавная буква
  int countn; //В пароле будет хотя бы одно число
  int county; //Будет включен хотя бы один спец символ
  int countA;          //Заглавные не будут включены
  int count0;          //Числа не будут включены
  unsigned int length; //Длина пароля
  char *pswd;

  if (!argv[1]) {
    printf("\t You must enter the required length for the password"); //Пользователь
                                                                      //не ввел
                                                                      //длинну
                                                                      //пароля
    exit(1);
  } else if (atoi(argv[1]) >
             4096) { //Пользователь ввел слишком большую длинну пароля
    printf("\t Password is too long.Max length is 4096 symbols.Please choose a "
           "smaller number\n ");
    exit(2);
  }

  if (atoi(argv[1]) == 0) { //Пользователь запросил пароль длинны 0
    printf("\t The password cannot consist of 0 symbols\n ");
    exit(3);

  } else // Все в порядке,считываем длинну
    length = atoi(argv[1]);

  pswd = gen_pswd(length);
  printf("%s\n", pswd);
  free(pswd);

  return 0;
}

