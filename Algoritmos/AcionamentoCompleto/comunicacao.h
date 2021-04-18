// Comunicação utilizando apenas entradas e saídas digitais
bool sinal = true;
//====================================================================
bool aguardarComando(){
  int SD1 = 9;                            // Variáveis locais
  int verificador = 0;
  unsigned long tempo_anterior = 0;
  
// Aguarda a mudança de estado de SD1 com um tempo limite de 1 segundo
  while(digitalRead(SD1) == sinal){ 
    // Tempo em ms desde o início da execução do programa
    unsigned long tempo_atual = millis();
    
    // Verifica a cada 100ms se um bit foi recebido
    if (tempo_atual - tempo_anterior >= 100){
      verificador++;
      if(verificador == 10) return false; // Cancela a operação
      tempo_anterior = tempo_atual;
    }
  }
  if (sinal == false)     sinal = true;
  else if (sinal == true) sinal = false;
  return true;                            // Bit recebido
}
//====================================================================
// Recebe, converte e armazena uma nova referência
int referencia (){
  int SD2 = 10;                           // Variáveis locais
  // Número de 7 bits e um bit de verificação
  byte ref = 0b00000000; 

  // Leitura sequencial de 8 bits
  for(int i=0; i<8; i++){

      // Se um bit for recebido
      if(aguardarComando()) {
        // Verifica o valor do bit lido na entrada digital SD2
        // e registra no índice i da variável "ref"
        if (digitalRead(SD2)) bitWrite(ref, i, 1);
        else bitWrite(ref, i, 0);
      }
    // Se o limite de tempo de espera for excedido, cancela a operação
      else return 0;
      }  
  // Confere se bit de verificação foi recebido
  if(bitRead(ref, 7) == 0){ 
    // Converte em inteiro o byte construído 
    int valor = ref;
    return valor;
  }
  // Cancela a operação
  else return 0;
}
