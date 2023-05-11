
#include <cstdio>

#include <cstdlib>

#include <ctime>

#include <vector>

#include <bitset>

#include <algorithm>

using namespace std;

const int n = 6;

const int L = 100;

int W[n][n];

static void* F[1L << n][n][n];

class state {
public:
	bool e[n];
	int s, t, ml;
	
	state () : s(-1), t(-1), ml(-1) {
		fill (e, e + n, false);
	}
	
	state* operator= (const state &a) {
		this->s = a.s;
		
		this->t = a.t;
		
		this->ml = a.ml;
		
		for (int i = 0; i < n; ++i) this->e[i] = a.e[i];
		
		return this;
	}
	
	int rec () {
		int z[n];
		int m = 0;
		
		if (this->ml != -1) {
			return this->ml;
		}
		
		int d = 0;
		
		for (int i = 0; i < n; ++i) {
			if (this->e[i]) {
				z[m++] = i;
				
				d |= 1L << i;
			}
		}
		
		if (F[d][this->s][this->t] != NULL) {
			state& st = *((state *) F[d][this->s][this->t]);
			
			return st.ml;
		}
		
		F[d][this->s][this->t] = this;
		
		if (m <= 1 || this->s == this->t) {
			return this->ml = 0;
		} else if (m == 2) {
			return this->ml = W[this->s][this->t];
		}
		
		//return 0;
		//puts("t");
		
		//for (int p = m >> 1; p <= m >> 1; ++p) {
		for (int p = 0; p < 1L << m; ++p)
		for (int c = 3; c < m; ++c)
		if (p & (1L << c))
		{
			state& left = *(new state()), right = *(new state());
			
			left.s = this->s;
			
			right.t = this->t;
			
			for (int i = 0; i < c; ++i) {
				left.e[z[i]] = p & (1L << i);
			}
			
			for (int i = c; i < m; ++i) {
				right.e[z[i]] = !left.e[z[i]];
			}

			left.e[z[c]] = right.e[z[c]] = true;

			right.s = left.t = z[c];
			
			int zl = 0, zr = 0;
			
			for (int i = 0; i < n; ++i) {
				if (left.e[i]) ++zl;
				
				if (right.e[i]) ++zr;
			}
			
			if (zl < 2 || zr < 2) continue;
			
			//printf ("%d\n", d);
			
			int kt = left.rec();
			
			if (kt != -1) {
				int kr = right.rec();
				
				if (kr != -1) {
					kt += kr;// + W[left.t][right.s];
					
					if (kt < this->ml || this->ml == -1) {
						this->ml = kt;
						
						printf ("%d: %d ", d, this->ml);
						//fill (this->e, this->e + n, false);
						
						//for (int i = 0; i < m; ++i) this->e[z[i]] = left.e[z[i]] || right.e[z[i]];
					}
				}
			}
		}
		
		F[d][this->s][this->t] = this;
		
		//printf ("%d ", this->ml);
		
		return this->ml;
	}
};

void optimal () {
	int e[n], o[n], l;
	
	l = -1;
	for (int i = 0; i < n; ++i) e[i] = i;
	
	do {
		int s = 0;
		
		for (int i = 0; i < n - 1; ++i) s += W[e[i]][e[i + 1]];
		
		if (s < l || l == -1) {
			l = s;
			
			for (int i = 0; i < n; ++i) o[i] = e[i];
		}
	} while (next_permutation (e, e + n));
	
	printf ("%d\n", l);
	
	for (int i = 0; i < n; ++i) printf (" %d", o[i]);
	
	printf ("\n\n");
}

int main(int argc, char** argv) {
	
	srand (time (NULL));
	
	memset (F, NULL, sizeof(F));
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int k = rand() * rand() * rand() * rand();
			
			if (k < 0) k = -k;
			
			W[i][j] = k % L;
		}
	}
	
	optimal ();
	
	int l = -1;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			if (i != j) {
				state& s = *(new state());
		
				s.s = i;
				
				s.t = j;
				
				fill (s.e, s.e + n, true);
				
				int k = s.rec();
				
				if (k >= 0) {
					if (l == -1 || k < l) l = k;
				}
			}
	}
	
	printf ("%d\n", l);
	
	return 0;
}
