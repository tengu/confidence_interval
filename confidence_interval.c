#include <math.h>
/* 
 * pnormaldist and wilson_lower_bound (ci_lower_bound) are from this article:
 * http://stackoverflow.com/questions/1687497/objective-c-implementation-of-the-wilson-score-interval
 */
static double b[] = {1.570796288, 
		     0.03706987906,
		     -0.8364353589e-3,
		     -0.2250947176e-3,
		     0.6841218299e-5,
		     0.5824238515e-5,
		     -0.104527497e-5,
		     0.8360937017e-7,
		     -0.3231081277e-8,
		     0.3657763036e-10,
		     0.6936233982e-12};

static double pnormaldist(double qn)
{
	if(qn < 0.0 || 1.0 < qn)
		return 0.0;

	if(qn == 0.5)
		return 0.0;

	double w1 = qn;
	if(qn > 0.5)
		w1 = 1.0 - w1;
	double w3 = -log(4.0 * w1 * (1.0 - w1));
	w1 = b[0];
	int i=1;
	for(;i<11;i++)
		w1 += b[i] * pow(w3,i);

	if(qn > 0.5)
		return sqrt(w1*w3);
	return -sqrt(w1*w3);
}

double wilson_lower_bound(int pos, int n, double power)
{
	if(n==0)
		return 0.0;
	double z = pnormaldist(1-power/2);
	double phat = 1.0*pos/n;
	return (phat + z*z/(2*n) - z*sqrt((phat*(1-phat)+z*z/(4*n))/n))/(1+z*z/n);
}

#ifdef BUILD_COMMAND
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char * argv[]) 
{
	int pos,n;
	double power;

	if (argc<4) {
		printf("usage %s pos n power\n", argv[0]);
		exit(1);
	}

	pos=atoi(argv[1]);
	n=atoi(argv[2]);
	power=atof(argv[3]);

	printf("%f\n", wilson_lower_bound(pos,n,power));
	return 0;
}
#endif
