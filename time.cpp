#include <sys/time.h>

// To get wall time

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

---------------------------------------------------------------------------------
An example usage:

double start1, end1;

cout << "Time check " << endl;

start1 = get_wall_time();

for(i=0;i<1000000;i++)
{
	cout << i << endl;
}

end1 = get_wall_time();

printf("Wall clock time = %f\n",end1-start1);
