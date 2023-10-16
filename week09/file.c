/**
 * this file is to be used as a test of clang IL generation capabilities
 * compile as:
 *   clang file.c: error because there is no main (entry point)
 *   clang -S file.c: generates file.s which contains the code in ASM
 *   clang -S -emit-llvm filec.: generates file.ll which cotains llvm IR code
 */

void prefix_sum(int *src, int *dst, int N) {
	/* for(int i=0;i<N;i++){
		int tmp=0;
		int j=0;
		if(j<i){
			do {
				tmp += src[j];
				j++;
			}while(j<i);
			dst[i]=tmp;
		}
	} */
	if (0 < N) {
		int i = 0;
		do {
			int tmp = 0;
			int j = 0;
			if (j < i) {
				do {
					tmp += src[j];
					j++;
				} while (j < i);
				dst[i] = tmp;
			}
			i++;
		} while (i < N);
	}
}

//crea el archivo .dot
//opt -dot-cfg file.ll -disable-output -enable-new-pm=0
// crea la imagen del archivo dot
//dot -Tpng .prefix_sum.dot -o ps.png

//llc file.ll -march=arm -o file.arm
