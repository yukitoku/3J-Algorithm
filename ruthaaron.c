#define KETA 6

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

struct NUMBER{
	int n[KETA];//各桁の値
	int sign;//符号変数
};

int setSign(struct NUMBER *a, int s){
	if(s >= 0)
		a->sign = 1;
	else
		a->sign = -1;
}

int getSign(struct NUMBER *a){
	if(a->sign < 0)
		return -1;
	else
		return 1;
}

void clearByZero(struct NUMBER *a){//ゼロクリア&符号を+にセット
	int i = 0;

	while(1){
		if(i > KETA - 1) break;
		a->n[i] = 0;
		i++;
	}
	setSign(a,0);
	//a->sign = 1;//符号をプラスにセット
}

void dispNumber(struct NUMBER *a){//表示関数
	int i = KETA - 1;
		printf("+ ");
	while(1){
		if(i < 0) break;
		printf("%d ", a->n[i]);
		i--;
	}
}

void setRnd(struct NUMBER *a,int k){//乱数格納
	int i = 0;
	a->sign = 1;

	while(1){
		if(i > k - 1) break;
		a->n[i] = random() % 10;
		i++;
	}
}

void copyNumber(struct NUMBER *a, struct NUMBER *b){//aをbにコピー
	int i = 0;
	b->sign = a->sign;

	 while(1){
	 	if(i > KETA - 1) break;
	 	b->n[i] = a->n[i];
	 	i++;
	 } 
}

int isZero(struct NUMBER *a){//ゼロかどうか
	int i = 0;

	while(1){
		if(i > KETA-1) break;
		if((a->n[i] != 0)) return -1;
		i++;
	}

	return 1;
}

int mulBy10(struct NUMBER *a){//10倍
	int i = KETA - 1;
	int overflag = 0;
	if (a->n[KETA-1] != 0) 
		overflag = -1;
	
	while(1){
		if(i <= 0) break;
		a->n[i] = a->n[i-1];
		i--;
	}
	a->n[0] = 0;

	return overflag;
}

int divBy10(struct NUMBER *a){
	int i = 0;

	while(1){
		if(i > KETA-2) break;
		a->n[i] = a->n[i+1];
		i++;
	}
	a->n[KETA-1] = 0;
	return 0;
}

int setInt(struct NUMBER *a, int x){
	int i = 0;
	int x2 = x;
	int amari;

	while(1){
		if(abs(x) <= 0) break;
		amari = x%10;
		a->n[i] = abs(amari);
		x /= 10;
		i++;
	}
	return 0;
}

int numComp(struct NUMBER *a , struct NUMBER *b){
	int i = KETA-1;
	
	while(1){
		if(i < 0) break;
		if(a->n[i] > b->n[i]) return 1;
		if(a->n[i] < b->n[i]) return -1;
		i--;
	}
	return 0;
}

int getKeta(struct NUMBER *a){
	int i = KETA;
	while(a->n[i-1] == 0) i--;
	return i;
}

int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
	int d;
	int e = 0;
	int i = 0;
	int ret = 0;

	while(1){
		if(i > KETA-1) break;
		d = a->n[i] + b->n[i] + e;
		c->n[i] = d % 10;
		d /= 10;
		e = d % 10;
		i++;
	}
	if(d > 0) ret = -1;

	return ret;
}

int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
	int h = 0;
	int ai,bi;
	int i = 0;
	clearByZero(c);
	if(numComp(a,b) > -1){
		while(1){
			if(i > KETA-1) break;
			ai = a->n[i];
			bi = b->n[i];
			ai -= h;
			if(ai >= bi){
				c->n[i] = ai - bi;
				h = 0;
			} 
			if(ai < bi){
				c->n[i] = 10 + ai - bi;
				h = 1;
			}
			i++;
		}
	}
	else{
		sub(b,a,c);
		setSign(c,-1);
	}
	return 0;
}

int increment(struct NUMBER *a, struct NUMBER *b){
	struct NUMBER one;
	int r;
	clearByZero(&one);

	setInt(&one , 1);
	r = add(a, &one, b);

	return r;
}

int decrement(struct NUMBER *a, struct NUMBER *b){
	struct NUMBER one;
	int r;
	clearByZero(&one);

	setInt(&one , 1);
	r = sub(a, &one, b);

	return r;
}

