#define RODADAS 20

//LEDs do Jogo
#define LED_VERMELHO 12
#define LED_AMARELO 8
#define LED_VERDE 10

//LEDs Indicativos
#define LED_ERROU 6
#define LED_GANHOU 7

#define BOTAO_VERMELHO 13
#define BOTAO_AMARELO 9
#define BOTAO_VERDE 11

//Constantes úteis
#define NUMERO_MAX_RODADAS 25
#define BOTAO_NAO_APERTADO 100
#define INTERVALO_TEMPO 500
#define TEMPO_AGUARDAR_RESPOSTA 5

//Função responsável por gerar seed e tornar o jogo "aleatório"
void gerar_seed() {
  int seed;
  
  do {
    seed = botao();
  } while (seed == BOTAO_NAO_APERTADO);
  seed += rand () % 50;
  
  srand(seed);
}

//Função responsável por ler botão. Caso nenhum botão for digitado, é retornado BOTAO_NAO_APERTADO (100)
int botao() {
  delay (700);
 
  if (digitalRead(BOTAO_VERMELHO) == 0){
    return 0;
  } 
  
  if (digitalRead(BOTAO_AMARELO) == 0){
    return 1;
  }
  
  if (digitalRead(BOTAO_VERDE) == 0){
    return 2;
  }
  
  return BOTAO_NAO_APERTADO;
}

//Função responsável por piscar o led em uma determinada quantia de vezes
void piscar_led(int led, int indice, int quantidade_de_vezes) {
  
  digitalWrite(led, HIGH);
  delay (INTERVALO_TEMPO);
  digitalWrite(led, LOW);
  delay (INTERVALO_TEMPO);
    
  if(indice == quantidade_de_vezes) {
    return;
  }

  indice++;
  piscar_led(led, indice, quantidade_de_vezes);

}


//Função responsável por piscar sequência, piscando o led correspondente
void piscar_sequencia(int i, int num[25]) {
    int j;
    
    for (j = 0; j < i; j++){       
      if (num[j] == 0){
        
        piscar_led(LED_VERMELHO, 1, 1);
        delay(INTERVALO_TEMPO);
      
      } else if (num[j] == 1) {
        
        piscar_led(LED_AMARELO, 1, 1);
        delay(INTERVALO_TEMPO);
        
      } else if (num[j] == 2) {
        
        piscar_led(LED_VERDE, 1, 1);
        delay(INTERVALO_TEMPO);
     
      } 
  }
  
}

//Função que verifica os acertos. Caso algum botão for incorreto, o jogo é reiniciado
int verificar_acertos(int i, int num[25]) {
  int j, tentativa, espera = 0;
  
  for (j = 0; j < i+1; j++){ 
        do {
          tentativa = botao();
          espera++;
        } while (tentativa == BOTAO_NAO_APERTADO && espera < TEMPO_AGUARDAR_RESPOSTA);
          
        if (tentativa != num[j]){
          return 0;
        }
   }

   delay(INTERVALO_TEMPO);
   return 1;
}

//Função que verifica o resultado e pisca leds indicativas caso ganhe ou perca
void gerar_resultado(int ganhou) {
  if (ganhou){
    piscar_led(LED_VERMELHO, 1, 3);
    piscar_led(LED_AMARELO, 1, 3);
    piscar_led(LED_VERDE, 1, 3);
    
  }  else {
    piscar_led(LED_ERROU, 1, 3);
  }
  
}

//Pinagem de entradas e saídas
void setup() {
  Serial.begin(9600);
  
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ERROU, OUTPUT);
  pinMode(LED_GANHOU, OUTPUT);
  
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);
  pinMode(BOTAO_VERDE, INPUT_PULLUP);
}

void loop() {
  
  int i, j;
  int num[NUMERO_MAX_RODADAS];
  int ganhou = 1, continuar = 1, acertou;
 
  gerar_seed();

  i = 0;
  while((continuar) && i < NUMERO_MAX_RODADAS) { //Enquanto não errar e não for 25 rodadas (limite de rodadas), deve executar o jogo
    num[i] = rand() % 3;

    piscar_sequencia(i+1, num);
 
    acertou = verificar_acertos(i, num);
    continuar = acertou;
    ganhou = acertou;
    
    i++;
 }

  gerar_resultado(ganhou);

  
}
