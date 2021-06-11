package a01;

class Carro {
  public int velocidade;

  public void acelerar(int velocidade) {
    this.velocidade = velocidade;
    System.out.println("Acelerando o carro para " + velocidade + "km/h");
  }

  public void frear() {
    this.velocidade = 0;
    System.out.println("Freando o carro");
  }

  public static void main(String[] args) {
    Carro carro = new Carro();

    System.out.println(carro.velocidade);
    carro.acelerar(100);
    System.out.println(carro.velocidade);
    carro.frear();
    System.out.println(carro.velocidade);
  }
}