int simpleMultiple(int a, int b, int *c){
	int i = 1;
	*c = 0;

	while(1){
		if(i > b) break;
		*c += a;
		i++;
	}
	
	return 0;
}

int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
	int bi,aj;
	int i = 0;
	int j = 0;
	int h = 0;
	struct NUMBER d;
	clearByZero(c);

		int e;
		while(1){
			if(i > KETA-1) break;
			bi = b->n[i];
			j = 0;
			h = 0;

			clearByZero(&d);

			while(1){
				if (j > KETA - i) break;

				aj = a->n[j];
				simpleMultiple(aj,bi,&e);
				e += h;
				d.n[j+i] = e % 10;
				h = e / 10;
				if((j == (KETA - 1)) && h != 0) return -1;
				j++;
			}
			add(c,&d,c);
			i++;
	}
	return 0;
}



int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d){
	struct NUMBER e,f;

	clearByZero(c);

	while(1){
		if(numComp(a, b) >= 0){
			copyNumber(b, d);
			clearByZero(&e);
			setInt(&e, 1);

			while(1){
				if(numComp(a, d) < 1) break;
				mulBy10(d);
				mulBy10(&e);
			}
			divBy10(d);
			divBy10(&e);

			sub(a, d, &f);
			copyNumber(&f, a);
			add(c, &e, c);
		} else {
			copyNumber(a, d);
			break;
		}
	}

	return 0;
}

void sqrt_newton(struct NUMBER *N, struct NUMBER *x){
	struct NUMBER b,c,d,e,f;
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&e);//2
	clearByZero(&f);

	setInt(&e,2);

	divide(N, &e, x, &c);
	
	copyNumber(x, &b);
	copyNumber(x, &c);

	while(1){
		copyNumber(&b, &c);
		copyNumber(x, &b);
		divide(N, &b, x, &d);
		add(x, &b, x);
		divide(x, &e, &f, &d);
		copyNumber(&f,x);

		if(numComp(x, &b) == 0) break;

		if(numComp(x, &c) == 0){
			if(numComp(x, &b)) copyNumber(&b, x);
			break;
		}
	}
}

void soinsu(struct NUMBER *x, struct NUMBER *ans){
	struct NUMBER root_x, num, a, b, c;
	clearByZero(&root_x);
	clearByZero(&num);
	clearByZero(&a);
	clearByZero(&b);
	copyNumber(x, &c);
	setInt(&num, 2);
	sqrt_newton(x, &root_x);

	while(numComp(&c, &root_x) == 1 && numComp(&c, &num) == 1){
		divide(&c, &num, &a, &b);
		if(isZero(&b) == 1){
			copyNumber(&a, &c);
			add(ans, &num, ans);
			divide(&c, &num, &a, &b);
		}
		else{
			increment(&num, &num);
		}
	}
	decrement(&c, &a);

	if(isZero(&a) != 1){
		add(ans, &c, ans);
	}
}

void ruthaaron(struct NUMBER *a, int roop_times){
	struct NUMBER before, current, num, b;
	int i = 0;
	clearByZero(&before);
	clearByZero(&current);
	clearByZero(&num);

	increment(a, &num);

	copyNumber(a, &b);
	
	soinsu(a, &before);

	while(1){
		if(i > roop_times) break;

		soinsu(&num, &current);

		if(numComp(&before, &current) == 0){
			dispNumber(a);
			printf("\n");
			dispNumber(&num);
			printf("\n\n");
		}

		copyNumber(&current, &before);
		copyNumber(&num, a);
		increment(&num, &num);
		clearByZero(&current);
		i++;
	}
}

int main (int argc,char **argv){
	srandom(time(NULL));

	struct NUMBER a,b,c,d;
	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);

	setRnd(&a, 2);
	setRnd(&b, 2);
	//setInt(&a,2);
	setSign(&a, 1);
	setSign(&b, 1);

	//printf("start number is\n");
	dispNumber(&a);
	printf("\n");
	dispNumber(&b);
	printf("\n\n");

	multiple(&a, &b, &c);

	//divide(&a,&b,&c,&d);

	//ruthaaron(&a,1000000000);

	//printf("end number is\n");
	//decrement(&a, &b);
	dispNumber(&c);
	printf("\n");
	//dispNumber(&d);

	return 0;
}