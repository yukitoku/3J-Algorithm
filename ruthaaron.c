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

int getKeta(struct NUMBER *a){
	int i = KETA;
	while(a->n[i-1] == 0) i--;
	return i;
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

int divby1keta(struct NUMBER *a, struct NUMBER *b, int d){
	int h, i, ai, t;

	clearByZero(b);

	i = getKeta(a) - 1;
	h = 0;

	while(1){
		if(i < 0) break;

		ai = a->n[i];
		t = 10 * h + ai;
		h = t % d;
		b->n[i] = (t - h) / d;
		i--;
	}
	return h;
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
	struct NUMBER e,f,a2;

	clearByZero(&a2);
	copyNumber(a,&a2);
	clearByZero(c);

	if(getKeta(b) == 1){
		d->n[0] = divby1keta(&a2, c, b->n[0]);
	}
	else{
		while(1){
			if(numComp(&a2, b) >= 0){
				copyNumber(b, d);
				clearByZero(&e);
				setInt(&e, 1);

				while(1){
					if(numComp(&a2, d) < 1) break;
					mulBy10(d);
					mulBy10(&e);
				}

				if(numComp(b, d) != 0){
					divBy10(d);
					divBy10(&e);
				}

				sub(&a2, d, &f);

				copyNumber(&f, &a2);
				add(c, &e, c);
			} else {
				copyNumber(&a2, d);
				break;
			}
		}
	}
	return 0;
}

void sqrt_newton(struct NUMBER *N, struct NUMBER *x){
	struct NUMBER b, c, d;

	divby1keta(N, x, 2);
	copyNumber(x, &b);
	copyNumber(x, &c);

	while(1){
		copyNumber(&b, &c);
		copyNumber(x, &b);
		divide(N, &b, x, &d);
		add(x, &b, x);
		divby1keta(x, &d, 2);
		copyNumber(&d, x);

		if(numComp(x, &b) == 0) break;
		if(numComp(x, &c) == 0){
			if(numComp(x, &b)) copyNumber(&b, x);
			break;
		}
	} 
}

void soinsu(struct NUMBER *x, struct NUMBER *ans){
	struct NUMBER root_x, num, a, b, x2;
	clearByZero(&root_x);
	clearByZero(&num);
	clearByZero(&a);
	clearByZero(&b);
	copyNumber(x, &x2);
	setInt(&num, 2);
	sqrt_newton(&x2, &root_x);

	//2で割れるだけ割る
	while(1){
		if((x2.n[0] % 2) == 1)break;

		divby1keta(&x2, &a, 2);
		add(ans, &num, ans);
		copyNumber(&a, &x2);
	}
	
	increment(&num, &num);

	while(numComp(&x2, &root_x) == 1 && numComp(&x2, &num) == 1){
		divide(&x2, &num, &a, &b);
		if(isZero(&b) == 1){
			add(ans, &num, ans);
			copyNumber(&a, &x2);
		}
		else{
			//3->5->7...のように偶数を飛ばして割る数を加算
			increment(&num, &num);
			increment(&num, &num);
		}
	}
	
	if(x2.n[0] != 1 || getKeta(&x2) > 1) add(ans, &x2, ans);
}

/*int pollard_rho(struct NUMBER *x, struct NUMBER *ans){
	struct NUMBER y, g;

	while(1){
		if(g.)
	}
}*/

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
			printf("\n");
			printf("\n");
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

	struct NUMBER a, b, c,d;
	clearByZero(&a);
	clearByZero(&b);

	//setRnd(&a, 4);
	//setRnd(&b, 2);
	setInt(&a, 2);
	//setInt(&b, 11);
	printf("start number is\n");
	dispNumber(&a);
	printf("\n");
	
	ruthaaron(&a,10000);

	printf("end number is\n");
	decrement(&a, &b);

	dispNumber(&b);
	printf("\n");
	

	return 0;
}
