/*
Universidade Estadual de Santa Cruz - Ciencia da Computacao
Conceitos de Linguagens de Programacao
Eduardo Takeshi Watanabe
*/
public class Permutacoes {
	private static int[] p;    

	public static void permuta(int[] vet) {
		p = new int[vet.length];
		permuta(vet,0);
	}
			
	private static void permuta(int[] vet, int n) {
		if (n==vet.length) {
			imprime();
			
		} else {
			for (int i=0; i < vet.length; i++) {
				boolean achou = false;
				
				for (int j = 0; j < n; j++) {
					if (p[j]==vet[i]) achou = true;
				}
			
				if (!achou) {
					p[n] = vet[i];
					permuta(vet,n+1);
				}
			}
		}
	}
	
	private static void imprime() {
		for (int i=0; i < p.length; i++) {
		    System.out.print(p[i] + " ");
		}
		System.out.println();
	}
	
	public static void main(String[] args) {
		int v[] = {1, 2, 3, 4, 5, 6, 7, 8};
		Permutacoes.permuta(v);
	}
}