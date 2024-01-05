#include <stdio.h>
int main()
{
    int i,j,kclusters,npts;
    kclusters=5;
    npts= 100   ;//MAXPOINTS;
    for(i=0;i < npts; i++)
       scanf("%lf%lf",&pts[i].x,&pts[i].y);

    k_cluster(pts, npts, CC, kclusters);
    for(i=0; i <npts; i++)
        printf("% 6.3f\t% 6.3f %5d\n",pts[i].x,pts[i].y,GC[i]);

}

int k_cluster(Point pts[], int npts, int  CC[], int kclusters)
{
    int i,j,k,ll,s;
    double D[MAXPOINTS];
    Point cj,cl;
    for (j= 1; j<  kclusters;j++){
        for(i = 0; i < npts;i++){
          D[i]=INF;
          for(ll = 0; ll < j ; ll++){
            cl=pts[  CC[ll]  ];
            D[i]=fmin(D[i], DIST(pts[i], cl));
          }
        }
        s=argmax(D,npts);
        CC[j]=s; GC[s]=j;
    }
    for(i = 0 ; i< npts ; i++){
       ll = argmindist(pts[i], CC, kclusters);
       GC[i]=ll;
    }

}