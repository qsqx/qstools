#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define ll long long
#define forn(i,n) for(int i=0;i<n;++i)
#define rep(i,n) for(int i=1;i<=n;++i)
#define repc(i,l,r) for(int i=l;i<=r;++i)
#define mp(a,b) make_pair(a,b)
#define llf long double
#define pii pair<int,int>
#define byte unsigned char
using namespace std;
byte ibuff[100005];
byte obuff[100005];
unsigned prime;
int gen1(){
}
int gen2(){
}
inline void wrt(byte *des,int pos,int k){
	des[pos / 8] |= (k&1) << (pos % 8);
}
void decode(byte *src,byte *des,int len){
	memset(des, 0, len / 4);
	len *= 2;
	forn(i, len){
		int mask = (~i & 1) ? (src[i >> 1] & 0xf) : (src[i >> 1] >> 4);
		int p = gen2() | (gen2() << 1);
		int k = (mask >> p) & 1;
		wrt(des, i, k^gen1());
	}
}
inline int get(byte *src,int pos){
	return (src[pos / 8] >> (pos % 8)) & 1;
}
void encode(byte *src,byte *des,int len){
	len *= 8;
	forn(i, len){
		int mask = (unsigned)rand()*prime + 777;
		mask &= 0xf;
		int x = gen1() ^ get(src, i);
		int p = gen2() | (gen2() << 1);
		mask &= ~(1 << p);
		mask |= x << p;
		if (~i & 1){
			des[i >> 1] = mask;
		}
		else{
			des[i >> 1] |= mask << 4;
		}
	}
}
int main(int argc,char *argv[]){
	srand(time(0));
	char *infile = "";
	char *outfile = "";
	int mod = 0;
	int r = 0;
	for (int p = 1; p < argc; ++p){
		if (argv[p][0] == '-'){
			char *s = argv[p] + 1;
			if (strcmp(s, "d") == 0 || strcmp(s, "decode")) mod = 1;
			else if(strcmp(s,"out")==0)	r = 1;
			else if (strcmp(s, "in") == 0) r = 0;
		}
		else{
			if (!r)	infile = argv[p];
			else outfile = argv[p];
			r = !r;
		}
	}
	if (infile[0] == '\0'){
		printf("infile is:");
		scanf("%s", infile);
	}
	if (outfile[0] == '\0'){
		printf("outfile is:");
		scanf("%s", outfile);
	}
	FILE *fin = fopen(infile, "rb");
	if (fin == NULL){ printf("can't open file %s", infile); }
	FILE *fout = fopen(outfile, "wb");
	if (fout == NULL){ printf("can't open file %s", outfile); }
	if (!mod){
		int len=fread(ibuff, 1, 10000, fin);
		encode(ibuff, obuff, len);
		fwrite(obuff, 1, len * 4, fout);
	}
	else{
		int len = fread(ibuff, 1, 10000, fin);
		decode(ibuff, obuff, len);
		fwrite(obuff, 1, len / 4, fout);
	}
	return 0;
}