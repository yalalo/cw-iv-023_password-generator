#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(char *a, char *b) //Простая функция, меняющая местами два
                            //объекта,пояснять особо нечего
{
  int t;

  t = *a, *a = *b, *b = t;
}

char *gen_pswd(unsigned int length) //Надо передать сюда еще count'ы из main'а
{
  unsigned int i, j;
  unsigned int nrand;
  unsigned int ns_russ, ns_gruss, ns_latin, ns_glatin, ns_esc,
      ns_dig; //Переменные для хранения информации о количестве различных
              //символов в пароле

  char *pswd;

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
      '-', '=', '+', '.', ',', ':', ';', '"', '?'}; //Специальные символы
                                                    //Ниже  будет добавлено
                                                    //очень много проверок на
                                                    //ключи

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
  unsigned int countN = 1; //Число паролей
  int countc = 0; //Будет включена хотя бы одна заглавная буква
  int countn = 0; //В пароле будет хотя бы одно число
  int county = 0; //Будет включен хотя бы один спец символ
  int countA = 0; //Заглавные не будут включены
  int count0 = 0; //Числа не будут включены
  unsigned int length = 10; //Длина пароля
  char *pswd;

  //Ниже огромная функция по поиску ключей

  int z = 0;
  int u = 0;
  int g;
  char arr[65];
  for (int i = 1; i < argc; i++) { //Проходимся по всем введенным ключам
    g = strlen(argv[i]); //Считываем длину каждого из введенных ключей
    strcpy(arr, argv[i]); //Копируем введенные ключи в массив arr,иного способа
                          //получить возможность обращаться к элементам ключа по
                          //их индексу я придумать не смог
    for (int j = 0; j < (g + 1);
         j++) { //Проходимся по каждому символу ключа, если это не длинна или
                //кол-во паролей,то просто увеличиваем соответствующую
                //переменную-счетчик на единицу,если  это N или l,то алгоритм
                //описан ниже
      if (arr[j] == 'N') {
        if (z == 0) {
          for (int v = 0; v < g;
               v++) { //Проходимся по ключу,отсекая не числовые символы до тех
                      //пор,пока atoi не найдет число,являющееся длинной или
                      //количеством паролей соответственно
            for (int v = 0; v < g; v++) {
              swap(&arr[v], &arr[v + 1]);
            }
            arr[g - 1] = '/0';
          }
          z = atoi(arr);
        }
        countN = z;
      }
      if (arr[j] == 'c') {
        countc = countc + 1;
      }
      if (arr[j] == 'n') {

        countn = countn + 1;
      }
      if (arr[j] == 'y') {
        county = county + 1;
      }
      if (arr[j] == 'A') {
        countA = countA + 1;
      }
      if (arr[j] == 'O') {
        count0 = count0 + 1;
      }
      if (arr[j] == 'l') { // Тот же принцип что и в поиске кол-ва паролей
        if (u == 0) {
          for (int v = 0; v < g; v++) {
            for (int v = 0; v < g; v++) {
              swap(&arr[v], &arr[v + 1]);
            }
            arr[g - 1] = '/0';
          }
          u = atoi(arr);
        }
        length = u;
      }
    }
  }

  if (((countA != 0) && (countc != 0)) ||
      ((count0 != 0) &&
       (countn != 0))) //Проверка на наличие взаимоисключающих ключей
  {
    printf("Error : You have entered mutually exclusive keys\n");
    exit(4);
  }

  if (length > 4096) { //Пользователь ввел слишком большую длинну пароля
    printf("\t Password is too long.Max length is 4096 symbols.Please choose a "
           "smaller number\n ");
    exit(2);
  }

  if (length == 0) { //Пользователь запросил пароль длинны 0
    printf("\t The password cannot consist of 0 symbols\n ");
    exit(3);
  }

  for (int i = 0; i < countN; i++) {
    pswd = gen_pswd(length);
    printf("%s\n", pswd);
    free(pswd);
  }
  return 0;
}

